#pragma once
#include "Emergency_missions.h"
#include "Polar_missions.h"
#include "Mountainous_missions.h"
#include "MarsStation.h"

class MarsStation;
class Event;


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
