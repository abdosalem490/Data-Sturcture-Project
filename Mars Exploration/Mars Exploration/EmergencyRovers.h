#pragma once
#include "Rovers/ROVER.h"
class EmergencyRovers : public Rover
{
public :
	static int checkupDuration;
	EmergencyRovers() : Rover( -1)
	{

	}
	EmergencyRovers( double speed) : Rover( speed)
	{

	}
};