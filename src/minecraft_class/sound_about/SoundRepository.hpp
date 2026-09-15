//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SOUND_ABOUT_SOUNDREPOSITORY_HPP
#define MINECRAFT_CLASS_SOUND_ABOUT_SOUNDREPOSITORY_HPP

#include "minecraft_class/sound_about/SoundEvent.hpp"
#include <string>

class SoundRepository
{
public:
	using add_type = void(*)(
		SoundRepository*,
		const std::string*,
		const SoundEvent*
	);
	static add_type add_orig;

	static void add(
		SoundRepository* this_ptr,
		const std::string* name,
		const SoundEvent* sound_event
	);

	static void install() noexcept;
};

#endif
