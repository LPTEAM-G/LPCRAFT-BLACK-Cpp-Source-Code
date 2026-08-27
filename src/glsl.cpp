#include "glsl.hpp"
#include <dlfcn.h>
#include <EGL/egl.h>

constexpr gl_enum glsl::lequal;
constexpr gl_enum glsl::always;
constexpr gl_enum glsl::src_alpha;
constexpr gl_enum glsl::one_minus_src_alpha;

glsl::depth_mask_type glsl::depth_mask = nullptr;
glsl::depth_func_type glsl::depth_func = nullptr;
glsl::blend_func_type glsl::blend_func = nullptr;
glsl::depth_rangef_type glsl::depth_rangef = nullptr;

void glsl::install() noexcept
{
	depth_mask = (depth_mask_type)eglGetProcAddress("glDepthMask");
	depth_func = (depth_func_type)eglGetProcAddress("glDepthFunc");
	blend_func = (blend_func_type)eglGetProcAddress("glBlendFunc");
	depth_rangef = (depth_rangef_type)eglGetProcAddress("glDepthRangef");
}
