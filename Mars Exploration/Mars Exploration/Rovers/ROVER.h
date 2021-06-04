#ifndef _ROVER_H
#define _ROVER_H
#include <string>
#include "../Mission.h"
class Rover {

public:


	Rover( double);

	// Setters and Getters for speed.
	virtual void setSpeed(double);
	virtual double getSpeed() const;

	// Setters and Getters for Checkup Duration.
	virtual void setCheckupD(int CD);
	virtual int getCheckupD() const;

	// Get No. completed missions, increment it, 
	// or decrement it (in case of faliure for instance.)
	virtual int getTotalCM() const;
	void setTotalCM(int t);
	virtual void incrementCM();
	virtual void decrementCM();

	int getCmForCheckup() const {
		return CMtillCheckup;
	}
	void setCMforCheckup(int a) {
		this->CMtillCheckup = a;
	}

	// Get No. failed missions, increment it.
	virtual int getFM() const;
	virtual void incrementFM();
	void setFM(int f);


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

	virtual double getDistanceTravelled() const;
	virtual void incrementDistanceTravelled(double amount);
	void setDistanceTravelled(double p);

	//getters and setters to check for the comleteness of Maintenance
	virtual void setFinishedMaintenance(bool value);
	virtual bool getFinishedMaintenance();

	//getters and setters for maintenanceDuration
	virtual void setMaintenanceDuration(int d);
	virtual int getMaintenanceDuration();


	//setters and getters for the ID
	virtual int getID();
	virtual void setID(int id);


private:

	double speed;
	
	int checkupDuration;
	int maintenanceDuration;
	double distanceTravelled;

	int daysInCheckup = 0;
	int daysInMaintenance = 0;

	bool finishedMaintenance = true;

	int totalCM = 0;
	int CMtillCheckup = 0;
	// For bonus, to store the number of failed missions that were assigned to this rover.
	// This may help then to determine the parameter of when to move this rover to maintainance.
	int failedMissions;

	// replace the int pointer with a mission pointer!
	Mission* assignedMission;
	int ID;

};



#endif