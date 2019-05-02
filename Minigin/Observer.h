#pragma once
namespace dae
{
	class Observer : public std::enable_shared_from_this<Observer>
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify() = 0;

	protected:
		void SubScribe(int event);
	};
}
