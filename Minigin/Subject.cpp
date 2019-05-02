#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>


void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
}

void dae::Subject::Notify(std::shared_ptr<GameObject> entity, int event)
{
	auto& observers = m_Events[event];

	for (auto observer : observers)
	{
		observer->Notify();
	}
}

void dae::Subject::SubScribe(std::shared_ptr<Observer> observer, int event)
{
	m_Events[event].push_back(observer);
}
