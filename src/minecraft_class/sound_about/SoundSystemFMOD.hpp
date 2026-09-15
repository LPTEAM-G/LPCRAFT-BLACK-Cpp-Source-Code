//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SOUND_ABOUT_SOUNDSYSTEMFMOD_HPP
#define MINECRAFT_CLASS_SOUND_ABOUT_SOUNDSYSTEMFMOD_HPP

#include <string>

class SoundSystemFMOD
{
public:
	using load_type = void(*)(
		SoundSystemFMOD*,
		const std::string*,
		bool,
		bool,
		float
	);
	static load_type load_orig;

	static void load(
		SoundSystemFMOD* this_ptr,
		const std::string* name,
		bool stream,
		bool is_3d,
		float min_distance
	);

	std::string& get_music_base_path() noexcept;

	static void install() noexcept;
};

#endif
