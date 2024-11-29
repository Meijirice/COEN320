
#include "fileWriter.h"
#include <iostream>
#include "Aircraft.h"

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
#include <vector>

fileWriter::fileWriter() {

}

fileWriter::~fileWriter() {
	
}

char* fileWriter:: select_input () {
	char* path;
	string x;
	int option;

	cout << "Select the air traffic condition (integer): \n"
	     << "1. Low\n"
		 << "2. Medium\n"
		 << "3. High\n"
		 << "4. Overload\n" << endl;

	cin >> option;

	switch(option) {
	case 1:
		x = "/data/home/input_low.txt";
		path = new char[x.length() + 1];
		copy(x.begin(), x.end(), path);
		break;
	case 2:
		x = "/data/home/input_medium.txt";
		path = new char[x.length() + 1];
		copy(x.begin(), x.end(), path);
		break;
	case 3:
		x = "/data/home/input_high.txt";
		path = new char[x.length() + 1];
		path = copy(x.begin(), x.end(), path);
		break;
	case 4:
		x = "/data/home/input_overload.txt";
		path = new char[x.length() + 1];
		copy(x.begin(), x.end(), path);
		break;
	}

	return path;
}

// To pass the creation of the aircraft to the AIrcraft object
typedef struct _my_aircraft {
	int entrancetime;
	int ID;
	float coordx, coordy, coordz;
	float speedx, speedy, speedz;
} my_aircraft_t;

vector <Aircraft*> fileWriter:: create_aircrafts (char* filep) {
		vector<Aircraft*> aircraft_list;
		my_aircraft_t aircraft_values;
		int input_file;
		int size_read;
		char buffer[3123];
		int index = 0;

		int reset = 1; // The number of lines in text file that defines an aircraft

		// Open file
		input_file = open(filep, O_RDONLY);

		// Read characters from file until end of file is encountered
		while ((size_read = read(input_file, &buffer[index], 1)) > 0) {
			// If the reader reaches the end of the line, else continues to add character to buffer
			if (buffer[index] == '\n' || index == sizeof(buffer) - 1) {
				// Print content read up to newline character or end of buffer
				buffer[index] = '\0'; // Null-terminate the string
				std::cout << "Line: " << buffer << std::endl; //Debug message

				/* Test for error */
				if (size_read == -1)
					perror("Error reading input file.");

				// Extract values
				std::string data;

				int i = 0;
				// We do not want the information that comes before the data. Ex. Time 5. We do not want "Time"
				for (i = 0; buffer[i] != '\0'; ++i) {
					if (buffer[i] == ' ') {
						break;
					}
				}

				// Extra data as a string
				for (int j = i + 1; buffer[j] != '\0'; ++j) {
					data += buffer[j];
				}

				switch (reset) {
				case 1: // Time
					aircraft_values.entrancetime = stoi(data);
					break;
				case 2: // Aircraft ID
					aircraft_values.ID = stoi(data);
					break;
				case 3: // X
					aircraft_values.coordx = stof(data);
					break;
				case 4: // Y
					aircraft_values.coordy = stof(data);
					break;
				case 5: // Z
					aircraft_values.coordz = stof(data);
					break;
				case 6: // Speed X
					aircraft_values.speedx = stof(data);
					break;
				case 7: // Speed Y
					aircraft_values.speedy = stof(data);
					break;
				case 8: // Speed Z
					aircraft_values.speedz = stof(data);

					Aircraft *new_aircraft = new Aircraft(aircraft_values.ID,
							aircraft_values.entrancetime, aircraft_values.coordx,
							aircraft_values.coordy, aircraft_values.coordz,
							aircraft_values.speedx, aircraft_values.speedy,
							aircraft_values.speedz);

					aircraft_list.push_back(new_aircraft);
					reset = 0; // Resets next block of data to make aircraft object
					break;
				}

				reset++;
				index = 0; // Reset index for next line
			} else {
				++index; // Increment index
			}
		}

		close(input_file);

		return aircraft_list;
}

