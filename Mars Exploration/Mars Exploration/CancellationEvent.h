#pragma once
#include "MarsStation.h"
class MarsStation;
class Event;

class CancellationEvent : public Event
{

public:
	CancellationEvent();

	CancellationEvent(int ID, int evenDay, MarsStation* ptr);

	void execute();

};
