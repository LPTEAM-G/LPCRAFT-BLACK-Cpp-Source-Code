#ifndef MINECRAFT_CLASS_BLOCKS_LIQUIDBLOCK_HPP
#define MINECRAFT_CLASS_BLOCKS_LIQUIDBLOCK_HPP

#include "minecraft_class/TextureUVCoordinateSet.hpp"

class LiquidBlock
{
public:
	using getTextureFuncType = TextureUVCoordinateSet* (*)(LiquidBlock*, signed char);
	static getTextureFuncType getTextureOrig;

	static TextureUVCoordinateSet* getTexture(LiquidBlock* this_ptr, signed char);
	static void install(void* handler) noexcept;
};

#endif
