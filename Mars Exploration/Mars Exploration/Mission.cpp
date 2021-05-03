#include "Mission.h"
Mission::Mission(int id, int Formulation_Day, int Execution_Days, int Significance, int Mission_Duration, double Target_Location, int Waiting_Days, int Completion_Day)
{
	set_ID(id);
	set_Completion_Day(Formulation_Day);
	set_Execution_Days(Waiting_Days);
	set_Formulation_Day(Execution_Days);
	set_Mission_Duration(Completion_Day);
	set_Significance(Significance);
	set_Waiting_Days(Mission_Duration);
	set_Target_Location(Target_Location);
}
void Mission::set_ID(int id)
{
	ID = (id >= 0) ? id: -1;
}
void Mission::set_Formulation_Day(int d)
{
	Formulation_Day = (d >= 0) ? d : 0;
}
void Mission::set_Waiting_Days(int d)
{
	Waiting_Days = (d >= 0) ? d : 0;
}
void Mission::set_Execution_Days(int d)
{
	Execution_Days = (d >= 0) ? d : 0;
}
void Mission::set_Completion_Day(int d)
{
	Completion_Day = (d >= 0) ? d : 0;
}
void Mission::set_Significance(int d)
{
	Significance = (d >= 0) ? d : 0;
}
void Mission::set_Mission_Duration(int d)
{
	Mission_Duration = (d >= 0) ? d : 0;
}
void Mission::set_Target_Location(double t)
{
	Target_Location = (t >= 0) ? t : 0;
}
int Mission::get_ID()
{
	return ID;
}
int Mission::get_Formulation_Day()
{
	return Formulation_Day;
}
int Mission::get_Waiting_Days()
{
	return Waiting_Days;
}
int Mission::get_Execution_Days()
{
	return Execution_Days;
}
int Mission::get_Completion_Day()
{
	return Completion_Day;
}
int Mission::get_Significance()
{
	return Significance;
}
int Mission::get_Mission_Duration()
{
	return Mission_Duration;
}
double Mission::get_Target_Location()
{
	return Target_Location;
}