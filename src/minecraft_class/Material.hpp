//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_MATERIAL_HPP
#define MINECRAFT_CLASS_MATERIAL_HPP

#include "minecraft_class/MaterialType.hpp"

class Material
{
public:
	static MaterialType get_type(Material* this_ptr) noexcept;
	static bool isType(Material* this_ptr, MaterialType type) noexcept;
};

#endif
