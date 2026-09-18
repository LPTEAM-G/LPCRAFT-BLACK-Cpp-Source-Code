//Copyright (c) 2026 LPTEAM
#include "Block.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/Material.hpp"
#include "minecraft_class/TextureUVCoordinateSet.hpp"
#include <cstdint>

Block** Block::get_block_table() noexcept
{
	return minecraft_app::get_lib_global_variable_ptr<Block*>(0x7CAE6C);
}

Material* Block::get_material() noexcept
{
	return *((Material**)((uint32_t)this + 84));
}

TextureUVCoordinateSet* Block::get_texture_virtual(signed char face) noexcept
{
	using func_type = TextureUVCoordinateSet*(*)(Block*, signed char);
	void** vtable = *((void***)this);
	func_type vfunc = (func_type)(vtable[76]);
	return vfunc(this, face);
}
