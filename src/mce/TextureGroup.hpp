//Copyright (c) 2026 LPTEAM
#pragma once

#include "mce/TexturePtr.hpp"
#include <string>

namespace mce
{
	class TextureGroup
	{
	public:
		mce::TexturePtr get_texture(const std::string& path, bool location);
	};
}
