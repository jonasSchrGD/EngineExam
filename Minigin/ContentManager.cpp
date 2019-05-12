#include "MiniginPCH.h"
#include "ContentManager.h"
#include "TextureLoader.h"

void dae::ContentManager::Initialize(std::string&& dataPath)
{
	m_DataPath = std::move(dataPath);

	AddLoader(std::make_shared<TextureLoader>());

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

void dae::ContentManager::Destroy()
{
	m_Loaders.clear();
}

void dae::ContentManager::AddLoader(std::shared_ptr<BaseLoader> loader)
{
	for (std::shared_ptr<BaseLoader> ldr : m_Loaders)
	{
		if (ldr->GetType() == loader->GetType())
		{
			return;
		}
	}

	m_Loaders.push_back(loader);
	loader->Initialize();
}

std::shared_ptr<dae::Font> dae::ContentManager::LoadFont(const std::string& file, unsigned size, bool bold)
{
	return std::make_shared<Font>(m_DataPath + file, size, bold);
}
