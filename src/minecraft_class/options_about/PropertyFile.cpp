//Copyright (c) 2026 LPTEAM
#include "PropertyFile.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "OptionStrings.hpp"
#include "Options.hpp"
#include <string>

PropertyFile::save_properties_to_file_type PropertyFile::save_properties_to_file_orig = nullptr;
PropertyFile::read_properties_from_file_type PropertyFile::read_properties_from_file_orig = nullptr;

void PropertyFile::save_boolean_key(const vector_prop* properties, const std::string* key, bool value) noexcept
{
	using save_boolean_key_type = void(*)(const vector_prop*, const std::string*, bool);
	save_boolean_key_type save_boolean_key_orig =
		(save_boolean_key_type)minecraft_app::get_lib_thumb_function_ptr(0x3E6604);
	save_boolean_key_orig(properties, key, value);
}

void PropertyFile::save_properties_to_file(const std::string* path, const vector_prop* properties)
{
	save_boolean_key(properties, &OptionStrings::Graphics_UseCenteredGUI, Options::opt_vars::use_centered_gui);
	save_properties_to_file_orig(path, properties);
}

void PropertyFile::read_properties_from_file(PropertyFile* properties, Options* options)
{
	read_properties_from_file_orig(properties, options);
	for (auto& prop : properties->props)
	{
		if (prop.key == OptionStrings::Graphics_UseCenteredGUI)
			Options::opt_vars::use_centered_gui = (prop.value == "1");
	}
}

void PropertyFile::install() noexcept
{
	//_ZN12PropertyFile20savePropertiesToFileERKSsRKSt6vectorINS_8PropertyESaIS3_EE
	void* save_properties_to_file_target = minecraft_app::get_lib_thumb_function_ptr(0x38FFF8);
	MSHook(
		save_properties_to_file_target,
		save_properties_to_file,
		save_properties_to_file_orig
	);

	//_ZN12PropertyFile22readPropertiesFromFileERKSs
	void* read_properties_from_file_target = minecraft_app::get_lib_thumb_function_ptr(0x3E8B98);
	MSHook(
		read_properties_from_file_target,
		read_properties_from_file,
		read_properties_from_file_orig
	);
}
