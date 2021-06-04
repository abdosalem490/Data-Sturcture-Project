#include "ROVER.h"

Rover::Rover( double argSpeed = 0) {

	assignMission(nullptr);
	setSpeed(argSpeed);
	
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
	return daysInCheckup;
}

void Rover::setdaysInMaintenance(int d)
{
	this->daysInMaintenance = d;
}

int Rover::getdaysInMaintenance()
{
	return daysInMaintenance;
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
	totalCM++;
	CMtillCheckup++;
}
void Rover::decrementCM() {
	if (totalCM != 0)
		totalCM--;
}
int Rover::getTotalCM() const {
	return totalCM;
}
void Rover::setTotalCM(int t) {
	totalCM = t;
}

void Rover::incrementFM() {
	failedMissions++;
}
int Rover::getFM() const {
	return failedMissions;
}
void Rover::setFM(int f) {
	failedMissions = f;
}

double Rover::getDistanceTravelled() const {
	return distanceTravelled;
}
void Rover::setDistanceTravelled(double p) {
	distanceTravelled = p;
}

void Rover::incrementDistanceTravelled(double amount) {
	distanceTravelled += amount;
}

void Rover::setFinishedMaintenance(bool value)
{
	this->finishedMaintenance = value;
}

bool Rover::getFinishedMaintenance()
{
	return this->finishedMaintenance;
}

void Rover::setMaintenanceDuration(int d)
{
	this->maintenanceDuration = d;
}

int Rover::getMaintenanceDuration()
{
	return this->maintenanceDuration;
}

int Rover::getID()
{
	return this->ID;
}

void Rover::setID(int id)
{
	this->ID = id;
}



int Rover::getStatus() const {
	if (assignedMission == nullptr)
		return 1; // Available
	else
		return 0; // Not available.
}