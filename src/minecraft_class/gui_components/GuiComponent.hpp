#pragma once

class GuiComponent
{
private:
	void** vtable;

public:
	GuiComponent() noexcept;
};
