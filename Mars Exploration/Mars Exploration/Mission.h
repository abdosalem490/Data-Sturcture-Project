#pragma once
class Mission
{
	int ID;
	int Formulation_Day;
	int Waiting_Days;
	int Execution_Days;
	int Completion_Day;
	int Significance;
	int Mission_Duration;
	double Target_Location;
public:
	//Default constructor
	Mission(int id = -1, int Formulation_Day = -1, int Significance = -1, int Mission_Duration = -1, double Target_Location = -1);
	//Setting Data
	void set_ID(int id);
	void set_Formulation_Day(int d);
	void set_Waiting_Days(int d);
	void set_Execution_Days(int d);
	void set_Completion_Day(int d);
	void set_Significance(int d);
	void set_Mission_Duration(int d);
	void set_Target_Location(double t);
	//Getting the data
	int get_ID();
	int get_Formulation_Day();
	int get_Waiting_Days();
	int get_Execution_Days();
	int get_Completion_Day();
	int get_Significance();
	int get_Mission_Duration();
	double get_Target_Location();
};

