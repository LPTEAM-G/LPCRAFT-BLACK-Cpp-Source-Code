#ifndef MINECRAFT_CLASS_BLOCKS_BLOCKTESSELLATOR_HPP
#define MINECRAFT_CLASS_BLOCKS_BLOCKTESSELLATOR_HPP

#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"

class BlockTessellator
{
private:
	//草方块侧面的季节颜色叠加
	static void render_grass_block_sides_season_color(unsigned long base, bool open) noexcept;
	
public:
	using _getTextureFuncType = TextureUVCoordinateSet* (*)(BlockTessellator*, Block*, const BlockPos*, signed char);
	static _getTextureFuncType _getTextureOrig;

	static bool is_flat_mode(BlockTessellator* this_ptr) noexcept;
	static void set_flat_mode(BlockTessellator* this_ptr, bool mode) noexcept;
	static TextureUVCoordinateSet* _getTexture(BlockTessellator* this_ptr, Block* block, const BlockPos* pos_in_world, signed char face);
	static void install(void* handler, unsigned long base) noexcept;
};

#endif
