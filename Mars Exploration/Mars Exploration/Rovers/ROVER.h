#ifndef _ROVER_H
#define _ROVER_H
#include <string>
#include "../Mission.h"
class Rover {

public:


	Rover(std::string, double);

	// Setters and Getters for speed.
	void setSpeed(double);
	double getSpeed() const;

	// Setters and Getters for Checkup Duration.
	void setCheckupD(int CD);
	int getCheckupD() const;

	// Get No. completed missions, increment it, 
	// or decrement it (in case of faliure for instance.)
	int getCM() const;
	void incrementCM();
	void decrementCM();

	// Get No. failed missions, increment it.
	int getFM() const;
	void incrementFM();

	std::string getType() const;
	void setType(std::string);

	// in the following : replace int pointer with a mission pointer
	// when the classes are ready.
	void assignMission(Mission*);


	// This may be needed or may be not, depending on how we further implement the project.
	int getStatus() const;

private:

	double speed;
	std::string type;
	int checkupDuration;


	int completedMissions;
	// For bonus, to store the number of failed missions that were assigned to this rover.
	// This may help then to determine the parameter of when to move this rover to maintainance.
	int failedMissions;

	// replace the int pointer with a mission pointer!
	Mission* assignedMission;


};



#endif