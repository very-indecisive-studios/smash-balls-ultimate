#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Texture 
{
private:
	LPDIRECT3DTEXTURE9 textureD3D;
	int width;
	int height;
public:
	Texture(LPDIRECT3DTEXTURE9 &tD3D, int w, int h);
	~Texture();

	LPDIRECT3DTEXTURE9 & GetTextureD3D();
	int GetWidth();
	int GetHeight();
};
