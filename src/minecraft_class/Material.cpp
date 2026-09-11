//Copyright (c) 2026 LPTEAM
#include "Material.hpp"
#include "minecraft_class/MaterialType.hpp"

MaterialType Material::get_type() noexcept
{
	return *((MaterialType*)this);
}

bool Material::is_type(MaterialType type) noexcept
{
	return (int)type == 35 or this->get_type() == type;
}
