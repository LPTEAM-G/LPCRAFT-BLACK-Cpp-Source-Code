//Copyright (c) 2026 LPTEAM
#pragma  once

#include <string>

class Font
{
public:
	float get_line_length(
		const std::string& text,
		float result_scale,
		bool count_format_codes
	) noexcept;
};
