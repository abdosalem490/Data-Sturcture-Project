#include "MarsStation.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

MarsStation::MarsStation() {
    LoadInputFile();
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
            Emergency_missions* n_t = new Emergency_missions(t->get_ID(),t->get_Formulation_Day(),t->get_Significance(),t->get_Mission_Duration(),t->get_Target_Location());
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
        Pair<Emergency_missions*, int> p(EM,pr);
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

            // Choosing which array of speeds to fill.
            switch (i) {
            case 0:
                temparr = SM;
                tempCount = M;
                break;
            case 1:
                temparr = SP;
                tempCount = P;
                break;
            case 2:
                temparr = SE;
                tempCount = E;
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

                if (j != tempCount - 1)
                    l = l.substr(tmp.length() + 1, string::npos);
            }
        }

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

                cout << eventType << " " << ED << " " << ID << " " << endl;


                // TO DO: ADD CODE HERE TO ADD EVENTS TO THE LIST OF EVENTS.
            }

            // This is for the Formulation event type.
            else {
                // For meanings of the variables: check the project documents: section input file.

                string TYP = "";
                double TLOC, MDUR = 0;
                int SIG = 0;

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

                MDUR = std::stod(l.substr(0, l.find_first_of(WHITESPACE)));
                l = l.substr(l.substr(0, l.find_first_of(WHITESPACE)).length() + 1, string::npos);

                stringstream SIGstream(l);
                SIGstream >> SIG;

                cout << eventType << " " << TYP << " " << ED << " " << ID << " " << TLOC << " " << MDUR << " " << SIG << endl;
                // TO DO: ADD CODE HERE TO ADD EVENTS TO THE LIST OF EVENTS.

            }
        }
    }

    fileToLoad.close();
    return;
}



