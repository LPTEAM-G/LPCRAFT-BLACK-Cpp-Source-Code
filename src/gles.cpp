//Copyright (c) 2026 LPTEAM
#include "gles.hpp"
#include <dlfcn.h>
#include <EGL/egl.h>

constexpr gl_enum gles::lequal;
constexpr gl_enum gles::always;
constexpr gl_enum gles::src_alpha;
constexpr gl_enum gles::one_minus_src_alpha;

gles::depth_mask_type gles::depth_mask = nullptr;
gles::depth_func_type gles::depth_func = nullptr;
gles::blend_func_type gles::blend_func = nullptr;
gles::depth_rangef_type gles::depth_rangef = nullptr;

void gles::install() noexcept
{
	depth_mask = (depth_mask_type)eglGetProcAddress("glDepthMask");
	depth_func = (depth_func_type)eglGetProcAddress("glDepthFunc");
	blend_func = (blend_func_type)eglGetProcAddress("glBlendFunc");
	depth_rangef = (depth_rangef_type)eglGetProcAddress("glDepthRangef");
}
