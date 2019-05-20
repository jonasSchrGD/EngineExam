#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"
#include <algorithm>


void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
}

void dae::Subject::Notify(std::shared_ptr<GameObject> entity)
{
	for (auto observer : m_Observers)
	{
		observer->Notify(entity);
	}
}
