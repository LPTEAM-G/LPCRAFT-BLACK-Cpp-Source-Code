//Copyright (c) 2026 LPTEAM
#include "Material.hpp"
#include "minecraft_class/MaterialType.hpp"

MaterialType Material::get_type(Material* this_ptr) noexcept
{
	return *((MaterialType*)this_ptr);
}

bool Material::isType(Material* this_ptr, MaterialType type) noexcept
{
	return (int)type == 35 or get_type(this_ptr) == type;
}
