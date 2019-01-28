#include "pch.h"

#include "font.h"

Font::Font(LPD3DXFONT& fD3D, FontConfig config)
	: fontD3D(fD3D), config(config)
{ }

Font::~Font()
{
	fontD3D->Release();
}

LPD3DXFONT & Font::GetFontD3D()
{
	return this->fontD3D;
}

FontConfig Font::GetFontConfig()
{
	return this->config;
}
