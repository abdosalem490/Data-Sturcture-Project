#include "FormulationEvent.h" 
FormulationEvent::FormulationEvent() : Event()
{
	type = -1;
	targetLocation = -1;
	numberOfDays = -1;
	Significance = -1;
}
FormulationEvent::FormulationEvent(int ID, int eventDay, char type, double targetLocation, int numberOfDays, int Significance, MarsStation* ptr) : Event(ID, eventDay, ptr)
{
	this->type = type;
	this->targetLocation = targetLocation;
	this->numberOfDays = numberOfDays;
	this->Significance = Significance;
}
void FormulationEvent::execute()
{
	switch (type)
	{
	case 'E':
	{
		Emergency_missions* EM = new Emergency_missions(ID, eventDay, Significance, numberOfDays, targetLocation);
		Pmanger->Add_mission(EM);
		break;
	}
	case 'M':
	{
		Mountainous_missions* MM = new Mountainous_missions(ID, eventDay, Significance, numberOfDays, targetLocation);
		Pmanger->Add_mission(MM);
		break;
	}
	case 'P':
	{

		Polar_missions* PM = new Polar_missions(ID, eventDay, Significance, numberOfDays, targetLocation);
		Pmanger->Add_mission(PM);
		break;
	}
	default:
		break;
	}
}