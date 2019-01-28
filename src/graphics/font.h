#pragma once

#include <d3dx9.h>
#include <string>

struct FontConfig
{
	int height;
	UINT weight;
	BOOL italic;
};

class Font
{
private:
	LPD3DXFONT fontD3D;
	FontConfig config;
public:
	Font(LPD3DXFONT &fD3D, FontConfig config);
	~Font();

	LPD3DXFONT & GetFontD3D();
	FontConfig GetFontConfig();
};
