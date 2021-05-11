#ifndef _ROVER_H
#define _ROVER_H
#include <string>
#include "../Mission.h"
class Rover {

public:


	Rover(std::string, double);

	// Setters and Getters for speed.
	virtual void setSpeed(double);
	virtual double getSpeed() const;

	// Setters and Getters for Checkup Duration.
	virtual void setCheckupD(int CD);
	virtual int getCheckupD() const;

	// Get No. completed missions, increment it, 
	// or decrement it (in case of faliure for instance.)
	virtual int getCM() const;
	virtual void incrementCM();
	virtual void decrementCM();

	// Get No. failed missions, increment it.
	virtual int getFM() const;
	virtual void incrementFM();

	virtual std::string getType() const;
	virtual void setType(std::string);

	// in the following : replace int pointer with a mission pointer
	// when the classes are ready.
	virtual void assignMission(Mission*);

	//setters and getters for the days it passed in the checkup
	virtual void setdaysInCheckup(int d);
	virtual int getdaysInCheckup();

	//setters and getters for the days it passed in Maintenance
	virtual void setdaysInMaintenance(int d);
	virtual int getdaysInMaintenance();

	// This may be needed or may be not, depending on how we further implement the project.
	virtual int getStatus() const;

	double getDistanceTravelled() const;
	void incrementDistanceTravelled(double amount);

private:

	double speed;
	std::string type;
	int checkupDuration;

	double distanceTravelled;

	int daysInCheckup = 0 ;
	int daysInMaintenance = 0;

	int completedMissions;
	// For bonus, to store the number of failed missions that were assigned to this rover.
	// This may help then to determine the parameter of when to move this rover to maintainance.
	int failedMissions;

	// replace the int pointer with a mission pointer!
	Mission* assignedMission;


};



#endif