#pragma once
#include <unordered_map>
#include <memory>
#include <typeinfo>

namespace dae
{
	//reference: overlordEngine
	class BaseLoader
	{
	public:
		BaseLoader(const BaseLoader& other) = delete;
		BaseLoader(BaseLoader&& other) noexcept = delete;
		BaseLoader& operator=(const BaseLoader& other) = delete;
		BaseLoader& operator=(BaseLoader&& other) noexcept = delete;
		BaseLoader() = default;
		virtual ~BaseLoader() = default;

		virtual const type_info& GetType() const = 0;
		virtual void Initialize() = 0;
	};

	template<typename T>
	class ContentLoader : public BaseLoader
	{
	public:
		ContentLoader(){};
		virtual ~ContentLoader() = default;
		ContentLoader(const ContentLoader& other) = delete;
		ContentLoader(ContentLoader&& other) noexcept = delete;
		ContentLoader& operator=(const ContentLoader& other) = delete;
		ContentLoader& operator=(ContentLoader&& other) noexcept = delete;

		const type_info& GetType() const override { return typeid(T); }
		std::shared_ptr<T> GetContent(const std::string& assetFile);

		virtual std::shared_ptr<T> LoadContent(const std::string& assetFile) = 0;
		virtual void Initialize() override = 0;

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> m_contentReferences;
	};

	template <typename T>
	std::shared_ptr<T> ContentLoader<T>::GetContent(const std::string& assetFile)
	{
		for (std::pair<std::string, std::shared_ptr<T>> kvp : m_contentReferences)
		{
			if (kvp.first.compare(assetFile) == 0)
				return kvp.second;
		}

		std::shared_ptr<T> content = LoadContent(assetFile);
		if (content != nullptr)m_contentReferences.insert(std::pair<std::string, std::shared_ptr<T>>(assetFile, content));

		return content;
	}
}
