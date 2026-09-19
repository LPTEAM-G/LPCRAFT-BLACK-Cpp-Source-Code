#ifndef MINECRAFT_CLASS_COMPONENTS_GUIELEMENTS_HPP
#define MINECRAFT_CLASS_COMPONENTS_GUIELEMENTS_HPP

class GuiElement
{
public:
	bool is_not_locked() noexcept;
	void set_is_not_locked(bool flag) noexcept;
};

#endif
