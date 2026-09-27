//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/AABB.hpp"
#include "minecraft_class/Vec3.hpp"

class Entity
{
public:
	const Vec3& get_pos() const noexcept;
	const AABB& get_AABB() const noexcept;
};
