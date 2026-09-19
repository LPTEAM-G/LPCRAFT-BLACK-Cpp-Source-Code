#pragma once

class GuiElement
{
public:
	bool is_not_locked() noexcept;
	void set_is_not_locked(bool flag) noexcept;
};

