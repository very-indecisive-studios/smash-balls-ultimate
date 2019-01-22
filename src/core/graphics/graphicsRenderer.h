#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include "texture.h"
#include "core/math.h"
#include "core/sprites/sprite.h"
#include "core/text/text.h"


enum class DrawJobType { TEXTURE, FONT };

struct DrawJob
{
	DrawJobType type;
	Vector2 pos;
	uint8_t layer;

	DrawJob(DrawJobType type, Vector2 pos, uint8_t layer)
		: type(type), pos(pos), layer(layer) { }
	virtual ~DrawJob() { }
};

struct DrawTextureJob : public DrawJob
{
	Texture *texture;
	int scale;
	DrawingArea drawingArea;

	DrawTextureJob
	(
		Texture *texture,
		int scale,
		DrawingArea drawingArea,
		Vector2 pos,
		uint8_t layer
	) : DrawJob(DrawJobType::TEXTURE, pos, layer),
		texture(texture),
		scale(scale),
		drawingArea(drawingArea)
	{ }
	~DrawTextureJob() { }
};

struct DrawFontJob : public DrawJob
{
	Font *font;
	std::string text;
	float angleDegrees = 0;
	int color = 0xFFFFFFFF;
	int alignment;
	uint8_t layer;

	DrawFontJob
	(
		Font *font, 
		std::string text, 
		float angleDegrees, 
		int color,
		int alignment,
		Vector2 pos, 
		uint8_t layer
	) : DrawJob(DrawJobType::FONT, pos, layer),
		font(font),
		text(text),
		angleDegrees(angleDegrees),
		color(color),
		alignment(alignment)
	{ }
	~DrawFontJob() { }
};

class GraphicsRenderer
{
private:
	// Sprite draw queue.
	std::vector<DrawJob *> drawJobs;

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

	void ClearAllDrawJobs();
public:
	GraphicsRenderer();

	~GraphicsRenderer();

	HRESULT Initialize(HWND hwnd, int width, int height, bool fullscreen);

	void QueueDrawJob(DrawJob *job);

	HRESULT HandleLostDevice();

	HRESULT Render();

	Texture * LoadTextureFromFile(std::string fileName);

	Font * LoadFont(const std::string& fontName, int height, UINT weight, BOOL italic);

	void ReleaseAll();
};