void fileWriter::write_low() {
	int fd;
	int size_written;

	// To find the file navigate in the vmware
	fd = creat("/data/home/input_low.txt", S_IRUSR | S_IWUSR | S_IXUSR);
	std::string info = "Time 5\n";
	info.append("AircraftID 1\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 5\n");
	info.append("AircraftID 2\n");
	info.append("X 100000\n");
	info.append("Y 100000\n");
	info.append("Z 15000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 3\n");
	info.append("X 0\n");
	info.append("Y 100000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 4\n");
	info.append("X 100000\n");
	info.append("Y 0\n");
	info.append("Z 15234\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 20\n");
	info.append("AircraftID 5\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 25000\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	char buffer[info.length() + 1];
	strcpy(buffer, info.c_str());

	size_written = write(fd, buffer, sizeof(buffer));
	if (size_written != sizeof(buffer))
		perror("Error writing low");
}

void fileWriter::write_medium() {
	int fd;
	int size_written;

	fd = creat("/data/home/input_medium.txt", S_IRUSR | S_IWUSR | S_IXUSR);
	std::string info = "Time 5\n";
	info.append("AircraftID 1\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 5\n");
	info.append("AircraftID 2\n");
	info.append("X 100000\n");
	info.append("Y 100000\n");
	info.append("Z 15000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 3\n");
	info.append("X 0\n");
	info.append("Y 100000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 4\n");
	info.append("X 100000\n");
	info.append("Y 0\n");
	info.append("Z 15234\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 20\n");
	info.append("AircraftID 5\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 25000\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	info.append("Time 29\n");
	info.append("AircraftID 6\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 2000\n");
	info.append("SpeedY -2000\n");
	info.append("SpeedZ 2000\n");

	info.append("Time 30\n");
	info.append("AircraftID 7\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 10000\n");
	info.append("SpeedX -100\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 35\n");
	info.append("AircraftID 8\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 41\n");
	info.append("AircraftID 9\n");
	info.append("X 1800\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -130\n");
	info.append("SpeedY 1300\n");
	info.append("SpeedZ 1300\n");

	info.append("Time 45\n");
	info.append("AircraftID 10\n");
	info.append("X 1900\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ -1000\n");

	char buffer[info.length() + 1];
	strcpy(buffer, info.c_str());

	size_written = write(fd, buffer, sizeof(buffer));
	if (size_written != sizeof(buffer))
		perror("Error writing low");
}

void fileWriter::write_high() {
	int fd;
	int size_written;

	// To find the file navigate in the vmware
	fd = creat("/data/home/input_high.txt", S_IRUSR | S_IWUSR | S_IXUSR);

	std::string info = "Time 5\n";
	info.append("AircraftID 1\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 5\n");
	info.append("AircraftID 2\n");
	info.append("X 100000\n");
	info.append("Y 100000\n");
	info.append("Z 15000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 3\n");
	info.append("X 0\n");
	info.append("Y 100000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 4\n");
	info.append("X 100000\n");
	info.append("Y 0\n");
	info.append("Z 15234\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 20\n");
	info.append("AircraftID 5\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 25000\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	info.append("Time 29\n");
	info.append("AircraftID 6\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 2000\n");
	info.append("SpeedY -2000\n");
	info.append("SpeedZ 2000\n");

	info.append("Time 30\n");
	info.append("AircraftID 7\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 10000\n");
	info.append("SpeedX -100\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 35\n");
	info.append("AircraftID 8\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 41\n");
	info.append("AircraftID 9\n");
	info.append("X 1800\n");
	info.append("Y 2000\n");
	info.append("Z 19000\n");
	info.append("SpeedX -130\n");
	info.append("SpeedY 1300\n");
	info.append("SpeedZ 1300\n");

	info.append("Time 45\n");
	info.append("AircraftID 10\n");
	info.append("X 1900\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ -1000\n");

	char buffer[info.length() + 1];
	strcpy(buffer, info.c_str());

	size_written = write(fd, buffer, sizeof(buffer));
	if (size_written != sizeof(buffer))
		perror("Error writing High");
}

void fileWriter::write_overload() {

	int fd;
	int size_written;

	fd = creat("/data/home/input_overload.txt", S_IRUSR | S_IWUSR | S_IXUSR);
	std::string info = "Time 5\n";
	info.append("AircraftID 1\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 5\n");
	info.append("AircraftID 2\n");
	info.append("X 100000\n");
	info.append("Y 100000\n");
	info.append("Z 15000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY -1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 3\n");
	info.append("X 0\n");
	info.append("Y 100000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 200\n");
	info.append("SpeedY 200\n");
	info.append("SpeedZ 0\n");

	info.append("Time 10\n");
	info.append("AircraftID 4\n");
	info.append("X 100000\n");
	info.append("Y 0\n");
	info.append("Z 15234\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 0\n");

	info.append("Time 25\n");
	info.append("AircraftID 5\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	info.append("Time 29\n");
	info.append("AircraftID 6\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 2000\n");
	info.append("SpeedY -2000\n");
	info.append("SpeedZ 2000\n");

	info.append("Time 30\n");
	info.append("AircraftID 7\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 10000\n");
	info.append("SpeedX -100\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 35\n");
	info.append("AircraftID 8\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 41\n");
	info.append("AircraftID 9\n");
	info.append("X 1800\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -130\n");
	info.append("SpeedY 1300\n");
	info.append("SpeedZ 1300\n");

	info.append("Time 45\n");
	info.append("AircraftID 10\n");
	info.append("X 1900\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ -1000\n");

	info.append("Time 46\n");
	info.append("AircraftID 11\n");
	info.append("X 1500\n");
	info.append("Y 1060\n");
	info.append("Z 10100\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 48\n");
	info.append("AircraftID 12\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 49\n");
	info.append("AircraftID 13\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 200\n");
	info.append("SpeedY 200\n");
	info.append("SpeedZ 200\n");

	info.append("Time 51\n");
	info.append("AircraftID 14\n");
	info.append("Y 1245\n");
	info.append("Z 22340\n");
	info.append("SpeedX 2903\n");
	info.append("SpeedY 2903\n");
	info.append("SpeedZ -2903\n");

	info.append("Time 53\n");
	info.append("AircraftID 15\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	info.append("Time 59\n");
	info.append("AircraftID 16\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 2000\n");
	info.append("SpeedY -2000\n");
	info.append("SpeedZ 2000\n");

	info.append("Time 61\n");
	info.append("AircraftID 17\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 10000\n");
	info.append("SpeedX -100\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 63\n");
	info.append("AircraftID 18\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 68\n");
	info.append("AircraftID 19\n");
	info.append("X 1800\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -130\n");
	info.append("SpeedY 1300\n");
	info.append("SpeedZ 1300\n");

	info.append("Time 72\n");
	info.append("AircraftID 20\n");
	info.append("X 1900\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ -1000\n");

	info.append("Time 74\n");
	info.append("AircraftID 21\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 10000\n");
	info.append("SpeedX 100\n");
	info.append("SpeedY 100\n");
	info.append("SpeedZ 100\n");

	info.append("Time 76\n");
	info.append("AircraftID 22\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 150\n");
	info.append("SpeedY 150\n");
	info.append("SpeedZ 150\n");

	info.append("Time 79\n");
	info.append("AircraftID 23\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 200\n");
	info.append("SpeedY 200\n");
	info.append("SpeedZ 200\n");

	info.append("Time 80\n");
	info.append("AircraftID 24\n");
	info.append("Y 1245\n");
	info.append("Z 15234\n");
	info.append("SpeedX 2903\n");
	info.append("SpeedY 2903\n");
	info.append("SpeedZ 2903\n");

	info.append("Time 85\n");
	info.append("AircraftID 25\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 15400\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	info.append("Time 89\n");
	info.append("AircraftID 26\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 2000\n");
	info.append("SpeedY -2000\n");
	info.append("SpeedZ 2000\n");

	info.append("Time 90\n");
	info.append("AircraftID 27\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 15000\n");
	info.append("SpeedX -100\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 91\n");
	info.append("AircraftID 28\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 92\n");
	info.append("AircraftID 29\n");
	info.append("X 1800\n");
	info.append("Y 1900\n");
	info.append("Z 15900\n");
	info.append("SpeedX -130\n");
	info.append("SpeedY 1300\n");
	info.append("SpeedZ 1300\n");

	info.append("Time 95\n");
	info.append("AircraftID 30\n");
	info.append("X 1900\n");
	info.append("Y 1900\n");
	info.append("Z 15900\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ -1000\n");

	info.append("Time 96\n");
	info.append("AircraftID 31\n");
	info.append("X 1500\n");
	info.append("Y 1060\n");
	info.append("Z 15010\n");
	info.append("SpeedX 1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 98\n");
	info.append("AircraftID 32\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 99\n");
	info.append("AircraftID 33\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 200\n");
	info.append("SpeedY 200\n");
	info.append("SpeedZ 200\n");

	info.append("Time 100\n");
	info.append("AircraftID 34\n");
	info.append("Y 1245\n");
	info.append("Z 15340\n");
	info.append("SpeedX 2903\n");
	info.append("SpeedY 2903\n");
	info.append("SpeedZ 2903\n");

	info.append("Time 101\n");
	info.append("AircraftID 35\n");
	info.append("X 1200\n");
	info.append("Y 1200\n");
	info.append("Z 14000\n");
	info.append("SpeedX 1244\n");
	info.append("SpeedY 1244\n");
	info.append("SpeedZ -1244\n");

	info.append("Time 102\n");
	info.append("AircraftID 36\n");
	info.append("X 2000\n");
	info.append("Y 2000\n");
	info.append("Z 20000\n");
	info.append("SpeedX 2000\n");
	info.append("SpeedY -2000\n");
	info.append("SpeedZ 2000\n");

	info.append("Time 103\n");
	info.append("AircraftID 37\n");
	info.append("X 1000\n");
	info.append("Y 1000\n");
	info.append("Z 10000\n");
	info.append("SpeedX -100\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ 1000\n");

	info.append("Time 107\n");
	info.append("AircraftID 38\n");
	info.append("X 1500\n");
	info.append("Y 1500\n");
	info.append("Z 15000\n");
	info.append("SpeedX 1500\n");
	info.append("SpeedY 1500\n");
	info.append("SpeedZ 1500\n");

	info.append("Time 109\n");
	info.append("AircraftID 39\n");
	info.append("X 1800\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -130\n");
	info.append("SpeedY 1300\n");
	info.append("SpeedZ 1300\n");

	info.append("Time 112\n");
	info.append("AircraftID 40\n");
	info.append("X 1900\n");
	info.append("Y 1900\n");
	info.append("Z 19000\n");
	info.append("SpeedX -1000\n");
	info.append("SpeedY 1000\n");
	info.append("SpeedZ -1000\n");
	info.append("0");

	char buffer[info.length() + 1];
	strcpy(buffer, info.c_str());

	size_written = write(fd, buffer, sizeof(buffer));
	if (size_written != sizeof(buffer))
		perror("Error writing overload");
}


