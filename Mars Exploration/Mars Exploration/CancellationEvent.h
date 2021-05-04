#pragma once
#include "Event.h"
class CancellationEvent : public Event
{

public:
	CancellationEvent();

	CancellationEvent(int ID, int evenDay, MarsStation* ptr);

	void execute();

};
