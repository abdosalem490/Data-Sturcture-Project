#pragma once
#include "MarsStation.h"

class MarsStation; // Forward class decleration

class Event
{
protected:
	int ID;
	int eventDay;
	MarsStation* Pmanger;
public:
	Event();

	Event(int ID, int evenDay, MarsStation* ptr);
	int getEventDay();
	virtual void execute() = 0;
	~Event() { }
};
