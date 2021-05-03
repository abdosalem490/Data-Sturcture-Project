#pragma once
#include "Mission.h"
class Mountainous_missions :
    public Mission
{
public:
    Mountainous_missions(int id = -1, int Formulation_Day = -1, int Execution_Days = -1, int Significance = -1, int Mission_Duration = -1, double Target_Location = -1, int Waiting_Days = -1, int Completion_Day = -1);
};

