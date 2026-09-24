//Copyright (c) 2026 LPTEAM
#include "SoundRepository.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/sound_about/SoundEvent.hpp"
#include <string>

void SoundRepository::add(const std::string& name, const SoundEvent& event) noexcept
{
	using add_type = void(*)(SoundRepository*, const std::string*, const SoundEvent*);
	add_type add_orig = (add_type)minecraft_app::get_lib_thumb_function_ptr(0x2C67E4);
	add_orig(this, &name, &event);
}
