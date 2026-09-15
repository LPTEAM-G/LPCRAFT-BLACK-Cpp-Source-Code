//Copyright (c) 2026 LPTEAM
#include "OptionsPane.hpp"
#include <cstdint>

OptionsPane::vector_group& OptionsPane::get_groups() noexcept
{
	return *(vector_group*)((uintptr_t)this + 48);
}
