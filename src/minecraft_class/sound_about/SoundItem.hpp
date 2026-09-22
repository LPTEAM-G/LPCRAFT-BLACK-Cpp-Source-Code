//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>

struct SoundItem
{
	std::string name;
	float volume;
	bool stream;
	bool is_3d;
	float min_distance;
};

static_assert(
	sizeof(SoundItem) == 16,
	"SoundItem must be 16 bytes in size"
);
