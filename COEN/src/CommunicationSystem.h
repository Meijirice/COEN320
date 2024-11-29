/*
 * CommunicationSystem.h
 *
 *  
 * Author: mikenkie
 */

#ifndef COMMUNICATIONSYSTEM_H_
#define COMMUNICATIONSYSTEM_H_

#include <iostream>
#include <string>
#include "Aircraft.h"

class CommunicationSystem {
    private:

    public: 
        // Default Constructor
        CommunicationSystem();

        void executeChangePositionX (Aircraft& aircraft, float posX);
        void executeChangePositionY (Aircraft& aircraft, float posY);
        void executeChangePositionZ (Aircraft& aircraft, float posZ);

        void executeChangeSpeedX (Aircraft& aircraft, float speedX);
        void executeChangeSpeedY (Aircraft& aircraft, float speedY);
        void executeChangeSpeedZ (Aircraft& aircraft, float speedZ);
};

#endif
