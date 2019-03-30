#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Font.h"

namespace dae
{
	class Font;
	class Texture2D;
	
	class TextComponent final : public BaseComponent
	{
	public:
		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font, SDL_Color color = { 255,255,255 });
		virtual ~TextComponent() = default;

		void SetText(const std::string& text);

	protected:
		void Update() override;
		void Render() const override;

	private:
		void GameObjectSet() override{};
		
		bool mNeedsUpdate;
		std::string mText;
		SDL_Color m_Color;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;
	};
}
