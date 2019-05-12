#pragma once
#include "Singleton.h"
#include "BaseLoader.h"
#include "Font.h"

namespace dae
{
	//reference: overlordEngine
	class ContentManager final : public Singleton<ContentManager>
	{
	public:
		ContentManager() = default;
		~ContentManager() = default;

		void Initialize(std::string&& dataPath);
		void Destroy();

		void AddLoader(std::shared_ptr<BaseLoader> loader);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size, bool bold = false);

		template<class T>
		std::shared_ptr<T> Load(const std::string& assetFile)
		{
			const type_info& ti = typeid(T);
			for (std::shared_ptr<BaseLoader> loader : m_Loaders)
			{
				const type_info& loadertype = loader->GetType();
				if (loadertype == ti)
				{
					return (std::static_pointer_cast<ContentLoader<T>>(loader))->GetContent(m_DataPath + assetFile);
				}
			}

			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<BaseLoader>> m_Loaders;
		std::string m_DataPath;
	};
}
