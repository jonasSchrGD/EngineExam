#pragma once
#include <map>
#include <vector>

namespace dae
{
	class Observer;
	class GameObject;
	class Subject final
	{
	public:
		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		void Notify(std::shared_ptr<GameObject> entity);

	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};
}
