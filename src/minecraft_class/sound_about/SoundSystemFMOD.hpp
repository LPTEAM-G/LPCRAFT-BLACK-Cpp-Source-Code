//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>

class SoundSystemFMOD
{
public:
	void load(
		const std::string& name,
		bool stream,
		bool is_3d,
		float min_distance
	) noexcept;

	std::string& get_music_base_path() noexcept;
};
