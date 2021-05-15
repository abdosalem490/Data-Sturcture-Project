#include "Emergency_missions.h"
Emergency_missions::Emergency_missions(int id, int Formulation_Day, int Significance, int Mission_Duration, double Target_Location)
	:Mission(id, Formulation_Day, Significance, Mission_Duration, Target_Location)
{
	Calculate_priority();
	autoPromoted = false;
}
void Emergency_missions::Calculate_priority()
{
	int Significance = get_Significance();
	int Formulation_day = get_Formulation_Day();
	int Target = (int)get_Target_Location();
	int Duration = get_Mission_Duration();
	int p =  1000* Significance / (Formulation_day + Duration + Target);
	int counter = 0;
	while (p > 0)
	{
		p /= 10;
		counter++;
	}
	priority = counter;
}
//Getting the priority
int Emergency_missions::get_priority()
{
	return priority;
}
bool Emergency_missions::getAutoPromoted() {
	return autoPromoted;
}
void Emergency_missions::setAutoPromoted(bool p) {
	autoPromoted = p;
}