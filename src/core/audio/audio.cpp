#include "audio.h"
#include "core/gameException.h"
#include "context.h"

AudioEngine::AudioEngine()
{ }

AudioEngine::~AudioEngine()
{
	pXAudio2->StopEngine();

	pMasterVoice->DestroyVoice();

	MFShutdown();
}

void AudioEngine::Initialize()
{
	CoInitializeEx(NULL, COINITBASE_MULTITHREADED);

	// WMF setup.
	ThrowIfFailed(MFStartup(MF_VERSION), "Failed to start Windows Media Foundation");

	// XAudio2 setup.
	ThrowIfFailed(XAudio2Create(&pXAudio2), "Failed to create XAudio2 engine.");

	ThrowIfFailed(pXAudio2->CreateMasteringVoice(&pMasterVoice), "Failed to create XAudio2 master voice.");
}

void AudioEngine::CreateSourceReader(
	Microsoft::WRL::ComPtr<IMFAttributes> &rpSourceReaderConfig,
	std::wstring audioFileName,
	Microsoft::WRL::ComPtr<IMFSourceReader> &rpSourceReader, 
	AudioFormat &rAudioFormat
)
{
	// Create the source reader
	IMFSourceReader *sourceReader;
	ThrowIfFailed(
		MFCreateSourceReaderFromURL(audioFileName.c_str(), rpSourceReaderConfig.Get(), &sourceReader),
		"Cannot create source reader from filename."
	);

	// Stream index.
	DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;

	// Deselect all other streams and then select the first audio stream.
	ThrowIfFailed(
		sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false),
		"Cannot diselect all streams."
	);

	ThrowIfFailed(
		sourceReader->SetStreamSelection(streamIndex, true),
		"Cannot select audio stream."
	);

	// Get information about the media file.
	Microsoft::WRL::ComPtr<IMFMediaType> nativeMediaType;
	ThrowIfFailed(
		sourceReader->GetNativeMediaType(streamIndex, 0, nativeMediaType.GetAddressOf()),
		"Cannot retrieve information of media file."
	);

	// Make sure that this is really an audio file
	GUID majorType;
	ThrowIfFailed(
		nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType),
		"Cannot retrieve major type of media file."
	);
	if (majorType != MFMediaType_Audio)
	{
		throw GameException("Error attempting to load a non-audio file.");
	}

	// Check whether the audio file is compressed or uncompressed.
	GUID subType;
	ThrowIfFailed(
		nativeMediaType->GetGUID(MF_MT_SUBTYPE, &subType),
		"Cannot retrieve sub type of media file"
	);
	// If compressed type.
	if (subType != MFAudioFormat_Float || subType != MFAudioFormat_PCM)
	{
		// the audio file is compressed; we have to decompress it first
		// to do so, we inform the SourceReader that we want uncompressed data
		// this causes the SourceReader to look for decoders to perform our request
		Microsoft::WRL::ComPtr<IMFMediaType> partialType = nullptr;
		ThrowIfFailed(
			MFCreateMediaType(partialType.GetAddressOf()),
			"Cannot create media type."
		);

		// set the media type to "audio"
		ThrowIfFailed(
			partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio),
			"Cannot set major type of new media type."
		);

		// request uncompressed data
		ThrowIfFailed(
			partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM),
			"Cannot set sub type of new media type."
		);

		ThrowIfFailed(
			sourceReader->SetCurrentMediaType(streamIndex, NULL, partialType.Get()),
			"Cannot set the new media type to source reader."
		);
	}

	// Load wave format of the file.
	Microsoft::WRL::ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
	ThrowIfFailed(
		sourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf()),
		"Cannot get media type from source reader."
	);

	ThrowIfFailed(
		MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType.Get(), &rAudioFormat.pWaveFormat, &rAudioFormat.waveFormatLength),
		"Cannot create wave format from media type."
	);

	// Ensure the stream is selected before copying data.
	ThrowIfFailed(
		sourceReader->SetStreamSelection(streamIndex, true),
		"Cannot select audio stream."
	);

	rpSourceReader = sourceReader;
}

AudioPlayer* AudioEngine::CreateAudioPlayer(const std::wstring& audioFileName)
{
	AudioData *pAudioData = new AudioData();

	Microsoft::WRL::ComPtr<IMFAttributes> pSourceReaderConfig = nullptr;
	MFCreateAttributes(&pSourceReaderConfig, 1);
	pSourceReaderConfig->SetUINT32(MF_LOW_LATENCY, true);
	pSourceReaderConfig->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, &pAudioData->asyncSourceReaderCallback);
	
	CreateSourceReader(pSourceReaderConfig, audioFileName, pAudioData->pAsyncSourceReader, pAudioData->format);

	IXAudio2SourceVoice *pSourceVoice = nullptr;
	pXAudio2->CreateSourceVoice(&pSourceVoice, pAudioData->format.pWaveFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &sourceVoiceCallback);

	AudioPlayer *pAudioPlayer = new AudioPlayer(pSourceVoice, pAudioData);

	return pAudioPlayer;
}

AudioPlayer::AudioPlayer(IXAudio2SourceVoice* pSourceVoice, AudioData* pAudioStream)
	: pSourceVoice(pSourceVoice), pAudioData(pAudioStream)
{ }

