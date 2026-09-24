//Copyright (c) 2026 LPTEAM
#include "json_cpp.hpp"
#include "minecraft_app.hpp"
#include <string>
#include <vector>

namespace json_cpp
{
	value::value(int type)
	{
		using constructor_type = void(*)(value*, int);
		constructor_type constructor_orig = (constructor_type)minecraft_app::get_lib_thumb_function_ptr(0x2D9944);
		constructor_orig(this, type);
	}

	value::~value() noexcept
	{
		using destructor_type = void(*)(value*);
		destructor_type destructor_orig = (destructor_type)minecraft_app::get_lib_thumb_function_ptr(0x308A80);
		destructor_orig(this);
	}

	int value::size() const
	{
		using size_func_type = int(*)(const value*);
		size_func_type size_orig = (size_func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA280);
		return size_orig(this);
	}

	std::vector<std::string> value::get_member_names() const
	{
		using get_member_names_type = void(*)(std::vector<std::string>*, const value*);
		get_member_names_type get_member_names_orig = (get_member_names_type)minecraft_app::get_lib_thumb_function_ptr(0x311604);
		std::vector<std::string> names;
		get_member_names_orig(&names, this);
		return names;
	}

	bool value::is_member(const  std::string& name) const
	{
		using is_member_type = bool(*)(const value*, const std::string*);
		is_member_type is_member_orig = (is_member_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA414);
		return is_member_orig(this, &name);
	}

	bool value::is_string() const
	{
		using is_string_func_type = bool(*)(const value*);
		is_string_func_type is_string_orig = (is_string_func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA488);
		return is_string_orig(this);
	}

	bool value::is_null() const
	{
		using is_null_func_type = bool(*)(const value*);
		is_null_func_type is_null_orig = (is_null_func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA41C);
		return is_null_orig(this);
	}

	bool value::is_bool() const
	{
		using is_bool_func_type = bool(*)(const value*);
		is_bool_func_type is_bool_orig = (is_bool_func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA42C);
		return is_bool_orig(this);
	}

	bool value::is_object() const
	{
		using is_object_func_type = bool(*)(const value*);
		is_object_func_type is_object_orig = (is_object_func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA6F4);
		return is_object_orig(this);
	}

	bool value::is_array() const
	{
		using is_array_func_type = bool(*)(const value*);
		is_array_func_type is_array_orig = (is_array_func_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA6E4);
		return is_array_orig(this);
	}

	std::string value::as_string(const std::string& default_value) const
	{
		using as_string_type = void(*)(std::string*, const value*, const std::string*);
		as_string_type as_string_orig = (as_string_type)minecraft_app::get_lib_thumb_function_ptr(0x2D9E00);
		std::string str;
		as_string_orig(&str, this, &default_value);
		return str;
	}

	bool value::as_bool(bool default_value) const
	{
		using as_bool_type = bool(*)(const value*, bool);
		as_bool_type as_bool_orig = (as_bool_type)minecraft_app::get_lib_thumb_function_ptr(0x2DA0B4);
		return as_bool_orig(this, default_value);
	}

	value& value::operator[](int index)
	{
		using operator_overload_func_type = value*(*)(value*, int);
		operator_overload_func_type operator_overload_orig = (operator_overload_func_type)minecraft_app::get_lib_thumb_function_ptr(0x31A40C);
		return *operator_overload_orig(this, index);
	}

	value& value::operator[](const std::string& name)
	{
		using operator_overload_func_type = value*(*)(value*, const std::string*);
		operator_overload_func_type operator_overload_orig = (operator_overload_func_type)minecraft_app::get_lib_thumb_function_ptr(0x31A4F4);
		return *operator_overload_orig(this, &name);
	}

	reader::reader()
	{
		using constructor_type = void(*)(reader*);
		constructor_type constructor_orig = (constructor_type)minecraft_app::get_lib_thumb_function_ptr(0x2D880C);
		constructor_orig(this);
	}

	reader::~reader() noexcept
	{
		using destructor_type = void(*)(reader*);
		destructor_type destructor_orig = (destructor_type)minecraft_app::get_lib_thumb_function_ptr(0x2C4ADC);
		destructor_orig(this);
	}

	bool reader::parse(
		const std::string& json_text,
		value& root,
		bool collect_comments)
	{
		using parse_type = bool(*)(reader*, const std::string*, value*, bool);
		parse_type parse_orig = (parse_type)minecraft_app::get_lib_thumb_function_ptr(0x3519F8);
		return parse_orig(this, &json_text, &root, collect_comments);
	}
}
