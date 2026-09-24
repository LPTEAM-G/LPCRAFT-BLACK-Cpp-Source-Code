//Copyright (c) 2026 LPTEAM
#include "mod_install.hpp"
#include "minecraft_class/AmbientOcclusionCalculator.hpp"
#include "minecraft_class/AppPlatform.hpp"
#include "minecraft_class/AppPlatform_android.hpp"
#include "minecraft_class/LevelRenderer.hpp"
#include "minecraft_class/MinecraftClient.hpp"
#include "minecraft_class/MinecraftInputHandler.hpp"
#include "minecraft_class/render_context/MinecraftInputRenderContext.hpp"
#include "minecraft_class/blocks/PodzolBlock.hpp"
#include "minecraft_class/gui_components/OptionsItem.hpp"
#include "minecraft_class/options_about/Options.hpp"
#include "minecraft_class/options_about/PropertyFile.hpp"
#include "minecraft_class/sound_about/SoundEngine.hpp"
#include "minecraft_class/blocks/GrassBlock.hpp"
#include "minecraft_class/blocks/LiquidBlock.hpp"
#include "minecraft_class/blocks/GrassPathBlock.hpp"
#include "minecraft_class/blocks/MyceliumBlock.hpp"
#include "minecraft_class/screen_about/OptionsScreen.hpp"
#include "minecraft_class/touch_gui/TouchGlyphButtonControl.hpp"
#include "minecraft_class/touch_gui/TouchMapper.hpp"

void mod_install() noexcept
{
	MinecraftClient::install();
	AppPlatform::install();
	AppPlatform_android::install();
	
	//about options
	Options::install();
	OptionsItem::install();
	PropertyFile::install();

	//about sound
	SoundEngine::install();

	//about touch gui
	TouchMapper::install();
	TouchGlyphButtonControl::install();
	MinecraftInputHandler::install();
	MinecraftInputRenderContext::install();
	
	//about screen
	OptionsScreen::install();
	
	AmbientOcclusionCalculator::install();

	//about blocks
	GrassBlock::install();
	GrassPathBlock::install();
	PodzolBlock::install();
	MyceliumBlock::install();
	LiquidBlock::install();
	
	LevelRenderer::install();
}