AudioPlayer::~AudioPlayer()
{
	Stop();

	if (pAudioPlayerThread)
	{
		if (pAudioPlayerThread->joinable())
		{
			pAudioPlayerThread->join();
		}

		delete pAudioPlayerThread;
	}

	pSourceVoice->Stop();
	pSourceVoice->FlushSourceBuffers();
	pSourceVoice->DestroyVoice();

	for (auto pBuffer : buffers)
	{
		if (pBuffer)
		{
			pBuffer->Unlock();

			pBuffer->Release();
		}
	}
	 
	delete pAudioData;
}

void AudioPlayer::Work()
{
	pSourceVoice->Start();

	while (isPlaying)
	{
		// Update volume level.
		pSourceVoice->SetVolume(volumeLevel);

		// Use a buffer that is free.
		auto &rCurrentBufferState = bufferStates[bufferIndex];
        if (!rCurrentBufferState.isFree)
        {
			bufferIndex++;
			bufferIndex %= MAX_BUFFERS;

			continue;
        }

		/*
		 *  Reading samples from media file.
		 */

		// Read sample 'asynchronously' and block the thread until the reader reads a sample.
		// Using an asynchronous reader will read small samples of a media file instead of one sample containing the whole audio file.
		pAudioData->pAsyncSourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, nullptr, nullptr, nullptr);
		WaitForSingleObject(pAudioData->asyncSourceReaderState.hOnReadSampleEvent, INFINITE);
		ThrowIfFailed(pAudioData->asyncSourceReaderState.status, "Failed to read sample from audio file.");

		// If reader reaches the end of file, set the seeker of the reader to the start of the media file.
	    if (pAudioData->asyncSourceReaderState.isEOF)
	    {
			if (isLooping)
			{
				// Set the EOF state to false.
				pAudioData->asyncSourceReaderState.isEOF = false;

				// Set the seeking position to start of media file.
				PROPVARIANT var = { 0 };
				var.vt = VT_I8;

				pAudioData->pAsyncSourceReader->SetCurrentPosition(GUID_NULL, var);
			}
			else
			{
				break;
			}
	    }

		/*
		 *  Copying data sampled to available buffer. 
		 */

		// Get current buffer, unlock the buffer and release the buffer.
		auto &rpCurrentBuffer = buffers[bufferIndex];
		if (rpCurrentBuffer)
		{
			rpCurrentBuffer->Unlock();

			rpCurrentBuffer->Release();
		}

		// Fill the current buffer with data from sample.
		pAudioData->asyncSourceReaderState.pCurrentSample->ConvertToContiguousBuffer(&rpCurrentBuffer);

		// Obtain the address of data and the length through locking the buffer.
		BYTE *data = NULL;
		DWORD dataLength = 0;
		rpCurrentBuffer->Lock(&data, NULL, &dataLength);

		// Update the state of the buffer.
		rCurrentBufferState.isFree = false;

		// Create an XAudio buffer to be queued to the source voice.
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.AudioBytes = dataLength;
		buffer.pAudioData = data;
		buffer.pContext = &rCurrentBufferState;
		pSourceVoice->SubmitSourceBuffer(&buffer);
	}

	/*
	 *  Reset the seeker of media file if the player is stopped
	 */
	// Set the EOF state to false.
	pAudioData->asyncSourceReaderState.isEOF = false;

	// Set the seeking position to start of media file.
	PROPVARIANT var = { 0 };
	var.vt = VT_I8;

	pAudioData->pAsyncSourceReader->SetCurrentPosition(GUID_NULL, var);

	isPlaying = false;

	pSourceVoice->Stop();
	pSourceVoice->FlushSourceBuffers();
}

void AudioPlayer::Play()
{
	if (!pAudioPlayerThread)
	{
		isPlaying = true;
		pAudioPlayerThread = new std::thread(&AudioPlayer::Work, this);
	}
	else
	{
		isPlaying = false;
		if (pAudioPlayerThread->joinable())
		{
			pAudioPlayerThread->join();
		}
		delete pAudioPlayerThread;

		isPlaying = true;
		pAudioPlayerThread = new std::thread(&AudioPlayer::Work, this);
	}
}

void AudioPlayer::Stop()
{
	isPlaying = false;
}

bool AudioPlayer::IsPlaying()
{
	return isPlaying;
}

void AudioPlayer::SetLooping(bool willLoop)
{
	isLooping = willLoop;
}

void AudioPlayer::SetVolume(float level)
{
	volumeLevel = level;
}

AudioPlayer * AudioPlayer::Create(const std::wstring& audioFileName)
{
	return Context::Get()->GetAudioEngine()->CreateAudioPlayer(audioFileName);
}

AudioPlayer* AudioPlayer::CreatePersistent(const std::wstring& audioFileName, const std::string& tag)
{
	auto pAudioPlayer = Create(audioFileName);

	Context::Get()->GetResourceManager()->StorePersistentAudioPlayer(pAudioPlayer, tag);

	return pAudioPlayer;
}

AudioPlayer* AudioPlayer::GetPersistent(const std::string& tag)
{
	return Context::Get()->GetResourceManager()->GetPersistentAudioPlayer(tag);
}
