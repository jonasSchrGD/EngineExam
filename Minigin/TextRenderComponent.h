#pragma once
#include "BaseRenderComponent.h"
#include "Texture2D.h"
#include "Font.h"

namespace dae
{
	class Font;
	class Texture2D;
	
	class TextRenderComponent final : public BaseRenderComponent
	{
	public:
		explicit TextRenderComponent(const std::string& text, std::shared_ptr<Font> font, SDL_Color color = { 255,255,255 });
		virtual ~TextRenderComponent() = default;

		void SetText(const std::string& text);
		void Render() const;

	protected:
		void Update() override;

	private:
		
		bool mNeedsUpdate;
		std::string mText;
		SDL_Color m_Color;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;
	};
}
