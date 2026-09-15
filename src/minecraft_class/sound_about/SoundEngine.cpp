//Copyright (c) 2026 LPTEAM
#include "SoundEngine.hpp"
#include "hook_macro.hpp"
#include "json_cpp.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/AppPlatform.hpp"
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
	
	json_cpp::reader reader;
	json_cpp::value root;

	//加载自定义音乐包
	std::string music_pack_dir =
		AppPlatform::get_instance_as_android_derived()->get_user_data_path() +
		"music_pack/";
	std::string music_json_path = music_pack_dir + "music.json";

	auto read_file_to_string = [](const std::string& path) -> std::string
	{
		std::ifstream file{path, std::ios::binary};
		if (not file) return "";

		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	};

	std::string json_text = read_file_to_string(music_json_path);
	bool result = reader.parse(json_text, root, true);

	if (not root.is_object()) return;
	
	auto names = root.get_member_names();
	std::vector<SoundEvent> events;
	for (const auto& event_name : names)
	{
		SoundEvent event;
		json_cpp::value& music_place_object = root[event_name];
		if (not music_place_object.is_object())
			continue;
		
		if (
			not music_place_object.is_member("category") or
			not music_place_object.is_member("sounds"))
			continue;
		std::string category = music_place_object["category"].as_string();
		if (category != "music")
			continue;
		event.category = category;
		//category不是ui时为true
		bool is_3d = true;

		json_cpp::value& sound_array = music_place_object["sounds"];
		if (not sound_array.is_array())
			continue;
		auto sound_count = sound_array.size();

		for (int index = 0; index < sound_count; ++index)
		{
			json_cpp::value& sound_object = sound_array[index];
			SoundItem item;
			item.is_3d = is_3d;
			item.min_distance = 0.0;
			if (
				not sound_object.is_object() or
				not sound_object.is_member("name") or
				not sound_object.is_member("stream")
			)
				continue;

			item.name = sound_object["name"].as_string();
			item.stream = sound_object["stream"].as_bool();
			item.volume = 1.0f;

			event.sounds.push_back(item);
		}
		events.push_back(event);
		SoundRepository::add(
			this_ptr->get_sound_repository(),
			&event_name,
			&event
		);
	}

	for (const auto& event : events)
	{
		for (const auto& item : event.sounds)
		{
			SoundSystemFMOD::load(
				this_ptr->get_sound_system_fmod(),
				&item.name,
				item.stream,
				item.is_3d,
				item.min_distance
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
