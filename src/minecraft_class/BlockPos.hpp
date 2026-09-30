//Copyright (c) 2026 LPTEAM
#pragma once

#include "glm/type_vec3.hpp"

struct BlockPos
{
	int x;
	int y;
	int z;

	BlockPos(const glm::vec3& pos) noexcept;
};
