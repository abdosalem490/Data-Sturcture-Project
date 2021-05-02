#ifndef MARS_STATION_H
#define MARS_STATION_H

#include <iostream>
#include <string>

class MarsStation {

public:
    void LoadInputFile();
    MarsStation();



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



    // A utility funcion

};


#endif