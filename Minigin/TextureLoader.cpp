#include "MiniginPCH.h"
#include "TextureLoader.h"
#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>

std::shared_ptr<dae::Texture2D> dae::TextureLoader::LoadContent(const std::string& assetFile)
{
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), assetFile.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

void dae::TextureLoader::Initialize()
{
	// load support for png and jpg, this takes a while!
	
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}
}
