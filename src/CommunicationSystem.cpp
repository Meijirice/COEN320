/*
 * CommunicationSystem.cpp
 *
 *  
 * Author: mikenkie
 */

#include "CommunicationSystem.h"

CommunicationSystem::CommunicationSystem () {}

void CommunicationSystem:: executeChangePositionX (Aircraft& aircraft, float posX) {
    aircraft.setX(posX);
}

void CommunicationSystem:: executeChangePositionY (Aircraft& aircraft, float posY) {
    aircraft.setY(posY);
}

void CommunicationSystem:: executeChangePositionZ (Aircraft& aircraft, float posZ) {
    aircraft.setZ(posZ);
}

void CommunicationSystem:: executeChangeSpeedX (Aircraft& aircraft, float speedX) {
    aircraft.setSpeedX(speedX);
}

void CommunicationSystem:: executeChangeSpeedY (Aircraft& aircraft, float speedY) {
    aircraft.setSpeedY(speedY);
}

void CommunicationSystem:: executeChangeSpeedZ (Aircraft& aircraft, float speedZ) {
    aircraft.setSpeedZ(speedZ);
}
