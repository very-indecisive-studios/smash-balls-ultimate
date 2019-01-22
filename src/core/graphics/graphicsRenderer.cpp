#include <algorithm>
#include "graphicsRenderer.h"
#include "core/gameException.h"

void GraphicsRenderer::InitParamsD3D() 
{
	// Initialize D3D presentation params
	ZeroMemory(&paramsD3D, sizeof(paramsD3D));              // fill the structure with 0

	paramsD3D.BackBufferWidth = width;
	paramsD3D.BackBufferHeight = height;
	if (fullscreen) // if fullscreen
		paramsD3D.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24 bit color
	else
		paramsD3D.BackBufferFormat = D3DFMT_UNKNOWN;   // use desktop setting
	paramsD3D.BackBufferCount = 1;
	paramsD3D.SwapEffect = D3DSWAPEFFECT_DISCARD;
	paramsD3D.hDeviceWindow = hwnd;
	paramsD3D.Windowed = (!fullscreen);
	paramsD3D.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

HRESULT GraphicsRenderer::SwapBuffer()
{
	HRESULT result = E_FAIL;

	result = deviceD3D->Present(NULL, NULL, NULL, NULL);

	return result;
}

void GraphicsRenderer::ReleaseAll()
{
	spriteD3D->Release();
	deviceD3D->Release();
	d3d->Release();

	ClearAllDrawJobs();
}

HRESULT GraphicsRenderer::Reset()
{
	HRESULT result = E_FAIL;    // default to fail, replace on success

	InitParamsD3D();                        // init D3D presentation parameters

	result = deviceD3D->Reset(&paramsD3D);   // attempt to reset graphics device

	return result;
}

GraphicsRenderer::GraphicsRenderer()
{
	deviceD3D = NULL;
	spriteD3D = NULL;
	d3d = NULL;
}

GraphicsRenderer::~GraphicsRenderer()
{
	ReleaseAll();
}

HRESULT GraphicsRenderer::Initialize(HWND hwnd, int width, int height, bool fullscreen)
{
	this->hwnd = hwnd;
	this->width = width;
	this->height = height;
	this->fullscreen = fullscreen;

	HRESULT result = E_FAIL;

	// Initialize D3D.
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) 
	{
		return result;
	}

	// Initialize D3D presentation params.
	InitParamsD3D();

	if (fullscreen) 
	{
		UINT modes = d3d->GetAdapterModeCount(
			D3DADAPTER_DEFAULT,
			paramsD3D.BackBufferFormat
		);

		for (UINT i = 0; i < modes; i++)
		{
			result = d3d->EnumAdapterModes(
				D3DADAPTER_DEFAULT,
				paramsD3D.BackBufferFormat,
				i,
				&dModeD3D
			);

			if (
				SUCCEEDED(result) &&
				dModeD3D.Height == paramsD3D.BackBufferHeight &&
				dModeD3D.Width == paramsD3D.BackBufferWidth &&
				dModeD3D.RefreshRate >= paramsD3D.FullScreen_RefreshRateInHz
			) 
			{
				
				paramsD3D.FullScreen_RefreshRateInHz = dModeD3D.RefreshRate;
			}
		}
	}

	// Determine if graphics card supports harware texturing and lighting and vertex shaders
	D3DCAPS9 caps;
	DWORD behavior;
	result = d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	// If device doesn't support HW T&L or doesn't support 1.1 vertex 
	// shaders in hardware, then switch to software vertex processing.
	if (
		(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1)
	)
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  // use software only processing
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;  // use hardware only processing

	// Create D3D device.
	result = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&paramsD3D,
		&deviceD3D
	);

	if (FAILED(result)) 
	{
		return result;
	}

	// Create D3D sprite.
	result = D3DXCreateSprite(deviceD3D, &spriteD3D);

	return result;
}

HRESULT GraphicsRenderer::HandleLostDevice()
{
	HRESULT result = E_FAIL;

	if (deviceD3D == NULL)
	{
		return result;
	}

	result = deviceD3D->TestCooperativeLevel();
	
	if (FAILED(result))                  // if graphics device is not in a valid state
	{
		// if the device is lost and not available for reset
		if (result == D3DERR_DEVICELOST)
		{
			Sleep(100);             // yield cpu time (100 mili-seconds)
			return result;
		}
		// the device was lost but is now available for reset
		else if (result == D3DERR_DEVICENOTRESET)
		{
			ReleaseAll();
			result = Reset(); // attempt to reset graphics device
			
			if (FAILED(result))          // if reset failed
				return result;
		}
		else
			return result;                 // other device error
	}

	return result;
}

