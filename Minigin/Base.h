#pragma once

namespace dae
{
	template<typename T>
	class BaseLoader
	{
	public:
		BaseLoader() = default;
		virtual ~BaseLoader() = default;
		BaseLoader(const BaseLoader& other) = delete;
		BaseLoader(BaseLoader&& other) noexcept = delete;
		BaseLoader& operator=(const BaseLoader& other) = delete;
		BaseLoader& operator=(BaseLoader&& other) noexcept = delete;

		const type_info& GetType() const { return typeid(T); }
		virtual std::shared_ptr<T> Load() = 0;
	};
}
