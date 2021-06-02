#include "MarsStation.h"
#include "PromotionEvent.h"
#include "CancellationEvent.h"
#include "FormulationEvent.h"
#include "UI.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

MarsStation::MarsStation() {

	// Calling function LoadInputFile() is now moved inside UI to get the file name.
	UI* ourUI = new UI(this);
	SaveOutputFile();
}

// Execution
bool MarsStation::Execution()
{


	increment_Days();

	execute_Events();

	check_For_Failed_Missions();

	check_For_Completed_Rovers_Missions();

	check_for_rovers_into_maintainance();

	check_for_rovers_outta_maintainance();

    check_To_Get_From_Checkup();

	autoPromote();

	Assign_mission();

	if (available_Emergency_MissionList.isEmpty()
		&& available_Mountaneous_MissionList.isEmpty()
		&& available_Polar_MissionList.isEmpty()
		&& eventsList.isEmpty()
		&& inExecution_MissionsList.isEmpty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Assigning missions to rover
void MarsStation::Assign_mission()
{
	if ((available_Emergency_MissionList.isEmpty() == true && available_Mountaneous_MissionList.isEmpty() == true && available_Polar_MissionList.isEmpty() == true)
		|| (available_Emergency_RoversList.isEmpty() == true && available_Polar_RoversList.isEmpty() == true && available_Mountaneous_RoversList.isEmpty() == true && emergency_Rovers_InMaintenance.isEmpty() == true && mountaneous_Rovers_InMaintenance.isEmpty() == true && Polar_Rovers_InMaintenance.isEmpty() == true))
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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

			ptr_mission->set_Completion_Day(days_completion);
			
			
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (available_Mountaneous_RoversList.isEmpty() == false && ptr_mission->get_failed() == false)
		{
			MountaneousRovers* ptr_rover;
			Pair<MountaneousRovers*, double> pair_rover;
			pair_rover = available_Mountaneous_RoversList.getEntry(0);
			available_Mountaneous_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

			ptr_mission->set_Completion_Day(days_completion);
			
			
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (available_Polar_RoversList.isEmpty() == false && ptr_mission->get_failed() == false)
		{
			PolarRovers* ptr_rover;
			Pair<PolarRovers*, double> pair_rover;
			pair_rover = available_Polar_RoversList.getEntry(0);
			available_Polar_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

			ptr_mission->set_Completion_Day(days_completion);
			
			
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (mountaneous_Rovers_InMaintenance.isEmpty() == false && ptr_mission->get_failed() == false)
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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

			ptr_mission->set_Completion_Day(days_completion);
			
			
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (Polar_Rovers_InMaintenance.isEmpty() == false && ptr_mission->get_failed() == false)
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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			// assigning completion days
			
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

			ptr_mission->set_Completion_Day(days_completion);
						
			
			
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (available_Emergency_RoversList.isEmpty() == false && ptr_mission->get_failed() == false)
		{
			EmergencyRovers* ptr_rover;
			Pair<EmergencyRovers*, double> pair_rover;
			pair_rover = available_Emergency_RoversList.getEntry(0);
			available_Emergency_RoversList.remove(0);
			ptr_rover = pair_rover.get_value();
			// assigning mission to rover
			ptr_rover->assignMission(ptr_mission);
			// assigning Execution_Days
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

			ptr_mission->set_Completion_Day(days_completion);
			
			
			//putting mission in exceution
			Pair<Mission*, int> Pair_mission_exceution(ptr_mission, ptr_mission->get_Completion_Day());
			inExecution_MissionsList.insertSorted(Pair_mission_exceution);
			// putting rover in execution
			Pair<Rover*, int> Pair_rover_inMission(ptr_rover, ptr_mission->get_Completion_Day());
			rovers_InMission.insertSorted(Pair_rover_inMission);
		}
		else if (emergency_Rovers_InMaintenance.isEmpty() == false && ptr_mission->get_failed() == false)
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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

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
			int days_Execution = (int)ceil(((2 * ptr_mission->get_Target_Location()) / (25 * ptr_rover->getSpeed())) + ptr_mission->get_Mission_Duration());
			ptr_mission->set_Execution_Days(days_Execution);
			
			
			// assigning completion days
			int days_completion = 0;
			if (ptr_mission->get_failed() == false)
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_Formulation_Day();
			else
				days_completion = ptr_mission->get_Execution_Days() + ptr_mission->get_Waiting_Days() + ptr_mission->get_failed_day();

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
		eventsList.peek(e);
		if (e->getEventDay() != today)
		{
			break;
		}
		eventsList.dequeue(e);
		e->execute();
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


			if (r && r->getCmForCheckup() != 0 && (r->getCmForCheckup() % N == 0))
			{
				r->setdaysInCheckup(r->getCheckupD());
				r->setCMforCheckup(0);
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
void MarsStation::autoPromote()
{
	LinkedQueue <Mountainous_missions*> temp_available_Mountaneous_MissionList;
	while (!available_Mountaneous_MissionList.isEmpty())
	{
		Mountainous_missions* m;
		available_Mountaneous_MissionList.dequeue(m);
		if (m->get_Waiting_Days() == AutoP)
		{
			Emergency_missions* n_m = new Emergency_missions(m->get_ID(), m->get_Formulation_Day(), m->get_Significance(), m->get_Mission_Duration(), m->get_Target_Location());
			n_m->set_Waiting_Days(m->get_Waiting_Days());
			n_m->set_failed(m->get_failed());
			n_m->setAutoPromoted(true);
			Add_mission(n_m);
			n_m = nullptr;

		}
		else
		{
			temp_available_Mountaneous_MissionList.enqueue(m);
		}
	}
	while (!temp_available_Mountaneous_MissionList.isEmpty())
	{
		Mountainous_missions* m;
		temp_available_Mountaneous_MissionList.dequeue(m);
		available_Mountaneous_MissionList.enqueue(m);
	}
}
void MarsStation::check_For_Failed_Missions()
{
	// Generating a random float number between 0 and 1 to act as the probability of mission faliure.
	float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
	
	int i = 0;
	Mission* m;
	Rover* r;

	while (i < inExecution_MissionsList.getLength())
	{
		Pair<Mission*, int>p1 = inExecution_MissionsList.getEntry(i);
		m = p1.get_value();

		// There's a slim 10% chance the mission will fail, ONLY IF it has not failed before.
		if (random < 0.1 && random > 0 && m->get_failed() == false)
		{

			//std::cout << "Mission " << m->get_ID() << " failed on day " << today << std::endl;
			Pair<Rover*, int> p1 = rovers_InMission.getEntry(i);

			// Getting the rover and incrementing the number of its failed missions.
			r = p1.get_value();
			r->incrementFM();

			// Removing missions and rovers from the in execution list.
			inExecution_MissionsList.remove(i);
			rovers_InMission.remove(i);

			// Setting completion day, execution day and failed flag for the mission.
			m->set_Completion_Day(0);
			m->set_Execution_Days(0);
			m->set_failed(true);
			m->set_failed_day(today);

			// Enqueuing the mission into the available mission list.
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

			// Enqueuing the rover into checkup list.
			//rovers_InCheckup
			r->setdaysInCheckup(r->getCheckupD());
			r->setCMforCheckup(0);
			Pair<Rover*, int>pairForCheckup(r, r->getdaysInCheckup());
			rovers_InCheckup.insertSorted(pairForCheckup);
		}
		i++;
	}
}
void MarsStation::check_for_rovers_into_maintainance() {

	// Criteria for moving rovers into maintainance:
	//  1. If it has none completed missions and any number of failed missions.
	//  2. Retrieve the distance that it has travelled in all of its missions and the use this as well.
	//  3. If the ratio of its failed to completed missions is equal to or higher than: 1/3


	for (int i = 0; i < available_Polar_RoversList.getLength(); i++) {

		PolarRovers* toBeMaintained = available_Polar_RoversList.getEntry(i).get_value();

		int CM = toBeMaintained->getTotalCM();
		int FM = toBeMaintained->getFM();
		double speed = toBeMaintained->getSpeed();
		double distanceTravelled = toBeMaintained->getDistanceTravelled();

		bool conditions[3] = { (CM == 0 && FM != 0), (distanceTravelled / speed >= 75), (double(CM) / FM <= (1.0 / 3.0)) };
		int yes = 0;

		for (int i = 0; i < 3; i++)
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
		int CM = toBeMaintained->getTotalCM();
		int FM = toBeMaintained->getFM();
		double speed = toBeMaintained->getSpeed();
		double distanceTravelled = toBeMaintained->getDistanceTravelled();

		bool conditions[3] = { (CM == 0 && FM != 0), (distanceTravelled / speed >= 75), (double(CM) / FM <= (1.0 / 3.0)) };
		int yes = 0;

		for (int i = 0; i < 3; i++)
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
		int CM = toBeMaintained->getTotalCM();
		int FM = toBeMaintained->getFM();
		double speed = toBeMaintained->getSpeed();
		double distanceTravelled = toBeMaintained->getDistanceTravelled();

		bool conditions[3] = { (CM == 0 && FM != 0), (distanceTravelled / speed >= 75), (double(CM) / FM <= (1.0 / 3.0)) };
		int yes = 0;

		for (int i = 0; i < 3; i++)
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
	while (i < rovers_InCheckup.getLength())
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
			n_t->set_Waiting_Days(t->get_Waiting_Days());
			n_t->set_failed(t->get_failed());
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
	fileToLoad.open(inputFileName);

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
				*tempAvg = *tempAvg + temparr[j];

				if (j != tempCount - 1)
					l = l.substr(tmp.length() + 1, string::npos);
			}
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

		int ID = 1;

		for (int i = 0; i < M; i++) {
			
			MountaneousRovers* toAdd = new MountaneousRovers( SM[i]);

			toAdd->setCheckupD(CM);
			//toAdd->setdaysInMaintenance();

			available_Mountaneous_RoversList.insertSorted(Pair<MountaneousRovers*, double>(toAdd, SM[i]));
			toAdd->setID(ID);
			ID++;
		}

		for (int i = 0; i < P; i++) {
			PolarRovers* toAdd = new PolarRovers( SP[i]);
			toAdd->setCheckupD(CP);
			//toAdd->setdaysInMaintenance();
			available_Polar_RoversList.insertSorted(Pair<PolarRovers*, double>(toAdd, SP[i]));
			toAdd->setID(ID);
			ID++;
		}

		for (int i = 0; i < E; i++) {
			EmergencyRovers* toAdd = new EmergencyRovers( SE[i]);
			toAdd->setCheckupD(CE);
			//toAdd->setdaysInMaintenance();
			available_Emergency_RoversList.insertSorted(Pair<EmergencyRovers*, double>(toAdd, SE[i]));
			toAdd->setID(ID);
			ID++;
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
	outputfile.open(outputFileName);

	if (outputfile.is_open()) {


		outputfile << "CD\tID\tFD\tWD\tED" << endl;
		
		int numOfPolarM = 0, numOfEmergencyM = 0, numOfMntM = 0, total = 0, autoPromotedM = 0;
		double waitingDays = 0, executionDays = 0, avgWaiting = 0, avgExecution = 0;
		
		
		// Printing, and getting number of completed missions.
		for (int i = 0; i < completed_MissionsList.getLength(); i++) {
			Mission* completed = completed_MissionsList.getEntry(i).get_value();
			outputfile << completed->get_Completion_Day() << "\t" << completed->get_ID() << "\t" << completed->get_Formulation_Day() << "\t" << completed->get_Waiting_Days() << "\t" << completed->get_Execution_Days();
			
			if (completed->get_failed() == true)
				outputfile << " *";

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

			outputfile << endl;
		}


		total = numOfPolarM + numOfEmergencyM + numOfMntM;
		avgExecution = executionDays / total;
		avgWaiting = waitingDays / total;

		outputfile << endl << endl;
		outputfile << "Missions: " << total << "[M: " << numOfMntM << ", P: " << numOfPolarM << ", E: " << numOfEmergencyM << "]" << endl;

		int numOfPolarR = available_Polar_RoversList.getLength() + Polar_Rovers_InMaintenance.getLength();
		int numOfMntR = available_Mountaneous_RoversList.getLength() + mountaneous_Rovers_InMaintenance.getLength();
		int numofEmergencyR = available_Emergency_RoversList.getLength() + emergency_Rovers_InMaintenance.getLength();

		// Comment the following part if it is NOT allowed to finish the program while there are rovers in checkup.

		for (int i = 0; i < rovers_InCheckup.getLength(); i++) {
			if (dynamic_cast<PolarRovers*> (rovers_InCheckup.getEntry(i).get_value()))
				numOfPolarR++;
			else if (dynamic_cast<EmergencyRovers*> (rovers_InCheckup.getEntry(i).get_value()))
				numofEmergencyR++;
			else
				numOfMntR++;
		}

		int totalR = numOfPolarR + numofEmergencyR + numOfMntR;
		outputfile << "Rovers: " << totalR << "\t[M: " << numOfMntR << ", P: " << numOfPolarR << ", E: " << numofEmergencyR << "]" << endl;
		outputfile << "Avg Wait = " << avgWaiting << ", Avg Execution = " << avgExecution << endl;
		
		// CHECK ON THIS BEFORE DELIVERING THE PROJECT.
		if (total != 0)
			outputfile << "Auto-promoted: " << autoPromotedM / total << endl;


		outputfile << endl << endl;
		outputfile << "* beside any mission indicates that the mission has failed once and got reassigned." << endl;
		outputfile.close();

	}


	return;
}
//============================= methods for returning data to be printed ===================================
void MarsStation::getWaitingMissions(Node<int>*& e, Node<int>*& p, Node<int>*& m)
{
	Node<int>* temp_e = nullptr;
	Node<int>* temp_m = nullptr;
	Node<int>* temp_p = nullptr;

	Node<int>* tail_e = e;
	Node<int>* tail_m = m;
	Node<int>* tail_p = p;

	LinkedpriorityQueue<Emergency_missions*, int> temp_available_Emergency_MissionList;
	LinkedQueue <Mountainous_missions*> temp_available_Mountaneous_MissionList;
	LinkedQueue <Polar_missions*> temp_available_Polar_MissionList;

	if (!available_Emergency_MissionList.isEmpty())	
	{
		while (!available_Emergency_MissionList.isEmpty())
		{
			Pair<Emergency_missions*, int>temp;
			available_Emergency_MissionList.dequeue(temp);
			temp_e = new Node<int>(temp.get_value()->get_ID());
			temp_available_Emergency_MissionList.enqueue(temp);
			if (!e)
			{
				e = tail_e = temp_e;
				temp_e = nullptr;
			}
			else
			{
				tail_e->setNext(temp_e);
				tail_e = temp_e;
				temp_e = nullptr;
			}
		}
		
	}
	while (!temp_available_Emergency_MissionList.isEmpty())
	{
		Pair<Emergency_missions*, int>temp;
		temp_available_Emergency_MissionList.dequeue(temp);
		available_Emergency_MissionList.enqueue(temp);
	}
	if (!available_Polar_MissionList.isEmpty())
	{
		while (!available_Polar_MissionList.isEmpty())
		{
			Polar_missions* temp;
			available_Polar_MissionList.dequeue(temp);
			temp_p = new Node<int>(temp->get_ID());
			temp_available_Polar_MissionList.enqueue(temp);
			if (!p)
			{
				p = tail_p = temp_p;
				temp_p = nullptr;
			}
			else
			{
				tail_p->setNext(temp_p);
				tail_p = temp_p;
				temp_p = nullptr;
			}
		}
	}
	while (!temp_available_Polar_MissionList.isEmpty())
	{
		Polar_missions* temp;
		temp_available_Polar_MissionList.dequeue(temp);
		available_Polar_MissionList.enqueue(temp);
	}
	if (!available_Mountaneous_MissionList.isEmpty())
	{
		while (!available_Mountaneous_MissionList.isEmpty())
		{
			Mountainous_missions* temp;
			available_Mountaneous_MissionList.dequeue(temp);
			temp_m = new Node<int>(temp->get_ID());
			temp_available_Mountaneous_MissionList.enqueue(temp);
			if (!m)
			{
				m = tail_m = temp_m;
				temp_m = nullptr;
			}
			else
			{
				tail_m->setNext(temp_m);
				tail_m = temp_m;
				temp_m = nullptr;
			}
		}
	}
	while (!temp_available_Mountaneous_MissionList.isEmpty())
	{
		Mountainous_missions* temp;
		temp_available_Mountaneous_MissionList.dequeue(temp);
		available_Mountaneous_MissionList.enqueue(temp);
	}
}

void MarsStation::getInExecutionMissionRover(Node<int>*& e_m, Node<int>*& e_r, Node<int>*& p_m, Node<int>*& p_r, Node<int>*& m_m, Node<int>*& m_r)
{
	Node<int>* temp_e_m = nullptr;
	Node<int>* temp_e_r = nullptr;
	Node<int>* temp_p_m = nullptr;
	Node<int>* temp_p_r = nullptr;
	Node<int>* temp_m_m = nullptr;
	Node<int>* temp_m_r = nullptr;

	Node<int>* tail_e_m = e_m;
	Node<int>* tail_e_r = e_r;
	Node<int>* tail_p_m = p_m;
	Node<int>* tail_p_r = p_r;
	Node<int>* tail_m_m = m_m;
	Node<int>* tail_m_r = m_r;

	if (!rovers_InMission.isEmpty() && !inExecution_MissionsList.isEmpty())
	{
		for (int i = 0; i < rovers_InMission.getLength() && i < inExecution_MissionsList.getLength(); i++)
		{
			Mission* m = inExecution_MissionsList.getEntry(i).get_value();
			if (dynamic_cast<Emergency_missions*>(m))
			{
				temp_e_m = new Node<int>(m->get_ID());
				temp_e_r = new Node<int>(rovers_InMission.getEntry(i).get_value()->getID());
				if (!e_m && !e_r)
				{

					e_m =  temp_e_m;
					tail_e_m = e_m;
					e_r =  temp_e_r;
					tail_e_r = e_r;

					temp_e_m = nullptr;
					temp_e_r = nullptr;

				}
				else
				{
					tail_e_m->setNext(temp_e_m);
					tail_e_m = temp_e_m;
					tail_e_r->setNext(temp_e_r);
					tail_e_r = temp_e_r;

					temp_e_m = nullptr;
					temp_e_r = nullptr;
				}
			}
			else if (dynamic_cast<Mountainous_missions*>(m))
			{
				temp_m_m = new Node<int>(m->get_ID());
				temp_m_r = new Node<int>(rovers_InMission.getEntry(i).get_value()->getID());
				if (!m_m && !m_r)
				{
					m_m = temp_m_m;
					tail_m_m = m_m;
					m_r =  temp_m_r;
					tail_m_r = m_r;

					temp_m_m = nullptr;
					temp_m_r = nullptr;
				}
				else
				{

					tail_m_m->setNext(temp_m_m);
					tail_m_m = temp_m_m;
					tail_m_r->setNext(temp_m_r);
					tail_m_r = temp_m_r;


					temp_m_m = nullptr;
					temp_m_r = nullptr;
				}
			}
			else if (dynamic_cast<Polar_missions*>(m))
			{
				temp_p_m = new Node<int>(m->get_ID());
				temp_p_r = new Node<int>(rovers_InMission.getEntry(i).get_value()->getID());
				if (!p_m && !p_r)
				{
					p_m =  temp_p_m;
					tail_p_m = p_m;
					p_r = temp_p_r;
					tail_p_r = p_r;
					temp_p_m = nullptr;
					temp_p_r = nullptr;

				}
				else
				{
					tail_p_m->setNext(temp_p_m);
					tail_p_m = temp_p_m;
					tail_p_r->setNext(temp_p_r);
					tail_p_r = temp_p_r;

					temp_p_m = nullptr;
					temp_p_r = nullptr;
				}
			}
			
			 
			
		}
	}
}

void MarsStation::getAvailableRover(Node<int>*& e, Node<int>*& p, Node<int>*& m)
{
	Node<int>* temp_e = nullptr;
	Node<int>* temp_m = nullptr;
	Node<int>* temp_p = nullptr;

	Node<int>* tail_e = e;
	Node<int>* tail_m = m;
	Node<int>* tail_p = p;

	
	if (!available_Emergency_RoversList.isEmpty())
	{
		for (int i = 0; i < available_Emergency_RoversList.getLength(); i++)
		{
			temp_e = new Node<int>(available_Emergency_RoversList.getEntry(i).get_value()->getID());
			if (!e)
			{
				e = temp_e;
				tail_e = e;
			}
			else
			{
				tail_e->setNext(temp_e);
				tail_e = temp_e;
				temp_e = nullptr;
			}
			
		}
		
	}
	if (!available_Polar_RoversList.isEmpty())
	{
		for (int i = 0; i < available_Polar_RoversList.getLength(); i++)
		{
			temp_p = new Node<int>(available_Polar_RoversList.getEntry(i).get_value()->getID());
			
			if (!p)
			{
				p = temp_p;
				tail_p = p;
			}
			else
			{
				tail_p->setNext(temp_p);
				tail_p = temp_p;
				temp_p = nullptr;
			}
		}
	}
	if (!available_Mountaneous_RoversList.isEmpty())
	{
		for (int i = 0; i < available_Mountaneous_RoversList.getLength(); i++)
		{
			temp_m = new Node<int>(available_Mountaneous_RoversList.getEntry(i).get_value()->getID());

			if (!m)
			{
				m = temp_m;
				tail_m = m;
			}
			else
			{
				tail_m->setNext(temp_m);
				tail_m = temp_m;
				temp_m = nullptr;
			}
		}
	}
}

void MarsStation::getInCheckupRover(Node<int>*& e, Node<int>*& p, Node<int>*& m)
{
	Node<int>* temp_e= nullptr;
	Node<int>* temp_m = nullptr;
	Node<int>* temp_p= nullptr;

	Node<int>* tail_e = e;
	Node<int>* tail_m = m;
	Node<int>* tail_p= p;


	if (!rovers_InCheckup.isEmpty())
	{
		for (int i = 0; i < rovers_InCheckup.getLength() ; i++)
		{
			Rover* m_r = rovers_InCheckup.getEntry(i).get_value();
			if (dynamic_cast<EmergencyRovers*>(m_r))
			{
				temp_e = new Node<int>(m_r->getID());

				if (!e)
				{
					e = tail_e = temp_e;
					temp_e = nullptr;
				}
				else
				{
					tail_e->setNext(temp_e);
					tail_e = temp_e;
					temp_e = nullptr;
				}
			}
			else if (dynamic_cast<MountaneousRovers*>(m_r))
			{
				temp_m = new Node<int>(m_r->getID());
				if (!p)
				{
					m = tail_m = temp_m;
					temp_m = nullptr;

				}
				else
				{
					tail_m->setNext(temp_m);
					tail_m = temp_m;

					temp_m = nullptr;
				}
			}
			else if (dynamic_cast<PolarRovers*>(m_r))
			{
				temp_p = new Node<int>(m_r->getID());



				if (!m)
				{
					m = tail_p = temp_p;

					temp_p = nullptr;
				}
				else
				{
					tail_p->setNext(temp_p);
					tail_p = temp_p;
					temp_p = nullptr;
				}
			}


		}
	}
}
//--------completed nissions in sorted list-----------//
void MarsStation::getCompletedMission(Node<int>*& e, Node<int>*& p, Node<int>*& m)
{
	Node<int>* temp_e = nullptr;
	Node<int>* temp_m = nullptr;
	Node<int>* temp_p = nullptr;

	Node<int>* tail_e = e;
	Node<int>* tail_m = m;
	Node<int>* tail_p = p;

	if (!completed_MissionsList.isEmpty())
	{
		
		for (int i = 0; i < completed_MissionsList.getLength(); i++)
		{
				Mission* mm = completed_MissionsList.getEntry(i).get_value();
				if (dynamic_cast<Emergency_missions*>(mm))
				{
					temp_e = new Node<int>(mm->get_ID());

					if (!e)
					{
						e = tail_e = temp_e;
					}
					else
					{
						tail_e->setNext(temp_e);
						tail_e = temp_e;
						temp_e = nullptr;
					}
				}
				else if (dynamic_cast<Polar_missions*>(mm))
				{
					temp_p = new Node<int>(mm->get_ID());
					if (!p)
					{
						p = tail_p = temp_p;
					}
					else
					{
						tail_p->setNext(temp_p);
						tail_p = temp_p;
						temp_p = nullptr;
					}
				}
				else if(dynamic_cast<Mountainous_missions*>(mm))
				{
					temp_m = new Node<int>(mm->get_ID());
					if (!m)
					{
						m = tail_m = temp_m;
					}
					else
					{
						tail_m->setNext(temp_m);
						tail_m = temp_m;
						temp_m = nullptr;
					}
				}

		}
		
	}
}

void MarsStation::getRoversInMaintenance(Node<int>*& e, Node<int>*& p, Node<int>*& m)
{
	Node<int>* temp_e = nullptr;
	Node<int>* temp_m = nullptr;
	Node<int>* temp_p = nullptr;

	Node<int>* tail_e = e;
	Node<int>* tail_m = m;
	Node<int>* tail_p = p;


	if (!emergency_Rovers_InMaintenance.isEmpty())
	{
		for (int i = 0; i < emergency_Rovers_InMaintenance.getLength(); i++)
		{
			temp_e = new Node<int>(emergency_Rovers_InMaintenance.getEntry(i).get_value()->getID());
			if (!e)
			{
				 e = temp_e;
				 tail_e = e;
			}
			else
			{
				tail_e->setNext(temp_e);
				tail_e = temp_e;
				temp_e = nullptr;
			}

		}

	}
	if (!Polar_Rovers_InMaintenance.isEmpty())
	{
		for (int i = 0; i < Polar_Rovers_InMaintenance.getLength(); i++)
		{
			temp_p = new Node<int>(Polar_Rovers_InMaintenance.getEntry(i).get_value()->getID());

			if (!p)
			{
				 p = temp_p;
				 tail_p = p;
			}
			else
			{
				tail_p->setNext(temp_p);
				tail_p = temp_p;
				temp_p = nullptr;
			}
		}
	}
	if (!mountaneous_Rovers_InMaintenance.isEmpty())
	{
		for (int i = 0; i < mountaneous_Rovers_InMaintenance.getLength(); i++)
		{
			temp_m = new Node<int>(mountaneous_Rovers_InMaintenance.getEntry(i).get_value()->getID());

			if (!m)
			{
				 m = temp_m;
				 tail_m = m;
			}
			else
			{
				tail_m->setNext(temp_m);
				tail_m = temp_m;
				temp_m = nullptr;
			}
		}
	}
}
