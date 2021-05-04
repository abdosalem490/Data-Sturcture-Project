#include "CancellationEvent.h"

CancellationEvent::CancellationEvent() : Event()
{

}
CancellationEvent::CancellationEvent(int ID, int evenDay, MarsStation* ptr) : Event(ID, evenDay, ptr)
{

}
void CancellationEvent::execute()
{
	Pmanger->Cancel_mission(ID);
}