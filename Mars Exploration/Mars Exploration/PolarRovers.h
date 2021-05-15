#pragma once
#include "Rovers/ROVER.h"
class PolarRovers : public Rover
{
public:
	static int checkupDuration;
	PolarRovers() : Rover( -1)
	{

	}
	PolarRovers( double speed) : Rover( speed)
	{

	}
};
