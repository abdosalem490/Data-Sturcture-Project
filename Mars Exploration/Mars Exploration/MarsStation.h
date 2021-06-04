#ifndef MARS_STATION_H
#define MARS_STATION_H

#include <string>

#include "Mission.h"
#include "Emergency_missions.h"
#include "Polar_missions.h"
#include "Mountainous_missions.h"
#include "LinkedPriorityQueue.h"
#include "LinkedQueue.h"
#include "SortedList.h"
#include "EmergencyRovers.h"
#include "PolarRovers.h"
#include "MountaneousRover.h"
#include "Rovers/ROVER.h"

// DON'T include any type of event here. Include them in MarsStation.cpp file.
#include "Event.h"


#include <iostream>
#include <string>

class Event; // Forward class decleration
class FormulationEvent;
class PromotionEvent;
class CancellationEvent;

class MarsStation {

public:
    void LoadInputFile();
    void SaveOutputFile();

    MarsStation();
    void Add_mission(Mission* ptr);
    void Promote_mission(int id);
    void Cancel_mission(int id);
    void execute_Events();
    
    void check_For_Completed_Rovers_Missions();
    void check_For_Failed_Missions();
    void check_To_Get_From_Checkup();
    void check_for_rovers_into_maintenance();
    void check_for_rovers_outta_maintenance();

    void increment_Days();
    void setToday(int d);
    int getToday();

    // Assigning missions to rover
    void Assign_mission();

    // Execution
    bool Execution();

    //============================= methods for returning data to be printed ===================================
    void getWaitingMissions(Node<int>*& e , Node<int>*& p , Node<int>*& m);
    void getInExecutionMissionRover(Node<int>*& e_m, Node<int>*& e_r, Node<int>*& p_m, Node<int>*& p_r, Node<int>*& m_m, Node<int>*& m_r);
    void getAvailableRover(Node<int>*& e, Node<int>*& p, Node<int>*& m);
    void getInCheckupRover(Node<int>*& e, Node<int>*& p, Node<int>*& m);
    void getCompletedMission(Node<int>*& e, Node<int>*& p, Node<int>*& m);
    void getRoversInMaintenance(Node<int>*& e, Node<int>*& p, Node<int>*& m);
    //=========================================== end of methods ===========================================

    // for auto promotion of mountaneous rovers
    void autoPromote();


    void setInputFileName(std::string arg) {
        inputFileName = arg;
        
        // Removing .txt extension, adding _output trail to the output file name, then reappending it again.
        std::string temp = inputFileName;
        std::string extension = ".txt";

        std::string::size_type i = temp.find(extension);

        if (i != std::string::npos)
            temp.erase(i, extension.length());

        outputFileName = temp + "_output" + ".txt";
    }

    std::string getOutputFile() const {
        return outputFileName;
    }

private:
    
    std::string inputFileName;
    std::string outputFileName;

    

    const std::string WHITESPACE = " \n\r\t\f\v";

    // Array of speeds for each list/type of rovers.
    double* SP, * SM, * SE;

    // Average speed of rovers of each type.
    double AvgSP, AvgSM, AvgSE;



    // Maximum ED
    // Checkup durations for the different rovers: CM, CP, CE. 
    // N: is the number of missions the rover completes before performing a checkup.
    int CM, CP, CE, N;

    // Number of rovers of each type: Mountanious, Polar and Emergency.
    int M, P, E;

    // AutoPromotion limit AutoP and number of events EV.
    int AutoP, EV;

    //today's day 
    int today = 0;

    // number of initial mountainous, polar, emergency missions: incremented at formulation and decremented at cancellation.
    int numOfMntM = 0, numOfPolarM = 0, numOfEmergencyM = 0;

    // a rough total number of all the missions (calculated when enqueueing events, helps at calculating chances of faliure).
    // Does not take cancellation into account.
    int roughNumOfMissions = 0;
    int numOfFailedMissions = 0;

    //<------------------------------Lists--------------------------------->

    //available missions
    LinkedpriorityQueue<Emergency_missions*, int> available_Emergency_MissionList;
    LinkedQueue <Mountainous_missions*> available_Mountaneous_MissionList;
    LinkedQueue <Polar_missions*> available_Polar_MissionList;

    //rover & missions in execution 
    LinkedSortedList<Pair<Mission* , int>> inExecution_MissionsList;
    LinkedSortedList<Pair<Rover*, int>> rovers_InMission;

    //completed missions
    LinkedSortedList<Pair<Mission* , double>> completed_MissionsList;

    //events needed to be done
    LinkedQueue <Event*> eventsList;

    //checkup list
    LinkedSortedList<Pair<Rover*, int>> rovers_InCheckup;

    //Maintenance rovers list 
    LinkedSortedList<Pair<EmergencyRovers* , int>> emergency_Rovers_InMaintenance;
    LinkedSortedList<Pair<MountaneousRovers*, int>> mountaneous_Rovers_InMaintenance;
    LinkedSortedList<Pair<PolarRovers*, int>> Polar_Rovers_InMaintenance;

    //available rovers
    LinkedSortedList<Pair<EmergencyRovers* , double>> available_Emergency_RoversList;
    LinkedSortedList<Pair<PolarRovers*, double>> available_Polar_RoversList;
    LinkedSortedList<Pair<MountaneousRovers*, double >> available_Mountaneous_RoversList;

    //<----------------------------end of list--------------------------------->

    // A utility funcion

};


#endif