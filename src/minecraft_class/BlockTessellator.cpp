//Copyright (c) 2026 LPTEAM
#include "BlockTessellator.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AmbientOcclusionCalculator.hpp"
#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockSource.hpp"
#include <asm-generic/mman-common.h>
#include <bits/sysconf.h>
#include <cstdint>
#include <cstring>

BlockTessellator::tessellateBlockInWorldWithAmbienceOcclusionType BlockTessellator::tessellateBlockInWorldWithAmbienceOcclusionTypeOrig = nullptr;
BlockTessellator::_getTextureFuncType BlockTessellator::_getTextureOrig = nullptr;

BlockSource* BlockTessellator::get_block_source() noexcept
{
	return *(BlockSource**)((uintptr_t)this + 4);
}

int BlockTessellator::tessellate_block_in_world_with_ambience_occlusion(BlockTessellator* this_ptr, Block* block, BlockPos* pos, const Color* color, const BlockOccluder* occluder)
{
	int result = tessellateBlockInWorldWithAmbienceOcclusionTypeOrig(this_ptr, block, pos, color, occluder);
	return result;
}

TextureUVCoordinateSet* BlockTessellator::_get_texture(BlockTessellator* this_ptr, Block* block, const BlockPos* pos_in_world, signed char face)
{
	return _getTextureOrig(this_ptr, block, pos_in_world, face);
}

void BlockTessellator::install() noexcept
{
	//_ZNK16BlockTessellator11_getTextureER5BlockRK8BlockPosa
	void* _getTextureTarget = minecraft_app::get_lib_thumb_function_ptr(0x397554);
	MSHook(_getTextureTarget, _get_texture, _getTextureOrig);

	//_ZN16BlockTessellator43tessellateBlockInWorldWithAmbienceOcclusionER5Block8BlockPosRK5ColorRK13BlockOccluder
	void* tessellateBlockInWorldWithAmbienceOcclusionTypeTarget =
		minecraft_app::get_lib_thumb_function_ptr(0x39F430);
	MSHook(
		tessellateBlockInWorldWithAmbienceOcclusionTypeTarget,
		tessellate_block_in_world_with_ambience_occlusion,
		tessellateBlockInWorldWithAmbienceOcclusionTypeOrig
	);
}
