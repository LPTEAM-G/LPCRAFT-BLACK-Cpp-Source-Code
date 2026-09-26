#include "TextureGroup.hpp"
#include "mce/TexturePtr.hpp"
#include "minecraft_app.hpp"
#include <string>

namespace mce
{
	TexturePtr TextureGroup::get_texture(const std::string& path, bool location)
	{
		using get_texture_type = void(*)(TexturePtr*, TextureGroup*, const std::string*, bool);
		get_texture_type get_texture_orig = (get_texture_type)minecraft_app::get_lib_thumb_function_ptr(0x327978);
		TexturePtr sret;
		get_texture_orig(&sret, this, &path, location);
		return sret;
	}
}
