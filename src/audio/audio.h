#pragma once

#include <string>
#include <thread>
#include <wrl.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <xaudio2.h>

struct AudioFormat
{
	WAVEFORMATEX *pWaveFormat = nullptr;
	uint32_t waveFormatLength = 0;
};

class AudioData
{
private:
	struct AsyncSourceReaderState
	{
		HANDLE hOnReadSampleEvent;
		HRESULT status = S_OK;
		Microsoft::WRL::ComPtr<IMFSample> pCurrentSample = nullptr;
	    bool isEOF = false;

		AsyncSourceReaderState()
		{
			hOnReadSampleEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		}

		~AsyncSourceReaderState()
		{
			CloseHandle(hOnReadSampleEvent);
		}
	};

	struct AsyncSourceReaderCallback : public IMFSourceReaderCallback
	{
		AsyncSourceReaderState *pState;

		AsyncSourceReaderCallback(AsyncSourceReaderState &state)
		{
			pState = &state;
		}

		~AsyncSourceReaderCallback()
		{ }

		HRESULT __stdcall QueryInterface(const IID& riid, void** ppvObject) override
		{
			if (!ppvObject)
				return E_POINTER;

			if (_uuidof(IMFSourceReaderCallback) == riid)
			{
				*ppvObject = this;
				return S_OK;
			}

			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
		ULONG __stdcall AddRef() override { return 1; }
		ULONG __stdcall Release() override { return 0; }
		HRESULT __stdcall OnFlush(DWORD dwStreamIndex) override { return S_OK; }
		HRESULT __stdcall OnEvent(DWORD dwStreamIndex, IMFMediaEvent* pEvent) override { return S_OK; }

		HRESULT __stdcall OnReadSample(
			HRESULT hrStatus, DWORD dwStreamIndex, DWORD dwStreamFlags, LONGLONG llTimestamp, IMFSample* pSample
		) override
		{
			if (SUCCEEDED(hrStatus))
			{
				if (pSample)
				{
					pState->pCurrentSample = pSample;
				}
			}

			if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
			{
				pState->isEOF = true;
			}

			pState->status = hrStatus;

			SetEvent(pState->hOnReadSampleEvent);

			return S_OK;
		}
	};

public:
	AudioFormat format;

	// Async source reader reading the audio file.
	AsyncSourceReaderState asyncSourceReaderState;
	AsyncSourceReaderCallback asyncSourceReaderCallback { asyncSourceReaderState };
	Microsoft::WRL::ComPtr<IMFSourceReader> pAsyncSourceReader = nullptr;
};

struct AudioBufferState
{
	bool isFree = true;
};

class AudioPlayer
{
private:
	static const uint8_t MAX_BUFFERS = 3;

	// Buffers.
	uint8_t bufferIndex = 0;
	IMFMediaBuffer *buffers[MAX_BUFFERS] = { };
	AudioBufferState bufferStates[MAX_BUFFERS];

	IXAudio2SourceVoice *pSourceVoice = nullptr;

	AudioData *pAudioData = nullptr;

	std::thread *pAudioPlayerThread = nullptr;

	bool				isPlaying	= false;
	bool				isLooping	= false;

	float volumeLevel = 1.0f;

	void Work();
public:
	AudioPlayer(IXAudio2SourceVoice *pSourceVoice, AudioData *pAudioData);
	~AudioPlayer();

	void Play();
	void Stop();

	bool IsPlaying();

	void SetLooping(bool willLoop);

	void SetVolume(float level);

	static AudioPlayer * Create(const std::wstring &audioFileName);
	static AudioPlayer * CreatePersistent(const std::wstring &audioFileName, const std::string &tag);
	static AudioPlayer * GetPersistent(const std::string &tag);
};

class AudioEngine
{
private:
	struct SourceVoiceCallback : public IXAudio2VoiceCallback
	{
		// Unused.
		void __stdcall OnVoiceProcessingPassStart(UINT32 BytesRequired) override { }
		void __stdcall OnVoiceProcessingPassEnd() override { }
		void __stdcall OnStreamEnd() override { }
		void __stdcall OnBufferStart(void * pBufferContext) override { }
		void __stdcall OnLoopEnd(void *pBufferContext) override { }
		void __stdcall OnVoiceError(void *pBufferContext, HRESULT Error) override { }

		// Signal buffer ended.
		void __stdcall OnBufferEnd(void *pBufferContext) override
		{
			auto pAudioBufferState = static_cast<AudioBufferState *>(pBufferContext);

			pAudioBufferState->isFree = true;
		}
	};

private:
	Microsoft::WRL::ComPtr<IXAudio2>		pXAudio2		= nullptr;
	IXAudio2MasteringVoice				*pMasterVoice	= nullptr;

	SourceVoiceCallback sourceVoiceCallback;

	void CreateSourceReader(
		Microsoft::WRL::ComPtr<IMFAttributes> &rpSourceReaderConfig,
		std::wstring audioFileName,
		Microsoft::WRL::ComPtr<IMFSourceReader> &rpSourceReader,
		AudioFormat &rAudioFormat
	);

public:
	AudioEngine();
	~AudioEngine();

	void Initialize();

	AudioPlayer * CreateAudioPlayer(const std::wstring &audioFileName);
};