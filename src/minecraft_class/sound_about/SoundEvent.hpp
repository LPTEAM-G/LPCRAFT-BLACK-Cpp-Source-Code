//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/sound_about/SoundItem.hpp"
#include <string>
#include <vector>

struct SoundEvent
{
	std::string category;
	std::vector<SoundItem> sounds;
};

static_assert(
	sizeof(SoundEvent) == 16,
	"SoundItem must be 16 bytes in size"
);

