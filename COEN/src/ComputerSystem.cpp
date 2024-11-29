#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ComputerSystem.h"
#include "cTimer.h"
#include "Radar.h"
#include <cmath>


using namespace std;

ComputerSystem::ComputerSystem() {
	// TODO Auto-generated constructor stub

}
ComputerSystem::ComputerSystem(vector<Aircraft*> acList, Radar *r, OperatorConsole *oc) {
	aircraftList = acList;
	radar = r;
	opCon = oc;
}

ComputerSystem::~ComputerSystem() {
	// TODO Auto-generated destructor stub
}

void ComputerSystem::simulation() {
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;

	while (true) {
		time = count * period_sec;

		if ((time % 1) == 0) {
			if ((time % 5) == 0) {
				radar->displayRadarScreen();
			}
			for (size_t i = 0; i < aircraftList.size(); ++i) {
				if (aircraftList[i]->isActive()) {
					for (size_t j = i + 1; j < aircraftList.size(); ++j) {
						if (aircraftList[j]->isActive()) {
							if (((fabs(aircraftList[i]->getX()- aircraftList[j]->getX()) <= 3000) &&
								(fabs(aircraftList[i]->getY()- aircraftList[j]->getY())<= 3000)) &&
								(fabs(aircraftList[i]->getZ()- aircraftList[j]->getZ())<= 1000))
							{
								std::cout << "WARNING: Aircraft"
										<< aircraftList[i]->getId()
										<< " and Aircraft"
										<< aircraftList[j]->getId()
										<< " TOO CLOSE.\n";
							}
						}
					}
				}
			}
			if ((time % 21 == 0)) {
				opCon->operator_console_request();
			}
		}
		count++;
		timer.waitTimer();
	} //end_while
}
;
