#pragma once

namespace dae
{
	template<typename T>
	class Base
	{
	public:
		Base() = default;
		virtual ~Base() = default;
		Base(const Base& other) = delete;
		Base(Base&& other) noexcept = delete;
		Base& operator=(const Base& other) = delete;
		Base& operator=(Base&& other) noexcept = delete;

		const type_info& GetType() const { return typeid(T); }
		virtual std::shared_ptr<T> Load() = 0;
	};
}
