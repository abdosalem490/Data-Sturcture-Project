#pragma once
#include "Rovers/ROVER.h"
class EmergencyRovers : public Rover
{
public :
	static int checkupDuration;
	EmergencyRovers() : Rover("-1", -1)
	{

	}
	EmergencyRovers(std::string type, double speed) : Rover(type, speed)
	{

	}
};