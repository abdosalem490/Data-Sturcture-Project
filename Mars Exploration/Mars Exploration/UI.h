#ifndef _UI_BASE
#define _UI_BASE

#include "MarsStation.h"
class MarStation;

class UI {

public:
	UI(MarsStation *arg);
	void Execute(int choice);

private:
	MarsStation* pStation;
	void printDay();
	void printWaitingMissions();
	void printInExecutionMissionRovers();
	void printAvailableRovers();
	void printInCheckupRovers();
	void printCompletedMission();
	void printRoversInMaintenance();
};



#endif
