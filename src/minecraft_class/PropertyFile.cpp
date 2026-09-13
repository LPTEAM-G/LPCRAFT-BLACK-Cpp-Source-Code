#include "PropertyFile.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/OptionStrings.hpp"
#include "minecraft_class/Options.hpp"
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

void PropertyFile::read_properties_from_file(vector_prop* properties, Options* options)
{
	
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
}
