//Copyright (c) 2026 LPTEAM
#include "SoundRepository.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/sound_about/SoundEvent.hpp"
#include <string>

SoundRepository::add_type SoundRepository::add_orig = nullptr;

void SoundRepository::add_impl(
	SoundRepository* this_ptr,
	const std::string* name,
	const SoundEvent *sound_event)
{
	add_orig(this_ptr, name, sound_event);
}

void SoundRepository::add(const std::string& name, const SoundEvent& event) noexcept
{
	add_impl(this, &name, &event);
}

void SoundRepository::install() noexcept
{
	void* add_target = minecraft_app::get_lib_thumb_function_ptr(0x2C67E4);
	MSHook(add_target, add_impl, add_orig);
}
