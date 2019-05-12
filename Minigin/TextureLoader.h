#pragma once
#include "BaseLoader.h"
#include "Texture2D.h"

namespace dae
{
	class TextureLoader final : public ContentLoader<Texture2D>
	{
	public:
		TextureLoader(){}
		~TextureLoader() override = default;

		std::shared_ptr<Texture2D> LoadContent(const std::string& assetFile) override;
		void Initialize() override;
	};
}
