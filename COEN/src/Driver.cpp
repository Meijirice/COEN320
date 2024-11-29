using namespace std;

#include "Aircraft.h"
#include "Radar.h"
#include "OperatorConsole.h"
#include "CommunicationSystem.h"
#include "DataDisplay.h"
#include "ComputerSystem.h"
#include "fileWriter.h"

#include <vector>
#include <iostream>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "cTimer.h"
#include <sys/dispatch.h>
#include <sys/siginfo.h>
#include <sys/trace.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>

void* aircraftThread(void *arg) {
	Aircraft *aircraft = static_cast<Aircraft*>(arg);
	aircraft->simulate();
	return NULL;
}
void* radarThread(void *arg) {
	Radar *radar = static_cast<Radar*>(arg);
	radar->simulation();
	return NULL;
}

void* systemThread(void *arg) {
	ComputerSystem *system = static_cast<ComputerSystem*>(arg);
	system->simulation();
	return NULL;
}

void* operatorConsoleThread(void *arg) {
	OperatorConsole *operatorConsole = static_cast<OperatorConsole*>(arg);
	return NULL;
}

void* write_to_output (void *arg) {
	vector<Aircraft*> *my_aircraft_list = static_cast<vector<Aircraft*>*>(arg);

	int size_written;
	int fd = creat("/data/home/myOutputFile.txt", S_IRUSR | S_IWUSR | S_IXUSR);

	if (fd != -1) {
			int period_sec = 1;
			cTimer timer(period_sec, 0);

			int time = 0;
			int count = 0;

			while (true) {
				time = count * period_sec;

				if ((time % 6) == 0) {
					for (Aircraft *currentAircraft : *my_aircraft_list) {
						std::string info = "Aircraft ID: "
								+ std::to_string(currentAircraft->getId())
								+ "\nAltitude: "
								+ std::to_string(currentAircraft->getZ())
								+ "\nLongitude: "
								+ std::to_string(currentAircraft->getX())
								+ "\nLatitude: "
								+ std::to_string(currentAircraft->getY())
								+ "\nSpeed: "
								+ std::to_string(currentAircraft->getSpeedX())
								+ "\n";

						char buffer[info.length() + 1];
						strcpy(buffer, info.c_str());

						size_written = write(fd, buffer, sizeof(buffer));
						if (size_written != sizeof(buffer))
							perror("Error writing myfile.dat");
					}
				}
				count++;
				timer.waitTimer();
			}

			close(fd);
		}

		return NULL;
}


int main() {
	fileWriter writer = fileWriter();
	writer.write_low(); // run this once and then comment it out 
	writer.write_medium(); // run this once and then comment it out 
	writer.write_high(); // run this once and then comment it out 
	writer.write_overload(); // run this once and then comment it out 

	// Selecting file input 
	char* file_path = writer.select_input ();

	// aircraft_vector
	vector<Aircraft*> aircraft_vector = writer.create_aircrafts(file_path);

	Radar radar(aircraft_vector);
	OperatorConsole opConsole(aircraft_vector);
	ComputerSystem system(aircraft_vector, &radar, &opConsole);

	vector<pthread_t> aircraft_threads;

	// Create threads for all aircraft stored in the vector
	for (Aircraft* ac : aircraft_vector) {
		pthread_t acthread;
		aircraft_threads.push_back(acthread);
	}
	
	// Create threads
	pthread_t rThread, sThread, ocThread, writeThread;
	for (size_t i = 0; i < aircraft_vector.size(); i++) {
		pthread_create(&aircraft_threads[i], NULL, aircraftThread, aircraft_vector[i]);
	}

	// Start the threads, passing each thread its corresponding aircraft

	pthread_create(&writeThread, NULL, write_to_output, &aircraft_vector);
	pthread_create(&rThread, NULL, radarThread, &radar);
	pthread_create(&sThread, NULL, systemThread, &system);
	pthread_create(&ocThread, NULL, operatorConsoleThread, &opConsole);

	// Wait for the threads to finish
	pthread_join(rThread, NULL);
	pthread_join(ocThread, NULL);
	pthread_join(writeThread, NULL);
	return 0;
}