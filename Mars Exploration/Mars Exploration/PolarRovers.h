#pragma once
#include "Rovers/ROVER.h"
class PolarRovers : public Rover
{
public:
	static int checkupDuration;
	PolarRovers() : Rover("-1", -1)
	{

	}
	PolarRovers(std::string type, double speed) : Rover(type, speed)
	{

	}
};
