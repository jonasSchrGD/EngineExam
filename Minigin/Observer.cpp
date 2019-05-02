#include "MiniginPCH.h"
#include "Observer.h"
#include "Subject.h"

void dae::Observer::SubScribe(int event)
{
	Subject::GetInstance().SubScribe(shared_from_this(), event);
}
