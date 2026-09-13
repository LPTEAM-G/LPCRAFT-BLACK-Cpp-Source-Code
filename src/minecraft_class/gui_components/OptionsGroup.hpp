#ifndef MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSGROUP_HPP
#define MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSGROUP_HPP

#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/Options.hpp"

class OptionsGroup
{
public:
	using add_option_item_type = void(*)(OptionsGroup*, const Options::Option*, MinecraftClient*);
	static add_option_item_type add_option_item_orig;

	static void add_option_item(OptionsGroup* this_ptr, const Options::Option* option, MinecraftClient* mcc);

	static void install() noexcept;
};

#endif
