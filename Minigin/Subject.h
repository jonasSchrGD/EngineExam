#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "GameObject.h"
#include <map>

namespace dae
{
	class Subject final: public Singleton<Subject>
	{
	public:
		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		void Notify(std::shared_ptr<GameObject> entity, int event) ;

		void SubScribe(std::shared_ptr<Observer> observer, int event);
		std::shared_ptr<GameObject> GetNotifier() { return m_Notifier; }

	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
		std::map<int, std::vector<std::shared_ptr<Observer>>> m_Events;

		std::shared_ptr<GameObject> m_Notifier;
	};
}
