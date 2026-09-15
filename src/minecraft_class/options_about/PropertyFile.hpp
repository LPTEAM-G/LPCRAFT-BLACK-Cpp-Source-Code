//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_OPTIONS_ABOUT_PROPERTYFILE_HPP
#define MINECRAFT_CLASS_OPTIONS_ABOUT_PROPERTYFILE_HPP

#include "Options.hpp"
#include <string>
#include <vector>

class PropertyFile
{
public:
	struct Property
	{
		std::string key;
		std::string value;
	};

	using vector_prop = std::vector<PropertyFile::Property>;
	vector_prop props;

	using save_properties_to_file_type = void(*)(const std::string*, const vector_prop*);
	static save_properties_to_file_type save_properties_to_file_orig;

	using read_properties_from_file_type = void(*)(PropertyFile*, Options*);
	static read_properties_from_file_type read_properties_from_file_orig;

	static void save_boolean_key(const vector_prop* properties, const std::string* key, bool value) noexcept;

	static void save_properties_to_file(const std::string* path, const vector_prop* properties);
	static void read_properties_from_file(PropertyFile* properties, Options* options);

	static void install() noexcept;
};

#endif
