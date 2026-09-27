//Copyright (c) 2026 LPTEAM
#include "Entity.hpp"
#include "minecraft_class/AABB.hpp"
#include "minecraft_class/Vec3.hpp"
#include <cstdint>

const Vec3& Entity::get_pos() const noexcept
{
	return *(Vec3*)((uintptr_t)this + 8);
}

const AABB& Entity::get_AABB() const noexcept
{
	return *(AABB*)((uintptr_t)this + 144);
}
