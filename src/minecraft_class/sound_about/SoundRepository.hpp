//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SOUND_ABOUT_SOUNDREPOSITORY_HPP
#define MINECRAFT_CLASS_SOUND_ABOUT_SOUNDREPOSITORY_HPP

#include "minecraft_class/sound_about/SoundEvent.hpp"
#include <string>

class SoundRepository
{
private:
	static void add_impl(
		SoundRepository* this_ptr,
		const std::string* name,
		const SoundEvent* sound_event
	);
	
public:
	using add_type = void(*)(
		SoundRepository*,
		const std::string*,
		const SoundEvent*
	);
	static add_type add_orig;

	void add(const std::string& name, const SoundEvent& event) noexcept;

	static void install() noexcept;
};

#endif
