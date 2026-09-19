//Copyright (c) 2026 LPTEAM
#pragma once

#include <string>

class Options
{
public:
	enum class option_type : unsigned
	{
		boolean = 0,
		floating = 1,
		string = 2,
		integer = 3
	};

	class Option
	{
	private:
		option_type opt_type;
		std::string opt_name;

	public:
		Option(option_type type, const std::string& name) noexcept;
		~Option() noexcept = default;

		option_type type() const noexcept;
		const std::string& name() const noexcept;
	};

	struct opt_vars
	{
		struct gui
		{
			static bool centered_hud;
		};

		struct graphics
		{
			static bool better_grass;
		};
	};
	static Option CENTERED_HUD;
	static Option BETTER_GRASS;

	using options_toggle_type = void(*)(Options*, const Option*, int);
	static options_toggle_type options_toggle_orig;

	using set_boolean_value_type = void(*)(Options*, const Option*, bool);
	static set_boolean_value_type set_boolean_value_orig;

	using get_boolean_value_type = bool(*)(Options*, const Option*);
	static get_boolean_value_type get_boolean_value_orig;

	static void toggle(Options* this_ptr, const Option* option, int step);
	static void set_boolean_value(Options* this_ptr, const Option* option, bool value);
	static bool get_boolean_value(Options* this_ptr, const Option* option);

	static void install() noexcept;
};

