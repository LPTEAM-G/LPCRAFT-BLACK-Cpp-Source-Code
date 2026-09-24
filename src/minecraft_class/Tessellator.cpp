#include "Tessellator.hpp"
#include "mce/PrimitiveMode.hpp"
#include "minecraft_app.hpp"

Tessellator* Tessellator::get_instance() noexcept
{
	return minecraft_app::get_lib_global_variable_ptr<Tessellator>(0x75F2B8);
}

Tessellator* Tessellator::begin(mce::PrimitiveMode mode, int count) noexcept
{
	using begin_type = Tessellator*(*)(Tessellator*, mce::PrimitiveMode, int);
	begin_type begin_orig = (begin_type)minecraft_app::get_lib_thumb_function_ptr(0x44FB80);
	return begin_orig(this, mode, count);
}

Tessellator* Tessellator::begin(int count) noexcept
{
	return this->begin((mce::PrimitiveMode)1, count);
}
