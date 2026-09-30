//Copyright (c) 2026 LPTEAM
#pragma once

#include <memory>
#include <string>
#include <vector>

class UIControl
{
public:
	using vector_controls = std::vector<std::shared_ptr<UIControl>>;

	std::string& get_name() noexcept;
	void set_visible(bool visible_flag) noexcept;
	vector_controls& get_children() noexcept;
};
