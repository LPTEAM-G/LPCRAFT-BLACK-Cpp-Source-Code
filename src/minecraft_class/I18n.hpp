//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>
#include <vector>

class I18n
{
public:
	static std::string get(const std::string& key, const std::vector<std::string>& args);
};
