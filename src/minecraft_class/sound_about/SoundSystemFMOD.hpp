//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>

class SoundSystemFMOD
{
private:
	static void load_impl(
		SoundSystemFMOD* this_ptr,
		const std::string* name,
		bool stream,
		bool is_3d,
		float min_distance
	);
	
public:
	using load_type = void(*)(
		SoundSystemFMOD*,
		const std::string*,
		bool,
		bool,
		float
	);
	static load_type load_orig;

	void load(
		const std::string& name,
		bool stream,
		bool is_3d,
		float min_distance
	) noexcept;

	std::string& get_music_base_path() noexcept;

	static void install() noexcept;
};

