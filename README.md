# Description
In the hope of getting to know more about Mars and the possibility of life on its surface, a
huge number of exploratory missions to different regions of the planet need to be conducted.
Imagine (at some future time) that we have several rovers of different types and capabilities on the
surface of Mars ready to carry out missions to its different regions. There is also a hypothetical
base station which acts as the central point from which the different rovers begin their exploratory
missions and to which they return after mission completion. The base station basically assigns
missions to the different rovers.

# Missions and Rovers

## Missions:
The following pieces of information are available for each mission:
- **Formulation Day**: the day when the mission formulation is finalized and the mission becomes
ready to be assigned to a rover.
- **Mission Type**: There are 3 types of missions: Emergency, Mountainous and Polar missions.
    - Emergency missions must be assigned first before mountainous and polar missions.
    - Mountainous missions are missions to mountainous regions of Mars and must be
    conducted by rovers equipped to navigate in such regions.
    - Polar missions are missions to the polar ice caps of Mars and must be conducted by
    rovers equipped to navigate in such regions.
- **Target Location**: The distance (in kilometers) from the base station to the target location of the
mission.
- **Mission Duration**: The number of days needed to fulfill the mission requirements at the target
location (assumed constant regardless of rover type).
- **Significance**: A number representing the importance of the mission and how beneficial it is (the
higher the number, the more significant it is).

## Rovers:
At startup, the system loads (from a file) information about the available rovers. For each rover, the
system will load the following information:
- **Rover Type**: There are 3 types of rovers: Emergency rovers, Mountainous rovers, and Polar
rovers.
    - **Emergency rovers** are rovers which are over-equipped and ready for emergency
    missions in almost any region.
    - **Mountainous rovers** are rovers which can navigate in mountainous regions.
    - **Polar rovers** are rovers which can navigate in polar regions.
- **Checkup Duration**: The duration (in days) of checkups that a rover needs to perform after
completing N missions.
- **Speed**: in kilometers/hour. (Note that a day on Mars is 25 hours.)

# Missions Assignment Criteria
To determine the next mission to assign (if a rover is available), the following assignment criteria
should be applied for all the formulated un-assigned missions on each day:
1. First, assign **emergency missions** to ANY available rover of any type. However, there is a
priority based on the rover type: first choose from *emergency rovers* THEN *mountainous rovers* THEN *polar rovers*. 
This means that we do not use mountainous rovers unless all
emergency rovers are busy, and we do not use polar rovers unless rovers of all other types
are busy.
2. Second, assign **polar missions** using the available *polar rovers* **ONLY**. If all polar rovers
are busy, wait until one is available.
3. Third, assign **mountainous missions** using any type of rovers *EXCEPT polar rovers*. First
use the available *mountainous rovers* THEN *emergency rovers* (if all mountainous rovers
are busy).
4. If a mission cannot be assigned on the current day, it should wait for the next day. On the
next day, it should be checked whether the mission can be assigned now or not. If not, it
should wait again and so on.
**NOTES:** If missions of a specific type cannot be assigned on the current day, try to assign the
other types (e.g. if polar missions cannot be assigned on the current day, this does NOT mean
not to assign the mountainous missions).
---
This is how we prioritize the assignment of missions of different types, but how will we prioritize the
assignment of missions of the same type?
- **For polar and mountainous missions**, assign them based on a first-come first-served
basis. Missions that are formulated first are assigned first.
- **For emergency missions**, we designed a priority equation for deciding which of the
available emergency missions should be assigned first. Emergency missions with a higher
priority are the ones to be assigned first.
- we developed a reasonable *weighted* priority equation depending on at least the
following factors: the mission formulation day, how far is the mission’s target location, the
mission’s duration, and the mission’s significance.
---
# Simulation Approach & Assumptions
we used incremental day steps. Simulate the changes in the system every 1 day.
## Some Definitions
- **Formulation Day (FD)**:
The day on which the mission is formulated and is ready to be assigned.
- **Waiting Mission**:
The mission that has been formulated (i.e. mission’s FD < current day but the mission is not
assigned yet). On each day, we choose the mission(s) to assign from the waiting
missions.
- **In-Execution Mission**:
The mission that has been assigned to a rover but is not completed yet.
- **Completed Mission**:
The mission that has been completed.
- **Waiting Days (WD)**:
The number of days from the formulation of a mission until it is assigned to a rover.
- **Execution Days (ED)**:
The days that a rover needs to complete a mission (the days it takes to reach the target
location, fulfill mission requirements, and then get back to the base station).
- **Completion Day (CD)**:
The day at which the mission is successfully completed by the rover.
(CD = FD + WD + ED)

## Assumptions
- If the rover is available on day D, it can be assigned to a new mission starting from that day.
- More than one mission can be formulated on the same day. Also, more than one mission
can be assigned to different rovers on the same day as long as there are available rovers.
- A rover can only be executing one mission at a time.
- A rover cannot be assigned a mission during its checkup time
- Checkup duration and rover speed are the same for all rovers of the same type.

# Input/Output File Formats
the program should receive all information to be simulated from an input file and produces an
output file that contains some information and statistics about the missions. This section describes
the format of both files and gives a sample for each.

