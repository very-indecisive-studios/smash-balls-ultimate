#include "font.h"

Font::Font(LPD3DXFONT& fD3D, const std::string &fontName, int height, uint8_t weight, bool italic)
	: fontD3D(fD3D), fontName(fontName), height(height), weight(weight), italic(italic)
{ }

Font::~Font()
{
	fontD3D->Release();
}

LPD3DXFONT& Font::GetFontD3D()
{
	return fontD3D;
}

const std::string& Font::GetFontName()
{
	return fontName;
}

int Font::GetHeight()
{
	return height;
}

int Font::GetWeight()
{
	return weight;
}

int Font::GetItalic()
{
	return italic;
}
