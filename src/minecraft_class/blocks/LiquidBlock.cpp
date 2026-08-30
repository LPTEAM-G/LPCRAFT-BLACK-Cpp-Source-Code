//Copyright (c) 2026 LPTEAM
#include "LiquidBlock.hpp"
#include "init.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include "hook_macro.hpp"
#include <dlfcn.h>

LiquidBlock::getTextureFuncType LiquidBlock::getTextureOrig = nullptr;

TextureUVCoordinateSet* LiquidBlock::getTexture(LiquidBlock *this_ptr, signed char status)
{
	
	TextureUVCoordinateSet* flowing_status = (TextureUVCoordinateSet*)((char*)this_ptr + 176);
	TextureUVCoordinateSet* calm_status = (TextureUVCoordinateSet*)((char*)this_ptr + 152);
	if (status > 1)
		return flowing_status;
	else
		return calm_status;
}

void LiquidBlock::install() noexcept
{
	void* getTextureTarget = dlsym(minecraft_app::game_lib_handler, "_ZN11LiquidBlock10getTextureEa");
	MSHook(getTextureTarget, getTexture, getTextureOrig);
}
