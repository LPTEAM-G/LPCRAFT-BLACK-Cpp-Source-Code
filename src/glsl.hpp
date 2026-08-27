#ifndef GLSL_HPP
#define GLSL_HPP

using gl_enum = unsigned int;
using gl_boolean = unsigned char;

constexpr gl_boolean gl_true = 1;
constexpr gl_boolean gl_false = 0;

class glsl
{
private:
	using depth_mask_type = void(*)(gl_boolean);
	using depth_func_type = void(*)(gl_enum);
	using blend_func_type = void(*)(gl_enum, gl_enum);
	using depth_rangef_type = void(*)(float, float);

public:
	static constexpr gl_enum lequal = 0x0203;
	static constexpr gl_enum always = 0x0207;
	static constexpr gl_enum src_alpha = 0x0302;
	static constexpr gl_enum one_minus_src_alpha = 0x0303;
	
	static depth_mask_type depth_mask;
	static depth_func_type depth_func;
	static blend_func_type blend_func;
	static depth_rangef_type depth_rangef;

	static void install() noexcept;
};

#endif
