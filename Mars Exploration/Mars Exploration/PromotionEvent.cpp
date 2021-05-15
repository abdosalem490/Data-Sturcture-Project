#include "PromotionEvent.h"


PromotionEvent::PromotionEvent() : Event()
{

}
PromotionEvent::PromotionEvent(int ID, int eventDay, MarsStation* ptr) : Event(ID, eventDay, ptr)
{

}
void PromotionEvent::execute()
{
	Pmanger->Promote_mission(ID);
}