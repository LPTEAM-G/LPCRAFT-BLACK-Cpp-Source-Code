#include "OptionsItem.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include <cstdint>

OptionsItem::_is_locked_type OptionsItem::_is_locked_orig = nullptr;

bool OptionsItem::_is_locked_impl(OptionsItem* this_ptr)
{
	if (this_ptr->get_option() == &Options::BETTER_GRASS)
	{
		auto* server = MinecraftClient::instance->get_server();
		if (server->get_level() != nullptr)
		{
			this_ptr->get_elements()[0]->set_is_not_locked(false);
		}
	}
	
	return _is_locked_orig(this_ptr);
}

bool OptionsItem::_is_locked() noexcept
{
	return _is_locked_impl(this);
}

const Options::Option* OptionsItem::get_option() const noexcept
{
	return *(Options::Option**)((uintptr_t)this + 68);
}

OptionsItem::vector_element& OptionsItem::get_elements() noexcept
{
	return *(vector_element*)((uintptr_t)this + 48);
}

void OptionsItem::install() noexcept
{
	//_ZN11OptionsItem9_isLockedEv
	void* _is_locked_target = minecraft_app::get_lib_thumb_function_ptr(0x2E7334);
	MSHook(_is_locked_target, _is_locked_impl, _is_locked_orig);
}
