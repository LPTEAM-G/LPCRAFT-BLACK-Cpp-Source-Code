//Copyright (c) 2026 LPTEAM
#include "mod_install.hpp"
#include "minecraft_class/AmbientOcclusionCalculator.hpp"
#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class/BlockSource.hpp"
#include "minecraft_class/BlockTessellator.hpp"
#include "minecraft_class/LevelRenderer.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/MinecraftInputRenderContext.hpp"
#include "minecraft_class/ScreenChooser.hpp"
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "minecraft_class/blocks/LiquidBlock.hpp"
#include "minecraft_class/screens/InGamePlayScreen.hpp"
#include "minecraft_class/touch_gui/TouchGlyphButtonControl.hpp"

void mod_install() noexcept
{
	MinecraftClient::install();
	AppPlatform::install();
	TouchGlyphButtonControl::install();
	MinecraftInputRenderContext::install();
	BlockSource::install();
	ScreenChooser::install();
	InGamePlayScreen::install();
	AmbientOcclusionCalculator::install();
	BlockTessellator::install();
	GrassBlock::install();
	LiquidBlock::install();
	LevelRenderer::install();
}
