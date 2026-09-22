#include "TouchControlSet.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/InputRenderContext.hpp"

TouchControlSet::render_type TouchControlSet::render_orig = nullptr;

int TouchControlSet::render_impl(TouchControlSet* this_ptr, InputRenderContext* context)
{
	return render_orig(this_ptr, context);
}

int TouchControlSet::render(InputRenderContext& context) noexcept
{
	return render_impl(this, &context);
}

void TouchControlSet::install() noexcept
{
	//_ZNK15TouchControlSet6renderER18InputRenderContext
	void* render_target = minecraft_app::get_lib_thumb_function_ptr(0x2B3168);
	MSHook(render_target, render_impl, render_orig);
}
