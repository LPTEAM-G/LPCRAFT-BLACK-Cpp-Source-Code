//Copyright (c) 2026 LPTEAM
#include "BlockTessellator.hpp"
#include "hook_macro.hpp"
#include "init.hpp"
#include "minecraft_class/AmbientOcclusionCalculator.hpp"
#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockSource.hpp"
#include <asm-generic/mman-common.h>
#include <bits/sysconf.h>
#include <cstdint>
#include <cstring>
#include <dlfcn.h>

BlockTessellator::tessellateBlockInWorldWithAmbienceOcclusionType BlockTessellator::tessellateBlockInWorldWithAmbienceOcclusionTypeOrig = nullptr;
BlockTessellator::_getTextureFuncType BlockTessellator::_getTextureOrig = nullptr;

BlockSource* BlockTessellator::get_block_source(BlockTessellator* this_ptr) noexcept
{
	return *(BlockSource**)((uintptr_t)this_ptr + 4);
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
	void* _getTextureTarget = dlsym(minecraft_app::game_lib_handler,"_ZNK16BlockTessellator11_getTextureER5BlockRK8BlockPosa");
	MSHook(_getTextureTarget, _get_texture, _getTextureOrig);

	void* tessellateBlockInWorldWithAmbienceOcclusionTypeTarget =
		dlsym(minecraft_app::game_lib_handler, "_ZN16BlockTessellator43tessellateBlockInWorldWithAmbienceOcclusionER5Block8BlockPosRK5ColorRK13BlockOccluder");
	MSHook(
		tessellateBlockInWorldWithAmbienceOcclusionTypeTarget,
		tessellate_block_in_world_with_ambience_occlusion,
		tessellateBlockInWorldWithAmbienceOcclusionTypeOrig
	);
}
