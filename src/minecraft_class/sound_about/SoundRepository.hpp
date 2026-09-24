//Copyright (c) 2026 LPTEAM
#pragma once

#include "minecraft_class/sound_about/SoundEvent.hpp"
#include <string>

class SoundRepository
{
public:
	void add(const std::string& name, const SoundEvent& event) noexcept;
};
