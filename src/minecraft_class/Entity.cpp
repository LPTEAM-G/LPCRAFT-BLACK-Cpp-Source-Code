//Copyright (c) 2026 LPTEAM
#include "Entity.hpp"
#include "glm/type_vec3.hpp"
#include "minecraft_class/AABB.hpp"
#include <cstdint>

const glm::vec3& Entity::get_pos() const noexcept
{
	return *(glm::vec3*)((uintptr_t)this + 8);
}

const AABB& Entity::get_AABB() const noexcept
{
	return *(AABB*)((uintptr_t)this + 144);
}
