//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_BLOCKS_BLOCKTESSELLATOR_HPP
#define MINECRAFT_CLASS_BLOCKS_BLOCKTESSELLATOR_HPP

#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockOccluder.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/Color.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include <cstdint>

class BlockTessellator
{
private:
	static unsigned long lib_base;

	enum class tessellate_block_flush_mode : uint16_t
	{
		default_mode = 0x0599,
		turn_off_mode = 0x0021,
		turn_on_mode = 0x0121
	};

public:
	using _getTextureFuncType = TextureUVCoordinateSet*(*)(BlockTessellator*, Block*, const BlockPos*, signed char);
	static _getTextureFuncType _getTextureOrig;

	using tessellateBlockInWorldWithAmbienceOcclusionType = int(*)(BlockTessellator*, Block*, BlockPos*, const Color*, const BlockOccluder*);
	static tessellateBlockInWorldWithAmbienceOcclusionType tessellateBlockInWorldWithAmbienceOcclusionTypeOrig;

	//--- Hooked Functions ---//
	static int tessellate_block_in_world_with_ambience_occlusion(BlockTessellator* this_ptr, Block* block, BlockPos* pos, const Color* color, const BlockOccluder* occluder);
	static TextureUVCoordinateSet* _get_texture(BlockTessellator* this_ptr, Block* block, const BlockPos* pos_in_world, signed char face);

	BlockSource* get_block_source() noexcept;

	static void install() noexcept;
};

#endif
