#ifndef MINECRAFT_CLASS_PROPERTYFILE_HPP
#define MINECRAFT_CLASS_PROPERTYFILE_HPP

#include "minecraft_class/Options.hpp"
#include <string>
#include <vector>

namespace PropertyFile
{
	struct Property
	{
		std::string key;
		std::string value;
	};

	using vector_prop = std::vector<PropertyFile::Property>;

	using save_properties_to_file_type = void(*)(const std::string*, const vector_prop*);
	extern save_properties_to_file_type save_properties_to_file_orig;

	using read_properties_from_file_type = void(*)(vector_prop*, Options*);
	extern read_properties_from_file_type read_properties_from_file_orig;

	void save_boolean_key(const vector_prop* properties, const std::string* key, bool value) noexcept;

	void save_properties_to_file(const std::string* path, const vector_prop* properties);
	void read_properties_from_file(vector_prop* properties, Options* options);

	void install() noexcept;
}

#endif
