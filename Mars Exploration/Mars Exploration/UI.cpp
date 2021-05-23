#include "UI.h"
#include <iostream>
#include <limits>
#include <thread>        
#include <chrono> 

UI::UI(MarsStation *arg) {

	pStation = arg;
	int choice = 0;
	bool flag = false;

	std::cout << "Choose the mode to run the program in:\n";
	std::cout << "1. Interactive mode.\n2. Step-By-Step mode.\n3. Silent Mode.\n";

	do {
		// To check if the input if is an integer value.
		if (cin >> choice) {
			
			flag = (choice != 1) && (choice != 2) && (choice != 3);
			if (flag)
				cout << "Please, enter a valid integer value between 1 and 3: ";
		} else {
			flag = (choice != 1) && (choice != 2) && (choice != 3);
			
			cout << "Please, enter a valid integer value between 1 and 3: ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		
		}
	} while (flag);
	Execute(choice);
}

void UI::Execute(int choice) {


	if (choice == 1) {

		// ADD CODE OF INTERACTIVE UI.
		int x;
		//the condition of the while loop to be modified
		while (pStation->executeDays())
		{
			cout << "press any key to continue" << endl;
			cin >> x;
			printDay();
			printWaitingMissions();
			printInExecutionMissionRovers();
			printAvailableRovers();
			printInCheckupRovers();
			printCompletedMission();
		}
	}
	else if (choice == 2) 
	{
		// ADD CODE OF STEP-BY-STEP UI.
		
		//the condition of the while loop to be modified
		while (pStation->executeDays())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			printDay();
			printWaitingMissions();
			printInExecutionMissionRovers();
			printAvailableRovers();
			printInCheckupRovers();
			printCompletedMission();
		}
	}
	else {

		// ADD CODE OF SILENT UI.

	}

}

void UI::printDay()
{
	cout<<"Current Day : "<<pStation->getToday()<<endl;
}

