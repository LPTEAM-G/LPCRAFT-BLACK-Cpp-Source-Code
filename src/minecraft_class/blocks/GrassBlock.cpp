#include <dlfcn.h>
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "hook_macro.hpp"

GrassBlock::getTextureInWorldFuncType GrassBlock::getTextureInWorldOrig = nullptr;

TextureUVCoordinateSet* GrassBlock::getTextureInWorld(GrassBlock* this_ptr, BlockSource* block_source, const BlockPos* pos_in_world, signed char face)
{
	constexpr signed char bottom_face = 0;
	constexpr signed char top_face = 1;
	
	TextureUVCoordinateSet* top_set = (TextureUVCoordinateSet*)((char*)this_ptr + 176);
	TextureUVCoordinateSet* bottom_set = (TextureUVCoordinateSet*)((char*)this_ptr + 152);
	TextureUVCoordinateSet* snowed_side_set = (TextureUVCoordinateSet*)((char*)this_ptr + 212);
	
	TextureUVCoordinateSet* texture_uv_set = getTextureInWorldOrig(this_ptr, block_source, pos_in_world, face);

	//判断其是否为侧面纹理
	if (
		texture_uv_set != top_set and
		texture_uv_set != bottom_set and
		texture_uv_set != snowed_side_set
	)
		return top_set;
	else
		return texture_uv_set;
}

void GrassBlock::install(void* handler) noexcept
{
	void* getTextureInWorldTarget = dlsym(handler, "_ZN10GrassBlock10getTextureER11BlockSourceRK8BlockPosa");
	MSHook(getTextureInWorldTarget, getTextureInWorld, getTextureInWorldOrig);
}
