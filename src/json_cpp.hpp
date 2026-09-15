//Copyright (c) 2026 LPTEAM
//对MCPE中已经使用的JsonCpp的二次封装
#ifndef JSON_CPP_HPP
#define JSON_CPP_HPP

#include <string>
#include <vector>
namespace json_cpp
{
	class value
	{
	private:
		alignas(8) char paddings[20];

	public:
		value(int type = 0);
		int size() const;
		std::vector<std::string> get_member_names() const;
		bool is_member(const std::string& name) const;
		bool is_string() const;
		bool is_null() const;
		bool is_bool() const;
		bool is_array() const;
		bool is_object() const;
		std::string as_string(const std::string& default_value = "") const;
		bool as_bool(bool default_value = false) const;
		value& operator[](int index);
		value& operator[](const std::string& name);
		~value() noexcept;
	};

	class reader
	{
	private:
		alignas(8) char paddings[116];

	public:
		reader();
		bool parse(
			const std::string& json_text,
			value& root,
			bool collect_comments
		);
		~reader() noexcept;
	};
}

#endif