HRESULT GraphicsRenderer::Render() 
{
	HRESULT result = E_FAIL;

	if (deviceD3D == nullptr || spriteD3D == nullptr) 
	{
		return result;
	}
	
	try 
	{
		ThrowIfFailed(deviceD3D->Clear(0, NULL, D3DCLEAR_TARGET, BACK_COLOUR, 1.0F, 0));

		ThrowIfFailed(deviceD3D->BeginScene());
		ThrowIfFailed(spriteD3D->Begin(D3DXSPRITE_ALPHABLEND));
		
		// Use nearest filtering because we using pixel art.
		deviceD3D->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		deviceD3D->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

		// Sort the jobs according to layers; ascending order.
		std::sort(
			drawJobs.begin(), 
			drawJobs.end(), 
			[](const DrawJob *lhs, const DrawJob *rhs)
			{
				return lhs->layer < rhs->layer;
			}
		);

		for (auto &job : drawJobs)
		{
			if (job->type == DrawJobType::TEXTURE)
			{
				auto sprJob = (DrawTextureJob *)job;
				
				// Find center of sprite
				D3DXVECTOR2 spriteCenter = D3DXVECTOR2(
					(float)(sprJob->drawingArea.right / 2 * sprJob->scale),
					(float)(sprJob->drawingArea.bottom / 2 * sprJob->scale)
				);
				D3DXVECTOR2 translate = D3DXVECTOR2(sprJob->pos.x, sprJob->pos.y);
				D3DXVECTOR2 scaling(sprJob->scale, sprJob->scale);
				
				D3DXMATRIX matrix;
				D3DXMatrixTransformation2D(
					&matrix,                // the matrix
					NULL,                   // keep origin at top left when scaling
					0.0f,                   // no scaling rotation
					&scaling,               // scale amount
					&spriteCenter,          // rotation center
					0,						// rotation angle
					&translate				// X,Y location
				);
				
				spriteD3D->SetTransform(&matrix);
				
				spriteD3D->Draw(
					sprJob->texture->GetTextureD3D(),
					&sprJob->drawingArea,
					NULL,
					NULL,
					0xFFFFFFFF
				);
			}
			else if (job->type == DrawJobType::FONT)
			{
				auto textJob = (DrawFontJob *)job;
				
				RECT posRect;
				posRect.top = textJob->pos.y;
				posRect.left = textJob->pos.x;
				posRect.right = 640;
				posRect.bottom = 480;
				
				// Rotation center
				D3DXVECTOR2 rCenter = D3DXVECTOR2((float)textJob->pos.x, (float)textJob->pos.y);
				// Setup matrix to rotate text by angle.
				D3DXMATRIX matrix;
				D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, textJob->angleDegrees, NULL);
				
				// Tell the sprite about the matrix.
				spriteD3D->SetTransform(&matrix);
				
				textJob->font->GetFontD3D()->DrawText(
					spriteD3D,
					textJob->text.c_str(),
					-1,
					&posRect,
					textJob->alignment,
					textJob->color
				);
			}
		}
		
		ThrowIfFailed(spriteD3D->End());
		ThrowIfFailed(deviceD3D->EndScene());

		ClearAllDrawJobs();
		
		ThrowIfFailed(SwapBuffer());

		result = S_OK;
	}
	catch (GameException e) 
	{
		return result;
	}

	return result;
}

Texture * GraphicsRenderer::LoadTextureFromFile(std::string fileName) 
{
	HRESULT result = E_FAIL;

	// Get image info from file.
	D3DXIMAGE_INFO imageInfo;
	result = D3DXGetImageInfoFromFile(fileName.c_str(), &imageInfo);
	ThrowIfFailed(result);

	// Create the new texture by loading from file.
	LPDIRECT3DTEXTURE9 textureD3D = NULL;
	result = D3DXCreateTextureFromFileEx(
		deviceD3D,          //3D device
		fileName.c_str(),	//image filename
		imageInfo.Width,    //texture width
		imageInfo.Height,   //texture height
		1,                  //mip-map levels (1 for no chain)
		0,                  //usage
		D3DFMT_UNKNOWN,     //surface format (default)
		D3DPOOL_DEFAULT,    //memory class for the texture
		D3DX_DEFAULT,       //image filter
		D3DX_DEFAULT,       //mip filter
		0xFF000000,         //color key for transparency
		&imageInfo,         //bitmap file info (from loaded file)
		NULL,               //color palette
		&textureD3D			//destination texture
	);

	ThrowIfFailed(result);

	return new Texture(textureD3D, imageInfo.Width, imageInfo.Height);
}

Font * GraphicsRenderer::LoadFont(const std::string& fontName, int height, UINT weight, BOOL italic)
{
	HRESULT result = E_FAIL;
	
	LPD3DXFONT fontD3D = NULL;
	result = D3DXCreateFont(
		deviceD3D, 
		height, 
		0, 
		weight, 
		1, 
		italic,
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, 
		fontName.c_str(),
		&fontD3D
	);
	
	ThrowIfFailed(result);

	return new Font(fontD3D, fontName, height, weight, italic);
}

void GraphicsRenderer::QueueDrawJob(DrawJob *job) 
{
	drawJobs.push_back(job);
}

void GraphicsRenderer::ClearAllDrawJobs() 
{
	for (auto sprJob : drawJobs)
	{
		delete sprJob;
		sprJob = nullptr;
	}

	drawJobs.clear();
}
