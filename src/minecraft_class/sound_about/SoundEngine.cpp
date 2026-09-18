//Copyright (c) 2026 LPTEAM
#include "SoundEngine.hpp"
#include "hook_macro.hpp"
#include "json_cpp.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform_android.hpp"
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <ios>
#include <sstream>
#include <string>
#include <vector>
#include "minecraft_class/sound_about/SoundEvent.hpp"
#include "minecraft_class/sound_about/SoundItem.hpp"
#include "minecraft_class/sound_about/SoundRepository.hpp"
#include "minecraft_class/sound_about/SoundSystemFMOD.hpp"

SoundEngine::constructor_type SoundEngine::constructor_orig = nullptr;

void SoundEngine::constructor(SoundEngine* this_ptr, Options* options)
{
	constructor_orig(this_ptr, options);

	std::string music_pack_path =
		AppPlatform_android::get_instance()->get_user_data_path() +
		"music_pack/";
	this_ptr->load_music_pack(music_pack_path);
}

void SoundEngine::load_music_pack(const std::string& path) noexcept
{
	SoundSystemFMOD* fmod = get_sound_system_fmod();
	SoundRepository* repository = get_sound_repository();
	fmod->get_music_base_path() = path;
	std::string json_path = path + "music.json";
	
	json_cpp::reader reader;
	json_cpp::value root;

	auto read_file_to_string = [](const std::string& path) -> std::string
	{
		std::ifstream file{path, std::ios::binary};
		if (not file) return "";

		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	};

	std::string json_text = read_file_to_string(json_path);
	bool successfully = reader.parse(json_text, root, true);
	if (not successfully)
		return;

	if (not root.is_object())
		return;
	
	std::vector<std::string> music_event_names = root.get_member_names();
	std::vector<SoundEvent> music_events;
	
	for (const auto& event_name : music_event_names)
	{
		json_cpp::value& music_item_array = root[event_name];
		if (not music_item_array.is_array())
			continue;

		SoundEvent music_event{"music", {}};
		for (int index = 0; index < music_item_array.size(); ++index)
		{
			json_cpp::value& music_name = music_item_array[index];
			if (not music_name.is_string())
				continue;
			
			SoundItem music_item = SoundItem
			{
				.name = music_name.as_string(),
				.volume = 1.0f,
				.stream = true,
				.is_3d = true,
				.min_distance = 0.0f
			};

			music_event.sounds.push_back(std::move(music_item));
		}
		repository->add(event_name, music_event);
		music_events.push_back(std::move(music_event));
	}

	for (const auto& event : music_events)
	{
		for (const auto& music_item : event.sounds)
		{
			fmod->load(
				music_item.name,
				music_item.stream,
				music_item.is_3d,
				music_item.min_distance
			);
		}
	}
}

SoundSystemFMOD* SoundEngine::get_sound_system_fmod() noexcept
{
	return (SoundSystemFMOD*)((uintptr_t)this + 4);
}

SoundRepository* SoundEngine::get_sound_repository() noexcept
{
	return (SoundRepository*)((uintptr_t)this + 120);
}

void SoundEngine::install() noexcept
{
	//_ZN11SoundEngineC1ER7Options
	void* constructor_target = minecraft_app::get_lib_thumb_function_ptr(0x48A57C);
	MSHook(constructor_target, constructor, constructor_orig);
}
