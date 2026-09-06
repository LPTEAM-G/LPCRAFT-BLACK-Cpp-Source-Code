//Copyright (c) 2026 LPTEAM
#include "AmbientOcclusionCalculator.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Block.hpp"
#include "minecraft_class/BlockPos.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/BlockTessellator.hpp"
#include <cstdint>
#include <hook_macro.hpp>

AmbientOcclusionCalculator::calculateType AmbientOcclusionCalculator::calculateOrig = nullptr;

BlockTessellator* AmbientOcclusionCalculator::get_block_tessellator() noexcept
{
	return (BlockTessellator*)(*(uintptr_t*)((uintptr_t)this + 28) - 772);
}

Block* AmbientOcclusionCalculator::get_block() noexcept
{
	return *(Block**)((uintptr_t)this + 36);
}

BlockPos* AmbientOcclusionCalculator::get_block_pos() noexcept
{
	return *(BlockPos**)((uintptr_t)this + 32);
}

void AmbientOcclusionCalculator::set_tint_sides(bool should_set) noexcept
{
	*((bool*)this) = should_set;
}

int AmbientOcclusionCalculator::calculate(AmbientOcclusionCalculator* this_ptr, signed char face, bool flag)
{
	if (face > 1)
	{
		this_ptr->set_tint_sides(true);
		Block* block = this_ptr->get_block();
		//如果是草方块
		if (block == Block::get_block_table()[2])
		{
			BlockTessellator* bt = this_ptr->get_block_tessellator();
			BlockSource* bs = bt->get_block_source();
			if (bs->is_snowed( this_ptr->get_block_pos()))
			{
				this_ptr->set_tint_sides(false);
			}
		}
	}
	
	int result = calculateOrig(this_ptr, face, flag);
	
	return result;
}

void AmbientOcclusionCalculator::install() noexcept
{
	//_ZN26AmbientOcclusionCalculator9calculateEab
	void* calculateTarget = minecraft_app::get_lib_thumb_function_ptr(0x39EEC4);
	MSHook(calculateTarget, calculate, calculateOrig);
}
