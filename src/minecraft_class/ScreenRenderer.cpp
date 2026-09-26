#include "ScreenRenderer.hpp"
#include "mce/MaterialPtr.hpp"
#include "minecraft_app.hpp"

ScreenRenderer::ScreenRenderer() noexcept {}

mce::MaterialPtr* ScreenRenderer::get_screen_material(int index) noexcept
{
	auto array = minecraft_app::get_lib_global_variable_ptr<mce::MaterialPtr>(0x75D8D0);
	return array + index;
}

