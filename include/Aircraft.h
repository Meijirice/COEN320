/*
 * Aircraft.h
 *
 *  Created on: Apr 2, 2024
 *      Author: mikenkie
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <unistd.h> // For sleep()
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Aircraft {
private:
	pthread_mutex_t mutex;
	int id;
	int arvtime;
	float x, y, z; // Position coordinates
	float speedX, speedY, speedZ; // Speed components in each direction
	bool active;
public:

	// Constructor
	Aircraft(int id, int t, float posX, float posY, float posZ, float speedX,
				float speedY, float speedZ);
	Aircraft(int id);
	Aircraft();

	// Getter for ID
	int getId() const;
	float getY() const; //latitude
	float getX() const; //longitude
	float getZ() const; //altitude
	float getSpeedX() const;
	bool isActive() const;
	// Mutator for Position Coordinates
	void setX(float posX);
	void setY(float posY);
	void setZ(float posZ);

	// Mutators for Speed
	void setSpeedX(float speedX);
	void setSpeedY(float speedY);
	void setSpeedZ(float speedZ);

	// Method to print the current position and speed of the aircraft
	void printStatus() const;
	void radarResponse(int &idOut, float &xOut, float &yOut, float &zOut,
			float &sXOut, float &sYOut, float &sZOut, bool &activeeOut);
	void simulate();
};

#endif /* AIRCRAFT_H_ */
