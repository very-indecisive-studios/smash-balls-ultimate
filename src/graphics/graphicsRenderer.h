#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include "texture.h"
#include "sprites/sprite.h"
#include "font.h"
#include "math/math.h"

struct DrawJob
{
	Vector2 pos;
	DrawingArea drawingArea = { 0 };
	uint8_t layer = 0;
	float angleDegrees = 0.0f;
	int color = 0xFFFFFFFF;

	DrawJob() { }
	virtual ~DrawJob() { }
};

struct DrawTextureJob : public DrawJob
{
	Texture *texture;
	int scale;

	DrawTextureJob() { }
	virtual ~DrawTextureJob() { }
};

struct DrawFontJob : public DrawJob
{
	Font *font;
	std::string text;
	int alignment;

	DrawFontJob() { }
	virtual ~DrawFontJob() { }
};

class GraphicsRenderer
{
private:
	enum class DrawJobType { TEXTURE, FONT };

	struct DrawJobRequest
	{
		DrawJobType type;
		DrawJob *job;

		DrawJobRequest() { }
		~DrawJobRequest()
		{
			delete job;
		}
	};

	// Sprite draw queue.
	std::vector<DrawJobRequest *> drawJobRequests;

	// DirectX 3D pointers.
	LPDIRECT3DDEVICE9	deviceD3D;
	LPDIRECT3D9			d3d;
	LPD3DXSPRITE		spriteD3D;

	// DirectX 3D properties.
	D3DPRESENT_PARAMETERS	paramsD3D;
	D3DDISPLAYMODE			dModeD3D;

	// Application window properties.
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;

	const D3DCOLOR BACK_COLOUR = 0xFF000000;

	void InitParamsD3D();

	HRESULT SwapBuffer();

	HRESULT Reset();

	void ClearAllDrawJobRequests();
public:
	GraphicsRenderer();

	~GraphicsRenderer();

	HRESULT Initialize(HWND hwnd, int width, int height, bool fullscreen);

	void QueueDrawTextureJob(DrawTextureJob *job);

	void QueueDrawFontJob(DrawFontJob *job);

	HRESULT HandleLostDevice();

	HRESULT Render();

	Texture * LoadTextureFromFile(const std::string &fileName);

	Font * LoadFont(const std::string &fontName, FontConfig config);

	void ReleaseAll();
};
