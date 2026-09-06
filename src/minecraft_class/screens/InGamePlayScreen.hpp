//Copyright (c) 2026 LPTEAM
#ifndef MINECRAFT_CLASS_SCREENS_INGAMEPLAYSCREEN_HPP
#define MINECRAFT_CLASS_SCREENS_INGAMEPLAYSCREEN_HPP

#include "minecraft_class/Entity.hpp"
#include "minecraft_class/Vec3.hpp"
class InGamePlayScreen
{
public:
	using _initType = int(*)(InGamePlayScreen*, int, int);
	static _initType _initOrig;
	
	using _renderedFramedItemsType = void(*)(InGamePlayScreen*, Vec3, Entity*, float);
	static _renderedFramedItemsType _renderedFramedItemsOrig;

	static int _init(InGamePlayScreen* this_ptr, int i1, int i2);
	static void _rendered_framed_items(InGamePlayScreen* this_ptr, Vec3 vec, Entity* entity, float tick);

	static void install() noexcept;
};

#endif
