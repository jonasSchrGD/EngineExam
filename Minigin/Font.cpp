#include "MiniginPCH.h"
#include "Font.h"

TTF_Font* dae::Font::GetFont() const {
	return mFont;
}

dae::Font::Font(const std::string& fullPath, unsigned size, bool bold) : mFont(nullptr), mSize(size)
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	
	if (mFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}

	if (bold)
		TTF_SetFontStyle(mFont, TTF_STYLE_BOLD);
}

dae::Font::~Font()
{
	TTF_CloseFont(mFont);
}
