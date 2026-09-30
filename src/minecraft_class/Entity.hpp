//Copyright (c) 2026 LPTEAM
#pragma once

#include "glm/type_vec3.hpp"
#include "minecraft_class/AABB.hpp"

class Entity
{
public:
	const glm::vec3& get_pos() const noexcept;
	const AABB& get_AABB() const noexcept;
};
