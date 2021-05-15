#pragma once
#include "Rovers/ROVER.h"

class MountaneousRovers : public Rover
{
public:

	static int checkupDuration;

	MountaneousRovers() : Rover( -1)
	{

	}
	MountaneousRovers( double speed) : Rover( speed)
	{

	}
};
