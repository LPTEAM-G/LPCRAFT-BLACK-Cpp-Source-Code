#include "GuiElement.hpp"
#include <cstdint>

bool GuiElement::is_not_locked() noexcept
{
	return *(bool*)((uintptr_t)this + 4);
}

void GuiElement::set_is_not_locked(bool flag) noexcept
{
	*(bool*)((uintptr_t)this + 4) = flag;
}
