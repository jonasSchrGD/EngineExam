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
		void Notify(std::shared_ptr<GameObject> entity, int event) ;

		void SubScribe(std::shared_ptr<Observer> observer, int event);

	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
		std::map<int, std::vector<std::shared_ptr<Observer>>> m_Events;
	};
}
