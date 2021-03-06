#pragma once

#include <d3dx9.h>
#include <string>

namespace FontWeight
{
	constexpr UINT BOLD = FW_BOLD;
	constexpr UINT LIGHT = FW_LIGHT;
	constexpr UINT THICC = BOLD;
	constexpr UINT NORMAL = FW_NORMAL;
};

struct FontConfig
{
	int height;
	UINT weight = FontWeight::NORMAL;
	bool italic = false;

	bool operator==(const FontConfig& rhs)
	{
		return this->height == rhs.height && 
			this->weight == rhs.weight && 
			this->italic == rhs.italic;
	}
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
