//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SOUND_ABOUT_SOUNDENGINE_HPP
#define MINECRAFT_CLASS_SOUND_ABOUT_SOUNDENGINE_HPP

#include "minecraft_class/options_about/Options.hpp"
#include "minecraft_class/sound_about/SoundRepository.hpp"
#include "minecraft_class/sound_about/SoundSystemFMOD.hpp"

class SoundEngine
{
public:
	using constructor_type = void(*)(SoundEngine*, Options*);
	static constructor_type constructor_orig;

	static void constructor(SoundEngine* this_ptr, Options* options);

	SoundSystemFMOD* get_sound_system_fmod() noexcept;
	SoundRepository* get_sound_repository() noexcept;

	static void install() noexcept;
};

#endif
