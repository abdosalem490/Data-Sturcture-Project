#pragma once
class Mission
{
	int ID;
	int Formulation_Day;
	// A variable to stor the day on which a mission failed. 
	// (Will be helpful in calculating the completion day, later.)
	int failedDay;
	int Waiting_Days;
	int Execution_Days;
	int Completion_Day;
	int Significance;
	int Mission_Duration;
	double Target_Location;
	bool Failed;
public:
	//Default constructor
	Mission(int id = -1, int Formulation_Day = -1, int Significance = -1, int Mission_Duration = -1, double Target_Location = -1);
	//Setting Data
	virtual void set_ID(int id);
	virtual void set_Formulation_Day(int d);
	virtual void set_Waiting_Days(int d);
	virtual void set_Execution_Days(int d);
	virtual void set_Completion_Day(int d);
	virtual void set_Significance(int d);
	virtual void set_Mission_Duration(int d);
	virtual void set_Target_Location(double t);
	virtual void set_failed(bool f);
	//Getting the data
	virtual int get_ID();
	virtual int get_Formulation_Day();
	virtual int get_Waiting_Days();
	virtual int get_Execution_Days();
	virtual int get_Completion_Day();
	virtual int get_Significance();
	virtual int get_Mission_Duration();
	virtual double get_Target_Location();
	virtual bool get_failed();

	void set_failed_day(int d);
	int get_failed_day() const;
};

