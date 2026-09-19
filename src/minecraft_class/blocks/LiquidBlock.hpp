//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/TextureUVCoordinateSet.hpp"

class LiquidBlock
{
public:
	using getTextureFuncType = TextureUVCoordinateSet* (*)(LiquidBlock*, signed char);
	static getTextureFuncType getTextureOrig;

	static TextureUVCoordinateSet* getTexture(LiquidBlock* this_ptr, signed char);
	static void install() noexcept;
};

