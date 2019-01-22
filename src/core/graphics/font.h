#pragma once
#include <d3dx9.h>
#include <string>

class Font
{
private:
	LPD3DXFONT fontD3D;
	std::string fontName;
	int height;
	UINT weight;
	BOOL italic;
public:
	Font(LPD3DXFONT &fD3D, const std::string &fontName, int height, uint8_t weight, bool italic);
	~Font();

	LPD3DXFONT & GetFontD3D();
	const std::string& GetFontName();
	int GetHeight();
	int GetWeight();
	int GetItalic();
};
