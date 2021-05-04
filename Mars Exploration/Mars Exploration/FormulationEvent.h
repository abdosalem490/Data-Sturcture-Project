#pragma once
#include "Event.h"
#include "Emergency_missions.h"
#include "Polar_missions.h"
#include "Mountainous_missions.h"
class FormulationEvent : public Event
{
private:
	char type;
	double targetLocation;
	int numberOfDays;
	int Significance;

public:
	FormulationEvent();
	FormulationEvent(int ID, int eventDay, char type, double targetLocation, int numberOfDays, int Significance, MarsStation* ptr);
	void execute();
};
