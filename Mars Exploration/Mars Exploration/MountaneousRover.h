#pragma once
#include "Rovers/ROVER.h"

class MountaneousRovers : public Rover
{
public:

	static int checkupDuration;

	MountaneousRovers() : Rover("-1", -1)
	{

	}
	MountaneousRovers(std::string type, double speed) : Rover(type, speed)
	{

	}
};
