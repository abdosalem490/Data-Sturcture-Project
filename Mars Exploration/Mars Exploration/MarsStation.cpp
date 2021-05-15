#include "MarsStation.h"
#include "PromotionEvent.h"
#include "CancellationEvent.h"
#include "FormulationEvent.h"


#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

MarsStation::MarsStation() {
	LoadInputFile();
}
// Assigning missions to rover
void MarsStation::Assign_mission()
{
	if ((available_Emergency_MissionList.isEmpty() == true && available_Mountaneous_MissionList.isEmpty() == true && available_Polar_MissionList.isEmpty() == true)
		|| (available_Emergency_RoversList.isEmpty() == true && available_Polar_RoversList.isEmpty() == true && available_Mountaneous_RoversList.isEmpty() == true)
		|| (emergency_Rovers_InMaintenance.isEmpty() == true && mountaneous_Rovers_InMaintenance.isEmpty() == true && Polar_Rovers_InMaintenance.isEmpty() == true))
	{
		return;
	}
	while (available_Emergency_MissionList.isEmpty() == false)
	{
		Emergency_missions* ptr_mission = NULL;
		Pair<Emergency_missions*, int> pair_emergency;
		bool sucess = available_Emergency_MissionList.dequeue(pair_emergency);
		if (sucess == false)
		{
			break;
		}
		ptr_mission = pair_emergency.get_value();
		if (available_Emergency_RoversList.isEmpty() == false)
		{
			EmergencyRovers* ptr_rover;
			Pair<EmergencyRovers*, double> pair_rover;
			pair_rover = available_Emergency_RoversList.getEntry(0);
			available_Emergency_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (available_Mountaneous_RoversList.isEmpty() == false)
		{
			MountaneousRovers* ptr_rover;
			Pair<MountaneousRovers*, double> pair_rover;
			pair_rover = available_Mountaneous_RoversList.getEntry(0);
			available_Mountaneous_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (available_Polar_RoversList.isEmpty() == false)
		{
			PolarRovers* ptr_rover;
			Pair<PolarRovers*, double> pair_rover;
			pair_rover = available_Polar_RoversList.getEntry(0);
			available_Polar_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (emergency_Rovers_InMaintenance.isEmpty() == false)
		{
			EmergencyRovers* ptr_rover;
			Pair<EmergencyRovers*, int> pair_rover;
			pair_rover = emergency_Rovers_InMaintenance.getEntry(0);
			emergency_Rovers_InMaintenance.remove(0);
			ptr_rover = pair_rover.get_value();
			// reducing speed to half
			ptr_rover->setSpeed((ptr_rover->getSpeed() / 2));
			//define that the rover didn't finish maintenance
			ptr_rover->setFinishedMaintenance(false);
			ptr_rover->setdaysInMaintenance(ptr_rover->getMaintenanceDuration());
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (mountaneous_Rovers_InMaintenance.isEmpty() == false)
		{
			MountaneousRovers* ptr_rover;
			Pair<MountaneousRovers*, int> pair_rover;
			pair_rover = mountaneous_Rovers_InMaintenance.getEntry(0);
			mountaneous_Rovers_InMaintenance.remove(0);
			ptr_rover = pair_rover.get_value();
			// reducing speed to half
			ptr_rover->setSpeed((ptr_rover->getSpeed() / 2));
			//define that the rover didn't finish maintenance
			ptr_rover->setFinishedMaintenance(false);
			ptr_rover->setdaysInMaintenance(ptr_rover->getMaintenanceDuration());
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (Polar_Rovers_InMaintenance.isEmpty() == false)
		{
			PolarRovers* ptr_rover;
			Pair<PolarRovers*, int> pair_rover;
			pair_rover = Polar_Rovers_InMaintenance.getEntry(0);
			Polar_Rovers_InMaintenance.remove(0);
			ptr_rover = pair_rover.get_value();
			// reducing speed to half
			ptr_rover->setSpeed((ptr_rover->getSpeed() / 2));
			//define that the rover didn't finish maintenance
			ptr_rover->setFinishedMaintenance(false);
			ptr_rover->setdaysInMaintenance(ptr_rover->getMaintenanceDuration());
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else
		{
			available_Emergency_MissionList.enqueue(pair_emergency);
		}
	}
	while (available_Mountaneous_MissionList.isEmpty() == false)
	{
		Mountainous_missions* ptr_mission = NULL;
		bool sucess = available_Mountaneous_MissionList.dequeue(ptr_mission);
		if (sucess == false)
		{
			break;
		}
		if (available_Mountaneous_RoversList.isEmpty() == false)
		{
			MountaneousRovers* ptr_rover;
			Pair<MountaneousRovers*, double> pair_rover;
			pair_rover = available_Mountaneous_RoversList.getEntry(0);
			available_Mountaneous_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (available_Emergency_RoversList.isEmpty() == false)
		{
			EmergencyRovers* ptr_rover;
			Pair<EmergencyRovers*, double> pair_rover;
			pair_rover = available_Emergency_RoversList.getEntry(0);
			available_Emergency_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (mountaneous_Rovers_InMaintenance.isEmpty() == false)
		{
			MountaneousRovers* ptr_rover;
			Pair<MountaneousRovers*, int> pair_rover;
			pair_rover = mountaneous_Rovers_InMaintenance.getEntry(0);
			mountaneous_Rovers_InMaintenance.remove(0);
			ptr_rover = pair_rover.get_value();
			// reducing speed to half
			ptr_rover->setSpeed((ptr_rover->getSpeed() / 2));
			//define that the rover didn't finish maintenance
			ptr_rover->setFinishedMaintenance(false);
			ptr_rover->setdaysInMaintenance(ptr_rover->getMaintenanceDuration());
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (emergency_Rovers_InMaintenance.isEmpty() == false)
		{
			EmergencyRovers* ptr_rover;
			Pair<EmergencyRovers*, int> pair_rover;
			pair_rover = emergency_Rovers_InMaintenance.getEntry(0);
			emergency_Rovers_InMaintenance.remove(0);
			ptr_rover = pair_rover.get_value();
			// reducing speed to half
			ptr_rover->setSpeed((ptr_rover->getSpeed() / 2));
			//define that the rover didn't finish maintenance
			ptr_rover->setFinishedMaintenance(false);
			ptr_rover->setdaysInMaintenance(ptr_rover->getMaintenanceDuration());
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else
		{
			available_Mountaneous_MissionList.enqueue(ptr_mission);
		}
	}
	while (available_Polar_MissionList.isEmpty() == false)
	{
		Polar_missions* ptr_mission = NULL;
		bool sucess = available_Polar_MissionList.dequeue(ptr_mission);
		if (sucess == false)
		{
			break;
		}
		if (available_Polar_RoversList.isEmpty() == false)
		{
			PolarRovers* ptr_rover;
			Pair<PolarRovers*, double> pair_rover;
			pair_rover = available_Polar_RoversList.getEntry(0);
			available_Polar_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}

		else if (Polar_Rovers_InMaintenance.isEmpty() == false)
		{
			PolarRovers* ptr_rover;
			Pair<PolarRovers*, int> pair_rover;
			pair_rover = Polar_Rovers_InMaintenance.getEntry(0);
			Polar_Rovers_InMaintenance.remove(0);
			ptr_rover = pair_rover.get_value();
			// reducing speed to half
			ptr_rover->setSpeed((ptr_rover->getSpeed() / 2));
			//define that the rover didn't finish maintenance
			ptr_rover->setFinishedMaintenance(false);
			ptr_rover->setdaysInMaintenance(ptr_rover->getMaintenanceDuration());
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / ptr_rover->getSpeed()) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			int days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			ptr_mission->set_Completion_Day(days_completion);
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else
		{
			available_Polar_MissionList.enqueue(ptr_mission);
		}
	}
}
void MarsStation::Cancel_mission(int id)
{
	LinkedQueue <Mountainous_missions*> temp;
	while (available_Mountaneous_MissionList.isEmpty() == false)
	{
		Mountainous_missions* t;
		available_Mountaneous_MissionList.dequeue(t);
		int id_temp = t->get_ID();
		if (id_temp != id)
		{
			temp.enqueue(t);
		}
	}
	while (temp.isEmpty() == false)
	{
		Mountainous_missions* t;
		temp.dequeue(t);
		available_Mountaneous_MissionList.enqueue(t);
	}
}
void MarsStation::execute_Events()
{
	Event* e;
	while (!eventsList.isEmpty())
	{
		if (eventsList.peek(e))
		{
			if (e->getEventDay() != today)
			{
				break;
			}
			eventsList.dequeue(e);
			e->execute();
		}
	}
}
void MarsStation::check_For_Completed_Rovers_Missions()
{
	Mission* m;
	Rover* r;
	while (!inExecution_MissionsList.isEmpty() && !rovers_InMission.isEmpty())
	{
		// Obtaining the mission.
		Pair<Mission*, int>p1 = inExecution_MissionsList.getEntry(0);
		m = p1.get_value();

		// Obtaining the rover.
		Pair<Rover*, int>p2 = rovers_InMission.getEntry(0);
		r = p2.get_value();

		// If the mission is to be completed today.
		if (m->get_Completion_Day() == today)
		{
			// Removing missions and rovers from the inExecution lists.
			inExecution_MissionsList.remove(0);
			rovers_InMission.remove(0);

			// Inserting mission to the completed missions list.
			int priority1_CompeletionDays = m->get_Completion_Day();
			int priority2_ExecutionDays = m->get_Execution_Days();
			int priority = 0;
			int numOfDigitsInExecutionDays = 0;
			int temp = priority2_ExecutionDays;
			while (temp > 0)
			{
				numOfDigitsInExecutionDays++;
				temp /= 10;
			}
			priority = priority1_CompeletionDays * numOfDigitsInExecutionDays + priority2_ExecutionDays;
			Pair<Mission*, int>p1_new(m, priority);
			completed_MissionsList.insertSorted(p1_new);

			// Incrementing the number of completed missions done by this rover.
			r->incrementCM();

			// Adding the distance travelled through this mission to the rover's data member: distanceTravelled.
			r->incrementDistanceTravelled(m->get_Target_Location() * 2);


			if (r && (r->getCM()) % N == N)
			{
				r->setdaysInCheckup(r->getCheckupD());
				Pair<Rover*, int>p2_new(r, r->getdaysInCheckup());
				rovers_InCheckup.insertSorted(p2_new);
			}
			else if (!r->getFinishedMaintenance())
			{
				if (dynamic_cast<EmergencyRovers*>(r))
				{
					EmergencyRovers* n_r = dynamic_cast<EmergencyRovers*>(r);
					n_r->setSpeed(n_r->getSpeed() * 2);
					Pair< EmergencyRovers*, int> p(n_r, n_r->getdaysInMaintenance());
					emergency_Rovers_InMaintenance.insertSorted(p);
				}
				else if (dynamic_cast<MountaneousRovers*>(r))
				{
					MountaneousRovers* n_r = dynamic_cast<MountaneousRovers*>(r);
					n_r->setSpeed(n_r->getSpeed() * 2);
					Pair< MountaneousRovers*, int> p(n_r,n_r-> getdaysInMaintenance());
					mountaneous_Rovers_InMaintenance.insertSorted(p);
				}
				else if (dynamic_cast<PolarRovers*>(r))
				{
					PolarRovers* n_r = dynamic_cast<PolarRovers*>(r);
					n_r->setSpeed(n_r->getSpeed() * 2);
					Pair< PolarRovers*, int> p(n_r,n_r->getdaysInMaintenance());
					Polar_Rovers_InMaintenance.insertSorted(p);
				}
			}
			else
			{
				if (dynamic_cast<EmergencyRovers*>(r))
				{
					EmergencyRovers* n_r = dynamic_cast<EmergencyRovers*>(r);
					Pair< EmergencyRovers*, double> p(n_r, n_r->getSpeed());
					available_Emergency_RoversList.insertSorted(p);
				}
				else if (dynamic_cast<MountaneousRovers*>(r))
				{
					MountaneousRovers* n_r = dynamic_cast<MountaneousRovers*>(r);
					Pair< MountaneousRovers*, double> p(n_r, n_r->getSpeed());
					available_Mountaneous_RoversList.insertSorted(p);
				}
				else if (dynamic_cast<PolarRovers*>(r))
				{
					PolarRovers* n_r = dynamic_cast<PolarRovers*>(r);
					Pair< PolarRovers*, double> p(n_r, n_r->getSpeed());
					available_Polar_RoversList.insertSorted(p);
				}
			}
		}
		else
		{
			m = nullptr;
			r = nullptr;
			break;
		}
	}
}
void MarsStation::check_For_Failed_Missions()
{
	srand((unsigned)time(0));
	int random = rand();
	random = (random % (inExecution_MissionsList.getLength())*20) + 1;
	int i = 0;
	Mission* m;
	Rover* r;
	while (i != inExecution_MissionsList.getLength())
	{
		Pair<Mission*, int>p1 = inExecution_MissionsList.getEntry(i);
		m = p1.get_value();
		if (m->get_ID() == random)
		{
			Pair<Rover*, int> p1 = rovers_InMission.getEntry(i);
			r = p1.get_value();
			r->incrementFM();
			inExecution_MissionsList.remove(i);
			rovers_InMission.remove(i);
			m->set_Completion_Day(0);
			m->set_Execution_Days(0);
			if (dynamic_cast<Emergency_missions*>(m))
			{
				Emergency_missions* n_m = dynamic_cast<Emergency_missions*>(m);
				Pair< Emergency_missions*, int >p(n_m, n_m->get_priority());
				available_Emergency_MissionList.enqueue(p);
			}
			else if (dynamic_cast<Mountainous_missions*>(m))
			{
				Mountainous_missions* n_m = dynamic_cast<Mountainous_missions*>(m);
				available_Mountaneous_MissionList.enqueue(n_m);
			}
			else if (dynamic_cast<Polar_missions*>(m))
			{
				Polar_missions* n_m = dynamic_cast<Polar_missions*>(m);
				available_Polar_MissionList.enqueue(n_m);
			}
			if (r && (r->getCM()) % N == N)
			{
				r->setdaysInCheckup(r->getCheckupD());
				Pair<Rover*, int> p(r, r->getdaysInCheckup());
				rovers_InCheckup.insertSorted(p);
			}
			else if (!r->getFinishedMaintenance())
			{
				if (dynamic_cast<EmergencyRovers*>(r))
				{
					EmergencyRovers* n_r = dynamic_cast<EmergencyRovers*>(r);
					n_r->setSpeed(n_r->getSpeed() * 2);
					Pair< EmergencyRovers*, int> p(n_r, n_r->getdaysInMaintenance());
					emergency_Rovers_InMaintenance.insertSorted(p);
				}
				else if (dynamic_cast<MountaneousRovers*>(r))
				{
					MountaneousRovers* n_r = dynamic_cast<MountaneousRovers*>(r);
					n_r->setSpeed(n_r->getSpeed() * 2);
					Pair< MountaneousRovers*, int> p(n_r, n_r->getdaysInMaintenance());
					mountaneous_Rovers_InMaintenance.insertSorted(p);
				}
				else if (dynamic_cast<PolarRovers*>(r))
				{
					PolarRovers* n_r = dynamic_cast<PolarRovers*>(r);
					n_r->setSpeed(n_r->getSpeed() * 2);
					Pair< PolarRovers*, int> p(n_r, n_r->getdaysInMaintenance());
					Polar_Rovers_InMaintenance.insertSorted(p);
				}
			}
			else
			{
				if (dynamic_cast<EmergencyRovers*>(r))
				{
					EmergencyRovers* n_r = dynamic_cast<EmergencyRovers*>(r);
					Pair< EmergencyRovers*, double> p(n_r, n_r->getSpeed());
					available_Emergency_RoversList.insertSorted(p);
				}
				else if (dynamic_cast<MountaneousRovers*>(r))
				{
					MountaneousRovers* n_r = dynamic_cast<MountaneousRovers*>(r);
					Pair< MountaneousRovers*, double> p(n_r, n_r->getSpeed());
					available_Mountaneous_RoversList.insertSorted(p);
				}
				else if (dynamic_cast<PolarRovers*>(r))
				{
					PolarRovers* n_r = dynamic_cast<PolarRovers*>(r);
					Pair< PolarRovers*, double> p(n_r, n_r->getSpeed());
					available_Polar_RoversList.insertSorted(p);
				}
			}
		}
		i++;
	}
}
void MarsStation::check_for_rovers_into_maintainance() {

	// Criteria for moving rovers into maintainance:
	//  1. If it has none completed missions and any number of failed missions.
	//  2. Retrieve the distance that it has travelled in all of its missions and the use this as well.
	//  3. If the ratio of its failed to completed missions is equal to or higher than: 1/3
	//  4. If its speed is under the average speed of its type: indicating that it may be a low-key rover.


	for (int i = 0; i < available_Polar_RoversList.getLength(); i++) {

		PolarRovers* toBeMaintained = available_Polar_RoversList.getEntry(i).get_value();

		int CM = toBeMaintained->getCM();
		int FM = toBeMaintained->getFM();
		double speed = toBeMaintained->getSpeed();
		double distanceTravelled = toBeMaintained->getDistanceTravelled();

		bool conditions[4] = {(CM == 0 && FM != 0), (distanceTravelled / speed >= 75), (speed < AvgSP), (double(CM) / FM >= (1.0 / 3.0)) };
		int yes = 0;
		
		for (int i = 0; i < 4; i++)
			if (conditions[i] == true)
				yes++;

		int days = (yes / 2) * toBeMaintained->getCheckupD();


		// Adding it to the maintenance list if any of the following is satisfied:
		if (yes) {
			toBeMaintained->setMaintenanceDuration(days);
			toBeMaintained->setdaysInMaintenance(days);

			available_Polar_RoversList.removeSorted(available_Polar_RoversList.getEntry(i));
			Pair<PolarRovers*, int> p(toBeMaintained, toBeMaintained->getdaysInMaintenance());
			Polar_Rovers_InMaintenance.insertSorted(p);
		}
	}
	for (int i = 0; i < available_Mountaneous_RoversList.getLength(); i++) {


		MountaneousRovers* toBeMaintained = available_Mountaneous_RoversList.getEntry(i).get_value();
		int CM = toBeMaintained->getCM();
		int FM = toBeMaintained->getFM();
		double speed = toBeMaintained->getSpeed();
		double distanceTravelled = toBeMaintained->getDistanceTravelled();

		bool conditions[4] = { (CM == 0 && FM != 0), (distanceTravelled / speed >= 75), (speed < AvgSM), (double(CM) / FM >= (1.0 / 3.0)) };
		int yes = 0;

		for (int i = 0; i < 4; i++)
			if (conditions[i] == true)
				yes++;

		int days = (yes / 2) * toBeMaintained->getCheckupD();


		// Adding it to the maintenance list if any of the following is satisfied:
		if (yes) {
			toBeMaintained->setMaintenanceDuration(days);
			toBeMaintained->setdaysInMaintenance(days);

			available_Mountaneous_RoversList.removeSorted(available_Mountaneous_RoversList.getEntry(i));
			Pair<MountaneousRovers*, int> p(toBeMaintained, toBeMaintained->getdaysInMaintenance());
			mountaneous_Rovers_InMaintenance.insertSorted(p);
		}
	}
	for (int i = 0; i < available_Emergency_RoversList.getLength(); i++) {

		EmergencyRovers* toBeMaintained = available_Emergency_RoversList.getEntry(i).get_value();
		int CM = toBeMaintained->getCM();
		int FM = toBeMaintained->getFM();
		double speed = toBeMaintained->getSpeed();
		double distanceTravelled = toBeMaintained->getDistanceTravelled();

		bool conditions[4] = { (CM == 0 && FM != 0), (distanceTravelled / speed >= 75), (speed < AvgSE), (double(CM) / FM >= (1.0 / 3.0)) };
		int yes = 0;

		for (int i = 0; i < 4; i++)
			if (conditions[i] == true)
				yes++;

		int days = (yes / 2) * toBeMaintained->getCheckupD();


		// Adding it to the maintenance list if any of the following is satisfied:
		if (yes) {
			toBeMaintained->setMaintenanceDuration(days);
			toBeMaintained->setdaysInMaintenance(days);

			available_Emergency_RoversList.removeSorted(available_Emergency_RoversList.getEntry(i));
			Pair<EmergencyRovers*, int> p(toBeMaintained, toBeMaintained->getdaysInMaintenance());
			emergency_Rovers_InMaintenance.insertSorted(p);
		}
	}

}
void MarsStation::check_for_rovers_outta_maintainance() {

	for (int i = 0; i < emergency_Rovers_InMaintenance.getLength(); i++) {
		Pair<EmergencyRovers*, int>p = emergency_Rovers_InMaintenance.getEntry(i);
		EmergencyRovers* r = p.get_value();
		if (r->getdaysInMaintenance() == 0) {
			emergency_Rovers_InMaintenance.remove(i);
			Pair<EmergencyRovers*, double> p(r, r->getSpeed());
			available_Emergency_RoversList.insertSorted(p);
		}
	}
	for (int i = 0; i < mountaneous_Rovers_InMaintenance.getLength(); i++) {

		Pair<MountaneousRovers*, int>p = mountaneous_Rovers_InMaintenance.getEntry(i);

		MountaneousRovers* r = p.get_value();
		if (r->getdaysInMaintenance() == 0) {
			emergency_Rovers_InMaintenance.remove(i);
			Pair<MountaneousRovers*, double> p(r, r->getSpeed());
			available_Mountaneous_RoversList.insertSorted(p);
		}
	}
	for (int i = 0; i < Polar_Rovers_InMaintenance.getLength(); i++) {
		Pair<PolarRovers*, int>p = Polar_Rovers_InMaintenance.getEntry(i);
		PolarRovers* r = p.get_value();
		if (r->getdaysInMaintenance() == 0) {
			emergency_Rovers_InMaintenance.remove(i);
			Pair<PolarRovers*, double> p(r, r->getSpeed());
			available_Polar_RoversList.insertSorted(p);
		}
	}

}
void MarsStation::check_To_Get_From_Checkup()
{
	int i;
	i = 0;
	while (i != rovers_InCheckup.getLength())
	{
		Pair<Rover*, int>p = rovers_InCheckup.getEntry(i);
		Rover* r = p.get_value();
		if (r->getdaysInCheckup() == 0)
		{
			r->setdaysInCheckup(r->getCheckupD());
			if (dynamic_cast<EmergencyRovers*>(r))
			{
				EmergencyRovers* n_r = dynamic_cast<EmergencyRovers*>(r);
				rovers_InCheckup.remove(i);
				Pair<EmergencyRovers*, double>p(n_r, r->getSpeed());
				available_Emergency_RoversList.insertSorted(p);
			}
			else if (dynamic_cast<MountaneousRovers*>(r))
			{
				MountaneousRovers* n_r = dynamic_cast<MountaneousRovers*>(r);
				rovers_InCheckup.remove(i);
				Pair<MountaneousRovers*, double>p(n_r, r->getSpeed());
				available_Mountaneous_RoversList.insertSorted(p);
			}
			else if (dynamic_cast<PolarRovers*>(r))
			{
				PolarRovers* n_r = dynamic_cast<PolarRovers*>(r);
				rovers_InCheckup.remove(i);
				Pair<PolarRovers*, double>p(n_r, r->getSpeed());
				available_Polar_RoversList.insertSorted(p);
			}
		}
		i++;
	}
}
void MarsStation::increment_Days()
{
	LinkedpriorityQueue<Emergency_missions*, int> available_Emergency_MissionList_temp;
	LinkedQueue <Mountainous_missions*> available_Mountaneous_MissionList_temp;
	LinkedQueue <Polar_missions*> available_Polar_MissionList_temp;

	while (!available_Emergency_MissionList.isEmpty())
	{
		Emergency_missions* m;
		Pair<Emergency_missions*, int> p;
		available_Emergency_MissionList.dequeue(p);
		m = p.get_value();
		m->set_Waiting_Days(m->get_Waiting_Days() + 1);
		Pair<Emergency_missions*, int> n_p(m, m->get_priority());
		available_Emergency_MissionList_temp.enqueue(n_p);

	}
	while (!available_Emergency_MissionList_temp.isEmpty())
	{
		Pair<Emergency_missions*, int> p;
		available_Emergency_MissionList_temp.dequeue(p);
		available_Emergency_MissionList.enqueue(p);
	}

	while (!available_Mountaneous_MissionList.isEmpty())
	{
		Mountainous_missions* m;

		available_Mountaneous_MissionList.dequeue(m);

		m->set_Waiting_Days(m->get_Waiting_Days() + 1);

		available_Mountaneous_MissionList_temp.enqueue(m);

	}
	while (!available_Mountaneous_MissionList_temp.isEmpty())
	{
		Mountainous_missions* m;
		available_Mountaneous_MissionList_temp.dequeue(m);
		available_Mountaneous_MissionList.enqueue(m);
	}

	while (!available_Polar_MissionList.isEmpty())
	{
		Polar_missions* m;

		available_Polar_MissionList.dequeue(m);

		m->set_Waiting_Days(m->get_Waiting_Days() + 1);

		available_Polar_MissionList_temp.enqueue(m);

	}
	while (!available_Polar_MissionList_temp.isEmpty())
	{
		Polar_missions* m;
		available_Polar_MissionList_temp.dequeue(m);
		available_Polar_MissionList_temp.enqueue(m);
	}

	int i = 0;
	while (i != rovers_InCheckup.getLength())
	{
		Pair<Rover*, int> p = rovers_InCheckup.getEntry(i);
		Rover* r = p.get_value();
		r->setdaysInCheckup(r->getdaysInCheckup() - 1);
		i++;
	}

	i = 0;

	while (i != emergency_Rovers_InMaintenance.getLength())
	{
		EmergencyRovers* r;
		Pair<EmergencyRovers*, int> p = emergency_Rovers_InMaintenance.getEntry(i);
		r = p.get_value();
		r->setdaysInMaintenance(r->getdaysInMaintenance() - 1);
		i++;
	}

	i = 0;

	while (i != mountaneous_Rovers_InMaintenance.getLength())
	{
		MountaneousRovers* r;
		Pair<MountaneousRovers*, int>p = mountaneous_Rovers_InMaintenance.getEntry(i);
		r = p.get_value();
		r->setdaysInMaintenance(r->getdaysInMaintenance() - 1);
		i++;
	}

	i = 0;
	while (i != Polar_Rovers_InMaintenance.getLength())
	{
		PolarRovers* r;
		Pair<PolarRovers*, int>p = Polar_Rovers_InMaintenance.getEntry(i);
		r = p.get_value();
		r->setdaysInMaintenance(r->getdaysInMaintenance() - 1);
		i++;
	}

	i = 0;
	today++;
}
void MarsStation::setToday(int d)
{
	this->today = d;
}
int MarsStation::getToday()
{
	return this->today;
}
void MarsStation::Promote_mission(int id)
{
	LinkedQueue <Mountainous_missions*> temp;
	while (available_Mountaneous_MissionList.isEmpty() == false)
	{
		Mountainous_missions* t;
		available_Mountaneous_MissionList.dequeue(t);
		int id_temp = t->get_ID();
		if (id_temp == id)
		{
			Emergency_missions* n_t = new Emergency_missions(t->get_ID(), t->get_Formulation_Day(), t->get_Significance(), t->get_Mission_Duration(), t->get_Target_Location());
			n_t->setAutoPromoted(true);
			
			Add_mission(n_t);
		}
		else
		{
			temp.enqueue(t);
		}
	}
	while (temp.isEmpty() == false)
	{
		Mountainous_missions* t;
		temp.dequeue(t);
		available_Mountaneous_MissionList.enqueue(t);
	}
}
void MarsStation::Add_mission(Mission* ptr)
{
	Emergency_missions* EM = dynamic_cast<Emergency_missions*>(ptr);
	Mountainous_missions* MO = dynamic_cast<Mountainous_missions*>(ptr);
	Polar_missions* PO = dynamic_cast<Polar_missions*>(ptr);
	if (EM != NULL)
	{
		int pr = EM->get_priority();
		Pair<Emergency_missions*, int> p(EM, pr);
		available_Emergency_MissionList.enqueue(p);
	}
	else if (MO != NULL)
	{
		available_Mountaneous_MissionList.enqueue(MO);
	}
	else if (PO != NULL)
	{
		available_Polar_MissionList.enqueue(PO);
	}
}
void MarsStation::LoadInputFile() {

	ifstream fileToLoad;
	string l = "";
	fileToLoad.open("input.txt");

	if (fileToLoad.is_open()) {

		// --------------------------- Getting number of rovers -------------------------- //

		do {
			getline(fileToLoad, l);
		} while (l == "");

		stringstream Mstream(l.substr(0, l.find_first_of(WHITESPACE)));
		Mstream >> M;

		l = l.substr(to_string(M).length() + 1, string::npos);

		stringstream Pstream(l.substr(0, l.find_first_of(WHITESPACE)));
		Pstream >> P;

		l = l.substr(to_string(P).length() + 1, string::npos);

		stringstream Estream(l.substr(0, l.find_first_of(WHITESPACE)));
		Estream >> E;

		// ------------------------------ Getting speeds of rovers ------------------------------ //

		// Temporary arrays for speeds till we design the rovers lists and classes.
		// TO_BE_REPLACED
		SM = new double[M];
		SP = new double[P];
		SE = new double[E];

		// Getting the speeds of rovers of each type.
		for (int i = 0; i < 3; i++) {

			double* temparr = nullptr;
			int tempCount;
			double* tempAvg = nullptr;

			// Choosing which array of speeds to fill.
			switch (i) {
			case 0:
				temparr = SM;
				tempCount = M;
				tempAvg = &AvgSM;
				break;
			case 1:
				temparr = SP;
				tempCount = P;
				tempAvg = &AvgSP;
				break;
			case 2:
				temparr = SE;
				tempCount = E;
				tempAvg = &AvgSE;
				break;
			}

			// Reading the one line needed for speeds and making sure it is not empty.
			do {
				getline(fileToLoad, l);
			} while (l == "");

			for (int j = 0; j < tempCount; j++) {

				string tmp = l.substr(0, l.find_first_of(WHITESPACE));
				stringstream speed(tmp);

				speed >> temparr[j];
				std::cout << temparr[j] << endl;
				*tempAvg = *tempAvg + temparr[j];

				if (j != tempCount - 1)
					l = l.substr(tmp.length() + 1, string::npos);
			}
			std::cout << endl << endl;
		}


		AvgSE = (E == 0) ? 0 : AvgSE / E;
		AvgSM = (M == 0) ? 0 : AvgSM / M;
		AvgSP = (P == 0) ? 0 : AvgSP / P;

		// ------------------------------ Getting number of mission and checkup duration ------------------------------ //
		do {
			getline(fileToLoad, l);
		} while (l == "");

		stringstream Nstream(l.substr(0, l.find_first_of(WHITESPACE)));
		Nstream >> N;
		l = l.substr(to_string(N).length() + 1, string::npos);

		stringstream CMstream(l.substr(0, l.find_first_of(WHITESPACE)));
		CMstream >> CM;
		l = l.substr(to_string(CM).length() + 1, string::npos);

		stringstream CPstream(l.substr(0, l.find_first_of(WHITESPACE)));
		CPstream >> CP;
		l = l.substr(to_string(CP).length() + 1, string::npos);

		stringstream CEstream(l.substr(0, l.find_first_of(WHITESPACE)));
		CEstream >> CE;

		// Creating/appending the rovers to their corresponding list and setting their checkup durations.

		for (int i = 0; i < M; i++) {
			
			MountaneousRovers* toAdd = new MountaneousRovers( SM[i]);

			toAdd->setCheckupD(CM);
			//toAdd->setdaysInMaintenance();
			available_Mountaneous_RoversList.insertSorted(Pair<MountaneousRovers*, double>(toAdd, SM[i]));
		}

		for (int i = 0; i < P; i++) {
			PolarRovers* toAdd = new PolarRovers( SP[i]);
			toAdd->setCheckupD(CP);
			//toAdd->setdaysInMaintenance();
			available_Polar_RoversList.insertSorted(Pair<PolarRovers*, double>(toAdd, SP[i]));
		}

		for (int i = 0; i < E; i++) {
			EmergencyRovers* toAdd = new EmergencyRovers( SE[i]);
			toAdd->setCheckupD(CE);
			//toAdd->setdaysInMaintenance();
			available_Emergency_RoversList.insertSorted(Pair<EmergencyRovers*, double>(toAdd, SE[i]));
		}

		// ------------------------------ Getting auto promotion and number of events ------------------------------ //

		do {
			getline(fileToLoad, l);
		} while (l == "");

		stringstream AutoPstream(l.substr(0, l.find_first_of(WHITESPACE)));
		AutoPstream >> AutoP;

		do {
			getline(fileToLoad, l);
		} while (l == "");

		stringstream EVstream(l.substr(0, l.find_first_of(WHITESPACE)));
		EVstream >> EV;

		// Checking line: to be removed later.
		cout << "AutoP" << AutoP << "E" << EV << endl;


		// ------------------------------ Getting Events ------------------------------ //



		for (int i = 0; i < EV; i++) {

			// Initializing common variables/attributes of events.
			string eventType = "";
			int ED = -1;
			int ID = -1;

			do {
				getline(fileToLoad, l);
			} while (l == "");

			eventType = l.substr(0, l.find_first_of(WHITESPACE));
			l = l.substr(eventType.length() + 1, string::npos);

			// Both these types have the same number of inputs.
			if (eventType == "X" || eventType == "P") {

				stringstream EDstream(l.substr(0, l.find_first_of(WHITESPACE)));
				EDstream >> ED;
				l = l.substr(to_string(ED).length() + 1, string::npos);

				stringstream IDstream(l);
				IDstream >> ID;

				Event* toAppend = nullptr;
				if (eventType == "X")
					toAppend = new CancellationEvent(ID, ED, this);
				else
					toAppend = new PromotionEvent(ID, ED, this);

				eventsList.enqueue(toAppend);
			}

			// This is for the Formulation event type.
			else {
				// For meanings of the variables: check the project documents: section input file.

				string TYP = "";
				double TLOC = 0;
				int SIG, MDUR = 0;

				TYP = l.substr(0, l.find_first_of(WHITESPACE));
				l = l.substr(TYP.length() + 1, string::npos);

				stringstream EDstream(l.substr(0, l.find_first_of(WHITESPACE)));
				EDstream >> ED;
				l = l.substr(to_string(ED).length() + 1, string::npos);

				stringstream IDstream(l.substr(0, l.find_first_of(WHITESPACE)));
				IDstream >> ID;
				l = l.substr(to_string(ID).length() + 1, string::npos);


				TLOC = std::stod(l.substr(0, l.find_first_of(WHITESPACE)));
				l = l.substr(l.substr(0, l.find_first_of(WHITESPACE)).length() + 1, string::npos);
				
				stringstream MDURstream(l.substr(0, l.find_first_of(WHITESPACE)));
				MDURstream >> MDUR;
				l = l.substr(l.substr(0, l.find_first_of(WHITESPACE)).length() + 1, string::npos);

				stringstream SIGstream(l);
				SIGstream >> SIG;

				FormulationEvent* toAppend;
				toAppend = new FormulationEvent(ID, ED, TYP[0], TLOC, MDUR, SIG, this);

				eventsList.enqueue(toAppend);

			}
		}
	}

	delete[] SM, SP, SE;


	fileToLoad.close();
	return;
}
void MarsStation::SaveOutputFile() {

	ofstream outputfile;
	outputfile.open("output.txt");

	if (outputfile.is_open()) {


		outputfile << "CD\tID\tFD\tWD\tED" << endl;
		
		int numOfPolarM = 0, numOfEmergencyM = 0, numOfMntM = 0, total = 0, autoPromotedM = 0;
		double waitingDays = 0, executionDays = 0, avgWaiting = 0, avgExecution = 0;
		
		
		// Printing, and getting number of completed missions.
		for (int i = 0; i < completed_MissionsList.getLength(); i++) {
			Mission* completed = completed_MissionsList.getEntry(i).get_value();
			outputfile << completed->get_Completion_Day() << "\t" << completed->get_ID() << "\t" << completed->get_Formulation_Day() << "\t" << completed->get_Waiting_Days() << "\t" << completed->get_Execution_Days();
			
			waitingDays += completed->get_Waiting_Days();
			executionDays += completed->get_Execution_Days();

			if (dynamic_cast<Polar_missions*> (completed))
				numOfPolarM++;
			else if (dynamic_cast<Emergency_missions*> (completed)) {
				numOfEmergencyM++;

				// For calculation of the percentage of automatically promoted missions later.
				if (dynamic_cast<Emergency_missions*> (completed)->getAutoPromoted() == true)
					autoPromotedM++;
			}
			else
				numOfMntM++;
		}


		total = numOfPolarM + numOfEmergencyM + numOfMntM;
		avgExecution = executionDays / total;
		avgWaiting = waitingDays / total;

		outputfile << endl << endl;
		outputfile << "Missions: " << total << "[M: " << numOfMntM << ", P: " << numOfPolarM << ", E: " << numOfEmergencyM << endl;

		int numOfPolarR = available_Polar_RoversList.getLength() + Polar_Rovers_InMaintenance.getLength();
		int numOfMntR = available_Mountaneous_RoversList.getLength() + mountaneous_Rovers_InMaintenance.getLength();
		int numofEmergencyR = available_Emergency_RoversList.getLength() + emergency_Rovers_InMaintenance.getLength();

		// Uncomment the following part if it is allowed to finish the program while there are rovers in checkup.
		
		/*for (int i = 0; i < rovers_InCheckup.getLength(); i++) {
			if (dynamic_cast<PolarRovers*> (rovers_InCheckup.getEntry(i).get_value()))
				numOfPolarR++;
			else if (dynamic_cast<EmergencyRovers*> (rovers_InCheckup.getEntry(i).get_value()))
				numofEmergencyR++;
			else
				numOfMntR++;
		}*/

		int totalR = numOfPolarR + numofEmergencyR + numOfMntR;
		outputfile << "Rovers: " << totalR << "\t[M: " << numOfMntR << ", P: " << numOfPolarR << ", E: " << numofEmergencyR << "]" << endl;
		outputfile << "Avg Wait = " << avgWaiting << ", Avg Execution = " << avgExecution << endl;
		outputfile << "Auto-promoted: " << autoPromotedM / total << endl;


		outputfile.close();

	}


	return;
}