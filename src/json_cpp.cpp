//Copyright (c) 2026 LPTEAM
#include "json_cpp.hpp"
#include "minecraft_app.hpp"
#include <string>
#include <vector>

namespace json_cpp
{
	value::value(int type)
	{
		using func_type = void(*)(value*, int);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2D9944);
		func(this, type);
	}

	value::~value() noexcept
	{
		using func_type = void(*)(value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x308A80);
		func(this);
	}

	int value::size() const
	{
		using func_type = int(*)(const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA280);
		return func(this);
	}

	std::vector<std::string> value::get_member_names() const
	{
		using func_type = void(*)(std::vector<std::string>*, const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x311604);
		std::vector<std::string> names;
		func(&names, this);
		return names;
	}

	bool value::is_member(const  std::string& name) const
	{
		using func_type = bool(*)(const value*, const std::string*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA414);
		return func(this, &name);
	}

	bool value::is_string() const
	{
		using func_type = bool(*)(const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA488);
		return func(this);
	}

	bool value::is_null() const
	{
		using func_type = bool(*)(const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA41C);
		return func(this);
	}

	bool value::is_bool() const
	{
		using func_type = bool(*)(const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA42C);
		return func(this);
	}

	bool value::is_object() const
	{
		using func_type = bool(*)(const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA6F4);
		return func(this);
	}

	bool value::is_array() const
	{
		using func_type = bool(*)(const value*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA6E4);
		return func(this);
	}

	std::string value::as_string(const std::string& default_value) const
	{
		using func_type = void(*)(std::string*, const value*, const std::string*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2D9E00);
		std::string str;
		func(&str, this, &default_value);
		return str;
	}

	bool value::as_bool(bool default_value) const
	{
		using func_type = bool(*)(const value*, bool);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA0B4);
		return func(this, default_value);
	}

	value& value::operator[](int index)
	{
		using func_type = value*(*)(value*, int);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x31A40C);
		return *func(this, index);
	}

	value& value::operator[](const std::string& name)
	{
		using func_type = value*(*)(value*, const std::string*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x31A4F4);
		return *func(this, &name);
	}

	reader::reader()
	{
		using func_type = void(*)(reader*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2D880C);
		func(this);
	}

	reader::~reader() noexcept
	{
		using func_type = void(*)(reader*);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x2C4ADC);
		func(this);
	}

	bool reader::parse(
		const std::string& json_text,
		value& root,
		bool collect_comments)
	{
		using func_type = bool(*)(reader*, const std::string*, value*, bool);
		func_type func = (func_type)minecraft_app::get_lib_thumb_function_ptr(0x3519F8);
		return func(this, &json_text, &root, collect_comments);
	}
}
