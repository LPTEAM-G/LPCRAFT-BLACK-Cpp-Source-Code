//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_AMBIENTOCCLUSIONCALCULATOR_HPP
#define MINECRAFT_CLASS_AMBIENTOCCLUSIONCALCULATOR_HPP

//向前声明
#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
class BlockTessellator;

class AmbientOcclusionCalculator
{	
public:
	using calculateType = int(*)(AmbientOcclusionCalculator*, signed char face, bool);
	static calculateType calculateOrig;

	BlockTessellator* get_BlockTessellator_ptr() noexcept;
	Block* get_block() noexcept;
	BlockPos* get_block_pos() noexcept;
	void set_tint_sides(bool should_set) noexcept;
	static int calculate(AmbientOcclusionCalculator* this_ptr, signed char face, bool flag);

	static void install() noexcept;
};

#endif
