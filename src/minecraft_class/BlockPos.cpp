//Copyright (c) 2026 LPTEAM
#include "BlockPos.hpp"
#include "glm/type_vec3.hpp"
#include <cmath>

BlockPos::BlockPos(const glm::vec3& pos) noexcept:
	x(floorf(pos.x)),
	y(floorf(pos.y)),
	z(floorf(pos.z))
{}
