//Copyright (c) 2026 LPTEAM
#include "SoundSystemFMOD.hpp"
#include "minecraft_app.hpp"
#include <cstdint>
#include <string>

void SoundSystemFMOD::load(
	const std::string& name,
	bool stream,
	bool is_3d,
	float min_distance) noexcept
{
	using load_type = void(*)(
		SoundSystemFMOD*,
		const std::string*,
		bool, bool,
		float
	);
	load_type load_orig = (load_type)minecraft_app::get_lib_thumb_function_ptr(0x2C634C);
	load_orig(this, &name, stream, is_3d, min_distance);
}

std::string& SoundSystemFMOD::get_music_base_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 4);
}
