//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/MaterialType.hpp"

class Material
{
public:
	MaterialType get_type() noexcept;
	bool is_type(MaterialType type) noexcept;
};

