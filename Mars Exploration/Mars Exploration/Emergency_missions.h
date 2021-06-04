#pragma once
#include "Mission.h"
class Emergency_missions : public Mission
{
    int priority;
    bool autoPromoted;
    bool promotedByEvent;
public:
    Emergency_missions(int id = -1, int Formulation_Day = -1, int Significance = -1, int Mission_Duration = -1, double Target_Location = -1);
    //Calculating the priority
    void Calculate_priority();
    //Getting the priority
    int get_priority();
    bool getAutoPromoted();
    void setAutoPromoted(bool p);

    bool getPromotedByEvent() const;
    void setPromotedByEvent(bool p);

};

