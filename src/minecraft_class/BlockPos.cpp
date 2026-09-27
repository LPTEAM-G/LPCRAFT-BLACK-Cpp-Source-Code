//Copyright (c) 2026 LPTEAM
#include "BlockPos.hpp"
#include "minecraft_class/Vec3.hpp"
#include <cmath>

BlockPos::BlockPos(const Vec3& pos) noexcept:
	x(floorf(pos.x)),
	y(floorf(pos.y)),
	z(floorf(pos.z))
{}
