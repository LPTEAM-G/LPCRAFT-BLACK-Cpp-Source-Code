//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/options_about/Options.hpp"
#include "minecraft_class/sound_about/SoundRepository.hpp"
#include "minecraft_class/sound_about/SoundSystemFMOD.hpp"
#include <string>

class SoundEngine
{
public:
	using constructor_type = void(*)(SoundEngine*, Options*);
	static constructor_type constructor_orig;

	static void constructor(SoundEngine* this_ptr, Options* options);
	void load_music_pack(const std::string& path) noexcept;

	SoundSystemFMOD* get_sound_system_fmod() noexcept;
	SoundRepository* get_sound_repository() noexcept;

	static void install() noexcept;
};

