#include "GuiComponent.hpp"
#include "minecraft_app.hpp"

GuiComponent::GuiComponent() noexcept:
	vtable((void**)minecraft_app::get_lib_vtable_address(0x6ECFB8))
{}
