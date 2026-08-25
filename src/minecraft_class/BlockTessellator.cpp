#include "BlockTessellator.hpp"
#include "tools.hpp"
#include <asm-generic/mman-common.h>
#include <bits/sysconf.h>
#include <cstring>
#include <dlfcn.h>
#include <sys/mman.h>

BlockTessellator::_getTextureFuncType BlockTessellator::_getTextureOrig = nullptr;

void BlockTessellator::render_grass_block_sides_season_color(unsigned long base, bool open) noexcept
{
	if (not open) return;

	//Hex value of command'movs r1, 0x0'
	//r1的类型是bool, 此处将其赋值为false
	//这使其不会随着方块状态的更新而更新, 从而导致莫名其妙的颜色丢失
	//它会被传递至AmbientOcclusionCalculator::setTintSides(this_ptr, bool)中
	uint16_t movs_r1_0x0 = 0x0021;

	//四侧渲染时的r1赋值
	void* r1_assign_place1 = (void*)(base + 0x39F75E);
	void* r1_assign_place2 = (void*)(base + 0x39F864);
	void* r1_assign_place3 = (void*)(base + 0x39F960);
	void* r1_assign_place4 = (void*)(base + 0x39FA50);

	long page_size = sysconf(_SC_PAGESIZE);
	void* page_start = (void*)((uintptr_t)r1_assign_place1 & ~(page_size - 1));

	mprotect(page_start, page_size, PROT_EXEC | PROT_READ | PROT_WRITE);

	memcpy(r1_assign_place1, (void*)&movs_r1_0x0, sizeof(movs_r1_0x0));
	__builtin___clear_cache((char*)r1_assign_place1, (char*)r1_assign_place1 + sizeof(movs_r1_0x0));
	memcpy(r1_assign_place2, (void*)&movs_r1_0x0, sizeof(movs_r1_0x0));
	__builtin___clear_cache((char*)r1_assign_place2, (char*)r1_assign_place2 + sizeof(movs_r1_0x0));
	memcpy(r1_assign_place3, (void*)&movs_r1_0x0, sizeof(movs_r1_0x0));
	__builtin___clear_cache((char*)r1_assign_place3, (char*)r1_assign_place3 + sizeof(movs_r1_0x0));
	memcpy(r1_assign_place4, (void*)&movs_r1_0x0, sizeof(movs_r1_0x0));
	__builtin___clear_cache((char*)r1_assign_place4, (char*)r1_assign_place4 + sizeof(movs_r1_0x0));

	mprotect(page_start, page_size, PROT_EXEC | PROT_READ);
}

bool BlockTessellator::is_flat_mode(BlockTessellator* this_ptr) noexcept
{
	return *(bool*)((unsigned char*)this_ptr + 40);
}

void BlockTessellator::set_flat_mode(BlockTessellator* this_ptr, bool mode) noexcept
{
	*(bool*)((unsigned char*)this_ptr + 40) = mode;
}

TextureUVCoordinateSet* BlockTessellator::_getTexture(BlockTessellator* this_ptr, Block* block, const BlockPos* pos_in_world, signed char face)
{
	return _getTextureOrig(this_ptr, block, pos_in_world, face);
}

void BlockTessellator::install(void* handler, unsigned long base) noexcept
{
	void* _getTextureTarget = dlsym(handler,"_ZNK16BlockTessellator11_getTextureER5BlockRK8BlockPosa");
	MSHook(_getTextureTarget, _getTexture, _getTextureOrig);
	render_grass_block_sides_season_color(base, true);
}
