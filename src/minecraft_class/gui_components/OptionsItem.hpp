#ifndef MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSITEM_HPP
#define MINECRAFT_CLASS_GUI_COMPONENTS_OPTIONSITEM_HPP


#include "minecraft_class/gui_components/GuiElement.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include <memory>
#include <vector>

class OptionsItem
{
private:
	using _is_locked_type = bool(*)(OptionsItem*);
	static _is_locked_type _is_locked_orig;
	static bool _is_locked_impl(OptionsItem* this_ptr);
	
public:
	using vector_element = std::vector<std::shared_ptr<GuiElement>>;

	bool _is_locked() noexcept;

	const Options::Option* get_option() const noexcept;
	vector_element& get_elements() noexcept;

	static void install() noexcept;
};

#endif
