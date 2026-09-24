#pragma once

#include "mce/PrimitiveMode.hpp"
class Tessellator
{
public:
	static Tessellator* get_instance() noexcept;
	
	Tessellator* begin(mce::PrimitiveMode type, int count) noexcept;
	Tessellator* begin(int count) noexcept;
};
