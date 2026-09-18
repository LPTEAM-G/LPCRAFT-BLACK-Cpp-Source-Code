//Copyright (c) 2026 LPTEAM
#include "SoundSystemFMOD.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include <cstdint>
#include <string>

SoundSystemFMOD::load_type SoundSystemFMOD::load_orig = nullptr;

void SoundSystemFMOD::load_impl(
	SoundSystemFMOD* this_ptr,
	const std::string* name,
	bool stream,
	bool is_3d,
	float min_distance)
{
	load_orig(this_ptr, name, stream, is_3d, min_distance);
}

void SoundSystemFMOD::load(
	const std::string& name,
	bool stream,
	bool is_3d,
	float min_distance) noexcept
{
	load_impl(this, &name, stream, is_3d, min_distance);
}

std::string& SoundSystemFMOD::get_music_base_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 4);
}

void SoundSystemFMOD::install() noexcept
{
	void* load_target = minecraft_app::get_lib_thumb_function_ptr(0x2C634C);
	MSHook(load_target, load_impl, load_orig);
}
