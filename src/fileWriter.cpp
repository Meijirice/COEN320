
#include <fileWriter.h>
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

fileWriter::fileWriter() {

}

fileWriter::~fileWriter() {
	
}

void fileWriter::writeLow() {
	int fd;
	int size_written;

	// To find the file navigate in the vmware
	fd = creat("input_low.txt", S_IRUSR | S_IWUSR | S_IXUSR);
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

void fileWriter::writeMed() {
	int fd;
	int size_written;

	fd = creat("input_medium.txt", S_IRUSR | S_IWUSR | S_IXUSR);
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

void fileWriter::writeHigh() {
	int fd;
	int size_written;

	// To find the file navigate in the vmware
	fd = creat("input_high.txt", S_IRUSR | S_IWUSR | S_IXUSR);

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

void fileWriter::writeOver() {

	int fd;
	int size_written;

	fd = creat("input_overload.txt", S_IRUSR | S_IWUSR | S_IXUSR);
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
