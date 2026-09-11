//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_MATERIAL_HPP
#define MINECRAFT_CLASS_MATERIAL_HPP

#include "minecraft_class/MaterialType.hpp"

class Material
{
public:
	MaterialType get_type() noexcept;
	bool is_type(MaterialType type) noexcept;
};

#endif
