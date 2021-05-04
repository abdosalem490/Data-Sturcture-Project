#pragma once
#include "Event.h"
class PromotionEvent : public Event
{
public:
	PromotionEvent();

	PromotionEvent(int ID, int eventDay, MarsStation* ptr);

	void execute();

};
