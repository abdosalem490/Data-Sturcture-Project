#ifndef MARS_STATION_H
#define MARS_STATION_H

#include "Mission.h"
#include "Emergency_missions.h"
#include "Polar_missions.h"
#include "Mountainous_missions.h"
#include "LinkedPriorityQueue.h"
#include "LinkedQueue.h"
#include <iostream>
#include <string>


class MarsStation {

public:
    void LoadInputFile();
    MarsStation();
    void Add_mission(Mission* ptr);
    void Promote_mission(int id);
    void Cancel_mission(int id);

private:
    const std::string WHITESPACE = " \n\r\t\f\v";

    // Array of speeds for each list/type of rovers.
    double* SP, * SM, * SE;


    // Checkup durations for the different rovers: CM, CP, CE. 
    // N: is the number of missions the rover completes before performing a checkup.
    int CM, CP, CE, N;

    // Number of rovers of each type: Mountanious, Polar and Emergency.
    int M, P, E;

    // AutoPromotion limit AutoP and number of events EV.
    int AutoP, EV;

    //lists
    LinkedpriorityQueue<Emergency_missions*, int> available_Emergency_MissionList;
    LinkedQueue <Mountainous_missions*> available_Mountaneous_MissionList;
    LinkedQueue <Polar_missions*> available_Polar_MissionList;


    // A utility funcion

};


#endif