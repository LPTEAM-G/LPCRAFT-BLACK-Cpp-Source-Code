#include "GuiData.hpp"
#include "minecraft_app.hpp"

float GuiData::get_gui_scale() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<float>(0x75B16C);
}

float GuiData::get_inv_gui_scale() noexcept
{
	return *minecraft_app::get_lib_global_variable_ptr<float>(0x75D928);
}
