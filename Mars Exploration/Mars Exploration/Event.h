#pragma once
#include "MarsStation.h"
class Event
{
protected:
	int ID;
	int eventDay;
	MarsStation* Pmanger;
public:
	Event();

	Event(int ID, int evenDay, MarsStation* ptr);

	virtual void execute() = 0;
	~Event() { }
};
