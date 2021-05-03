#pragma once
#include "Mission.h"
class Polar_missions :
    public Mission
{
public:
    Polar_missions(int id = -1, int Formulation_Day = -1, int Significance = -1, int Mission_Duration = -1, double Target_Location = -1);
};

