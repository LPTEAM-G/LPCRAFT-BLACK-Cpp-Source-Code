#pragma once

#include "mce/MaterialPtr.hpp"
#include "mce/PrimitiveMode.hpp"
#include "mce/TexturePtr.hpp"
#include "minecraft_class/Color.hpp"

class Tessellator
{
public:
	static Tessellator& get_instance() noexcept;
	
	Tessellator& begin(mce::PrimitiveMode type, int count) noexcept;
	Tessellator& begin(int count) noexcept;
	Tessellator& color(const Color& color) noexcept;
	void draw(mce::MaterialPtr& material, mce::TexturePtr& texture);

	Tessellator(const Tessellator&) = delete;
	Tessellator(Tessellator&&) = delete;
	Tessellator& operator=(const Tessellator&) = delete;
	Tessellator& operator=(Tessellator&&) = delete;
};
