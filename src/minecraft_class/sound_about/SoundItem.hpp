//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SOUND_ABOUT_SOUNDITEM_HPP
#define MINECRAFT_CLASS_SOUND_ABOUT_SOUNDITEM_HPP

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

#endif