## The Input File
- First line contains three integers. Each integer represents the total number of rovers of each
type.
    - **M**: for mountainous rovers
    - **P**: for polar rovers
    - **E**: for emergency rovers
- The 2nd line contains three integers:
    - **SM**: is the speed of all mountainous rovers (kilometers/hour)
    - **SP**: is the speed of all polar rovers (kilometers/hour)
    - **SE**: is the speed of all emergency rovers (kilometers/hour)
- The 3rd line contains four integers:
    - **N**: is the number of missions the rover completes before performing a checkup
    - **CM**: is the checkup duration in days for mountainous rovers
    - **CP**: is the checkup duration in days for polar rovers
    - **CE**: is the checkup duration in days for emergency rovers
- Then a line with only one integer **AutoP** which represents the number of days after which a
mountainous mission is automatically promoted to an emergency mission.
- The next line contains a number **E** which represents the number of **events** following this
line.
- Then the input file contains **E** lines (one line for **each event**). An event can be:
    - Formulation of a new mission. Denoted by letter **F**, or
    - Cancellation of an existing mission. Denoted by letter **X**, or
    - Promotion of a mission to be an emergency mission. Denoted by letter **P**.
    **NOTE**: The input lines of all events are *sorted by the event day in ascending* order.

## Events
- **Formulation event line** has the following information:
    - **F** (letter F at the beginning of the sentence) means a mission formulation event.
    - **TYP** is the mission type (*M: mountainous, P: polar, E: emergency*).
    - **ED** is the event day.
    - **ID** is a unique sequence number that identifies each mission.
    - **TLOC** is the mission’s target location (in kilometers from the base station).
    - **MDUR** is the number of days needed to fulfill the mission requirements at target location.
    - **SIG** is the mission’s significance.
- **Cancellation event line** has the following information:
    - **X** (Letter X) means a mission cancellation event.
    - **ED** is the event day.
    - **ID** is the ID of the mission to be canceled. This ID must be of a mountainous mission.
- **Promotion event line** has the following information:
    - **P** (Letter P) means a mission promotion event.
    - **ED** is the event day.
    - **ID** is the ID of the mission to be promoted to emergency. This ID must be of a mountainous mission.

## Sample Input File
```
3   3   2                     ➔ no. of rovers of each type
1   2   2                     ➔ rover speeds of each type (km/h)
3   9   8   7                 ➔ no. of missions before checkup and the checkup durations
25                            ➔ auto promotion limit
8                             ➔ no. of events in this file
F   M   2   1   100   4   5   ➔ formulation event example
F   M   5   2   250   4   4
F   E   5   3   500   6   3
F   P   6   4   900   7   4
X   10  1                     ➔ cancellation event example
F   M   18   5  560   5   9
P   19  2                     ➔ promotion event example
F   P   25   6   190  3   1
```
## The Output File
The output file we are required to produce should contain **M** output lines of the following format:
**CD**   **ID**   **FD**   **WD**   **ED**
which means that the mission identified by sequence number **ID** has been formulated on day **FD**. It
then waited for a *period* **WD** to be assigned. It has then taken **ED** to be completed at the day **CD**.
(Read the “Definitions Section” mentioned above)
The output lines *must be sorted* by **CD** in ascending order. If more than one mission is completed
on the same day, *they should be ordered by ED*.


Then the following statistics should be shown at the end of the file:
1. Total number of missions and number of missions of each type
2. Total number of rovers and number of rovers of each type
3. Average waiting time and average execution time in days
4. Percentage of automatically-promoted missions (relative to the total number of
mountainous missions)

## Sample Output File

The following numbers are just for clarification and are not produced by actual calculations.
```
CD   ID  FD  WD  ED
18   1   7   5   6
44   10  24  2   18
49   4   12  20  17
......................................................
......................................................
Missions: 124 [M: 100, P: 15, E: 9]
Rovers: 9 [M: 5, P: 3, E: 1]
Avg Wait = 12.3, Avg Exec = 25.65
Auto-promoted: 20%
```

# Program Interface
The program can run in one of three modes: interactive, step-by-step, or silent mode. When the
program runs, it should ask the user to select the program mode.

1. **Interactive Mode:** Allows user to monitor the missions and rovers. The program should
print an output like that shown below. In this mode, the program prints the current day then pauses
for an input from the user (“Enter” key for example) to display the output of the next day.

// TODO: add image here

**Output Screen Explanation**

- The numbers shown are the IDs of missions and rovers printed according to their types. The
IDs of **[emergency missions or rovers]** are printed within **[ ]**, the IDs of (**polar ones**) are
printed within **( )**, and the IDs of {**mountainous ones**} are printed within { }.
- In line 3, a notation like **[2/1,...]** means emergency mission #2 is being executed by rover#1
- Other lines are self-explanatory.
- The above screen is just for explanation and is not generated by actual simulation.

2. **Step-By-Step Mode** is identical to the interactive mode except that after each day, the
program w*aits for one second* (not for user input) then resumes automatically.

3. *Silent Mode*, the program produces only an output file (See the “File Formats” section). It
does not print any simulation steps on the console. It just prints the following screen

// TODO: add image here

**NOTE**: No matter what mode of operation the program is running in, the output file should be
produced.

