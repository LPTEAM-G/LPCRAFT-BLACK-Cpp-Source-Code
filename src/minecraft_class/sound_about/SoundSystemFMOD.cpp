//Copyright (c) 2026 LPTEAM
#include "SoundSystemFMOD.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class//AppPlatform_android.hpp"
#include <cstdint>
#include <string>

SoundSystemFMOD::load_type SoundSystemFMOD::load_orig = nullptr;

void SoundSystemFMOD::load(
	SoundSystemFMOD* this_ptr,
	const std::string* name,
	bool stream,
	bool is_3d,
	float min_distance)
{
	std::string default_music_path =
		this_ptr->get_music_base_path();
	this_ptr->get_music_base_path() =
		AppPlatform::get_instance_as_android_derived()->get_user_data_path() +
		"music_pack/";
	load_orig(this_ptr, name, stream, is_3d, min_distance);
	this_ptr->get_music_base_path() = default_music_path;
}

std::string& SoundSystemFMOD::get_music_base_path() noexcept
{
	return *(std::string*)((uintptr_t)this + 4);
}

void SoundSystemFMOD::install() noexcept
{
	void* load_target = minecraft_app::get_lib_thumb_function_ptr(0x2C634C);
	MSHook(load_target, load, load_orig);
}
