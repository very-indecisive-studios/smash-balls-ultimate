#include "texture.h"

Texture::Texture(LPDIRECT3DTEXTURE9 &tD3D, int w, int h)
{
	textureD3D = tD3D;
	width = w;
	height = h;
}

Texture::~Texture()
{
	textureD3D->Release();
}

LPDIRECT3DTEXTURE9 & Texture::GetTextureD3D()
{
	return textureD3D;
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}
