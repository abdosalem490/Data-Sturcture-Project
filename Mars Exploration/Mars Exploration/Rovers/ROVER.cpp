#include "ROVER.h"

Rover::Rover(std::string argType, double argSpeed = 0) {

	assignMission(nullptr);
	setSpeed(argSpeed);
	setType(argType);
	distanceTravelled = 0;

}

void Rover::assignMission(Mission* a) {
	assignedMission = a;
}

void Rover::setdaysInCheckup(int d)
{
	this->daysInCheckup = d;
}

int Rover::getdaysInCheckup()
{
	return this->getdaysInCheckup();
}

void Rover::setdaysInMaintenance(int d)
{
	this->daysInMaintenance = d;
}

int Rover::getdaysInMaintenance()
{
	return this->daysInMaintenance;
}

void Rover::setSpeed(double argSpeed) {
	speed = argSpeed;
}
double Rover::getSpeed() const {
	return speed;
}

void Rover::setCheckupD(int CD) {
	checkupDuration = CD;
}
int Rover::getCheckupD() const {
	return checkupDuration;
}

void Rover::incrementCM() {
	completedMissions++;
}
void Rover::decrementCM() {
	if (completedMissions != 0)
		completedMissions--;
}
int Rover::getCM() const {
	return completedMissions;
}

void Rover::incrementFM() {
	failedMissions++;
}
int Rover::getFM() const {
	return failedMissions;
}

std::string Rover::getType() const {
	return type;
}
void Rover::setType(std::string t) {
	type = t;
}

double Rover::getDistanceTravelled() const {
	return distanceTravelled;
}
void Rover::incrementDistanceTravelled(double amount) {
	distanceTravelled += amount;
}

int Rover::getStatus() const {
	if (assignedMission == nullptr)
		return 1; // Available
	else
		return 0; // Not available.
}