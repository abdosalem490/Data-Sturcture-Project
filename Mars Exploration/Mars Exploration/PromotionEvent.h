#pragma once
#include "MarsStation.h"

class MarsStation;
class Event;

class PromotionEvent : public Event {
public:
	PromotionEvent();

	PromotionEvent(int ID, int eventDay, MarsStation* ptr);

	void execute();

};