void UI::printWaitingMissions()
{
	Node<int>* e = nullptr;
	Node<int>* p = nullptr;
	Node<int>* m = nullptr;
	pStation->getWaitingMissions(e, p, m);
	Node<int>* temp_e = e;
	Node<int>* temp_p = p;
	Node<int>* temp_m = m;

	int counter = 0;
	if (temp_e->getItem() != -1)
	{
		while (temp_e)
		{
			counter++;
			temp_e = temp_e->getNext();
		}
	}
	if (temp_p->getItem() != -1)
	{
		while (temp_p)
		{
			counter++;
			temp_p = temp_p->getNext();
		}
	}
	if (temp_m->getItem() != -1)
	{
		while (temp_m)
		{
			counter++;
			temp_m = temp_m->getNext();
		}
	}
	temp_e = e;
	temp_p = p;
	temp_m = m;
	cout << counter;

	cout << " Waiting Missions : ";
	if (temp_e && temp_e->getItem() != -1)
	{
		cout << "[ ";
		while (temp_e)
		{
			cout << temp_e->getItem();
			cout << " , ";
			temp_e = temp_e->getNext();
		}
		cout << " ] ";
	}
	
	if (temp_p && temp_p->getItem() != -1)
	{
		cout << "( ";
		while (temp_p)
		{
			cout << temp_p->getItem();
			cout << " , ";
			temp_p = temp_p->getNext();
		}
		cout << " ) ";
	}

	if (temp_m && temp_m->getItem() != -1)
	{
		cout << "{ ";
		while (temp_m)
		{
			cout << temp_m->getItem();
			cout << " , ";
			temp_m = temp_m->getNext();
		}
		cout << " } " << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
}

void UI::printInExecutionMissionRovers()
{
	Node<int>* e_m = nullptr;
	Node<int>* e_r = nullptr;
	Node<int>* p_m = nullptr;
	Node<int>* p_r = nullptr;
	Node<int>* m_m = nullptr;
	Node<int>* m_r = nullptr;
	pStation->getInExecutionMissionRover(e_m, e_r, p_m, p_r, m_m, m_r);
	Node<int>* temp_e_m = e_m;
	Node<int>* temp_e_r = e_r;
	Node<int>* temp_p_m = p_m;
	Node<int>* temp_p_r = p_r;
	Node<int>* temp_m_m = m_m;
	Node<int>* temp_m_r = m_r;

	int counter = 0;
	if (temp_e_m->getItem() != -1)
	{
		while (temp_e_m)
		{
			counter++;
			temp_e_m = temp_e_m->getNext();
		}
	}
	if (temp_p_m->getItem() != -1)
	{
		while (temp_p_m)
		{
			counter++;
			temp_p_m = temp_p_m->getNext();
		}
	}
	if (temp_m_m->getItem() != -1)
	{
		while (temp_m_m)
		{
			counter++;
			temp_m_m = temp_m_m->getNext();
		}
	}
	temp_e_m = e_m;
	temp_p_m = p_m;
	temp_m_m = m_m;

	cout << counter;
	cout << " In-Execution Missions/Rovers : ";
	if (temp_e_m->getItem() != -1 && temp_e_r->getItem() != -1)
	{
		cout << " [ ";
		while (temp_e_m && temp_e_r)
		{
			cout << temp_e_m->getItem();
			cout << " / ";
			cout << temp_e_r->getItem();
			cout << " , ";
			temp_e_m = temp_e_m->getNext();
			temp_e_r = temp_e_r->getNext();
		}
		cout << " ] ";
	}
	if (temp_p_m->getItem() != -1 && temp_p_r->getItem() != -1)
	{
		cout << " ( ";
		while (temp_p_m && temp_p_r)
		{
			cout << temp_p_m->getItem();
			cout << " / ";
			cout << temp_p_r->getItem();
			cout << " , ";
			temp_p_m = temp_p_m->getNext();
			temp_p_r = temp_p_r->getNext();
		}
		cout << " ) ";
	}
	if (temp_m_m->getItem() != -1 && temp_m_r->getItem() != -1)
	{
		cout << " { ";
		while (temp_m_m && temp_m_r)
		{
			cout << temp_m_m->getItem();
			cout << " / ";
			cout << temp_m_r->getItem();
			cout << " , ";
			temp_m_m = temp_m_m->getNext();
			temp_m_r = temp_m_r->getNext();
		}
		cout << " } " << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
}

void UI::printAvailableRovers()
{
	Node<int>* e = nullptr;
	Node<int>* p = nullptr;
	Node<int>* m = nullptr;
	pStation->getAvailableRover(e, p, m);
	Node<int>* temp_e = e;
	Node<int>* temp_p = p;
	Node<int>* temp_m = m;

	int counter = 0;
	if (temp_e->getItem() != -1)
	{
		while (temp_e)
		{
			counter++;
			temp_e = temp_e->getNext();
		}
	}
	if (temp_p->getItem() != -1)
	{
		while (temp_p)
		{
			counter++;
			temp_p = temp_p->getNext();
		}
	}
	if (temp_m->getItem() != -1)
	{
		while (temp_m)
		{
			counter++;
			temp_m = temp_m->getNext();
		}
	}
	temp_e = e;
	temp_p = p;
	temp_m = m;
	cout << counter;

	cout << " Available Rovers : ";
	if (temp_e && temp_e->getItem() != -1)
	{
		cout << " [ ";
		while (temp_e)
		{
			cout << temp_e->getItem();
			cout << " , ";
			temp_e = temp_e->getNext();
		}
		cout << " ] ";
	}
	if (temp_p && temp_p->getItem() != -1)
	{
		cout << "( ";
		while (temp_p)
		{
			cout << temp_p->getItem();
			cout << " , ";
			temp_p = temp_p->getNext();
		}
		cout << " ) ";
	}
	if (temp_m && temp_m->getItem() != -1)
	{
		cout << "{ ";
		while (temp_m)
		{
			cout << temp_m->getItem();
			cout << " , ";
			temp_m = temp_m->getNext();
		}
		cout << " } " << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
}

void UI::printInCheckupRovers()
{
	Node<int>* e = nullptr;
	Node<int>* p = nullptr;
	Node<int>* m = nullptr;
	pStation->getInCheckupRover(e, p, m);
	Node<int>* temp_e = e;
	Node<int>* temp_p = p;
	Node<int>* temp_m = m;

	int counter = 0;
	if (temp_e->getItem() != -1)
	{
		while (temp_e)
		{
			counter++;
			temp_e = temp_e->getNext();
		}
	}
	if (temp_p->getItem() != -1)
	{
		while (temp_p)
		{
			counter++;
			temp_p = temp_p->getNext();
		}
	}
	if (temp_m->getItem() != -1)
	{
		while (temp_m)
		{
			counter++;
			temp_m = temp_m->getNext();
		}
	}
	temp_e = e;
	temp_p = p;
	temp_m = m;

	cout << counter;
	cout << " In-Checkup Rovers : ";
	if (temp_e && temp_e->getItem() != -1)
	{
		cout << " [ ";
		while (temp_e)
		{
			cout << temp_e->getItem();
			cout << " , ";
			temp_e = temp_e->getNext();
		}
		cout << " ] ";
	}
	if (temp_p && temp_p->getItem() != -1)
	{
		cout << "( ";
		while (temp_p)
		{
			cout << temp_p->getItem();
			cout << " , ";
			temp_p = temp_p->getNext();
		}
		cout << " ) ";
	}
	if (temp_m && temp_m->getItem() != -1)
	{
		cout << "{ ";
		while (temp_m)
		{
			cout << temp_m->getItem();
			cout << " , ";
			temp_m = temp_m->getNext();
		}
		cout << " } " << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
}

void UI::printCompletedMission()
{
	Node<int>* e = nullptr;
	Node<int>* p = nullptr;
	Node<int>* m = nullptr;
	pStation->getCompletedMission(e, p, m);
	Node<int>* temp_e = e;
	Node<int>* temp_p = p;
	Node<int>* temp_m = m;

	int counter = 0;
	if (temp_e->getItem() != -1)
	{
		while (temp_e)
		{
			counter++;
			temp_e = temp_e->getNext();
		}
	}
	if (temp_p->getItem() != -1)
	{
		while (temp_p)
		{
			counter++;
			temp_p = temp_p->getNext();
		}
	}
	if (temp_m->getItem() != -1)
	{
		while (temp_m)
		{
			counter++;
			temp_m = temp_m->getNext();
		}
	}
	temp_e = e;
	temp_p = p;
	temp_m = m;
	cout << counter;

	cout << " Completed Missions : ";
	if (temp_e && temp_e->getItem() != -1)
	{
		cout << " [ ";
		while (temp_e)
		{
			cout << temp_e->getItem();
			cout << " , ";
			temp_e = temp_e->getNext();
		}
		cout << " ] ";
	}
	if (temp_p && temp_p->getItem() != -1)
	{
		cout << "( ";
		while (temp_p)
		{
			cout << temp_p->getItem();
			cout << " , ";
			temp_p = temp_p->getNext();
		}
		cout << " ) ";
	}
	if (temp_m && temp_m->getItem() != -1)
	{
		cout << "{ ";
		while (temp_m)
		{
			cout << temp_m->getItem();
			cout << " , ";
			temp_m = temp_m->getNext();
		}
		cout << " } " << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
}

void UI::printRoversInMaintenance()
{
	Node<int>* e = nullptr;
	Node<int>* p = nullptr;
	Node<int>* m = nullptr;
	pStation->getRoversInMaintenance(e, p, m);
	Node<int>* temp_e = e;
	Node<int>* temp_p = p;
	Node<int>* temp_m = m;

	int counter = 0;
	if (temp_e->getItem() != -1)
	{
		while (temp_e)
		{
			counter++;
			temp_e = temp_e->getNext();
		}
	}
	if (temp_p->getItem() != -1)
	{
		while (temp_p)
		{
			counter++;
			temp_p = temp_p->getNext();
		}
	}
	if (temp_m->getItem() != -1)
	{
		while (temp_m)
		{
			counter++;
			temp_m = temp_m->getNext();
		}
	}
	temp_e = e;
	temp_p = p;
	temp_m = m;
	cout << counter;

	cout << " In-Maintenance Rovers : ";
	if (temp_e && temp_e->getItem() != -1)
	{
		cout << " [ ";
		while (temp_e)
		{
			cout << temp_e->getItem();
			cout << " , ";
			temp_e = temp_e->getNext();
		}
		cout << " ] ";
	}
	if (temp_p && temp_p->getItem() != -1)
	{
		cout << "( ";
		while (temp_p)
		{
			cout << temp_p->getItem();
			cout << " , ";
			temp_p = temp_p->getNext();
		}
		cout << " ) ";
	}
	if (temp_m && temp_m->getItem() != -1)
	{
		cout << "{ ";
		while (temp_m)
		{
			cout << temp_m->getItem();
			cout << " , ";
			temp_m = temp_m->getNext();
		}
		cout << " } " << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
}

