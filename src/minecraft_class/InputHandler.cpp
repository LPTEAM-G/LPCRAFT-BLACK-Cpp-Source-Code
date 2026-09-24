#include "InputHandler.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/render_context/InputRenderContext.hpp"

void InputHandler::render(InputRenderContext& context) noexcept
{
	using render_type = void(*)(InputHandler*, InputRenderContext*);
	render_type render_orig = (render_type)minecraft_app::get_lib_thumb_function_ptr(0x2B1904);
	render_orig(this, &context);
}
