#include "Event.h"

Event::Event()
{
	ID = -1;
	eventDay = -1;
	Pmanger = NULL;
}
Event::Event(int ID, int evenDay, MarsStation* ptr)
{
	this->ID = ID;
	this->eventDay = evenDay;
	this->Pmanger = ptr;
}

int Event::getEventDay()
{
	return this->eventDay;
}

