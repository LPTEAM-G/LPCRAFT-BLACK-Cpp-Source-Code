#include "Options.hpp"
#include "hook_macro.hpp"
#include "minecraft_app.hpp"
#include <string>

bool Options::opt_vars::use_centered_gui = false;
Options::Option Options::USE_CENTERED_GUI
{
	option_type::boolean,
	"options.use_centered_gui"
};

Options::Option::Option(Options::option_type type, const std::string& name) noexcept:
	opt_type(type),
	opt_name(name)
{}


Options::option_type Options::Option::type() const noexcept
{
	return opt_type;
}

const std::string& Options::Option::name() const noexcept
{
	return opt_name;
}


Options::options_toggle_type Options::options_toggle_orig = nullptr;
Options::set_boolean_value_type Options::set_boolean_value_orig = nullptr;
Options::get_boolean_value_type Options::get_boolean_value_orig = nullptr;

void Options::toggle(Options* this_ptr, const Option* option, int step)
{
	if (option == &Options::USE_CENTERED_GUI)
		opt_vars::use_centered_gui = not opt_vars::use_centered_gui;
	options_toggle_orig(this_ptr, option, step);
}

void Options::set_boolean_value(Options* this_ptr, const Option* option, bool value)
{
	if (option == &Options::USE_CENTERED_GUI)
		opt_vars::use_centered_gui = value;
	set_boolean_value_orig(this_ptr, option, value);
}

bool Options::get_boolean_value(Options* this_ptr, const Option* option)
{
	if (option == &Options::USE_CENTERED_GUI)
		return opt_vars::use_centered_gui;
	return get_boolean_value_orig(this_ptr, option);
}

void Options::install() noexcept
{
	//_ZN7Options6toggleEPKNS_6OptionEi
	void* toggle_target = minecraft_app::get_lib_thumb_function_ptr(0x3E78C4);
	MSHook(toggle_target, toggle, options_toggle_orig);
	
	//_ZN7Options3setEPKNS_6OptionEb
	void* set_boolean_value_target = minecraft_app::get_lib_thumb_function_ptr(0x38FA8C);
	MSHook(set_boolean_value_target, set_boolean_value, set_boolean_value_orig);

	//_ZN7Options15getBooleanValueEPKNS_6OptionE
	void* get_boolean_value_target = minecraft_app::get_lib_thumb_function_ptr(0x38F2D4);
	MSHook(get_boolean_value_target, get_boolean_value, get_boolean_value_orig);
}
