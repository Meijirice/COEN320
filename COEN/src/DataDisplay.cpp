/*
* DataDisplay.cpp
*
* Author mikenkie
*/

#include "DataDisplay.h"
#include <iostream>

DataDisplay::DataDisplay() {

}

void DataDisplay:: displayInfoToRadar(Aircraft& aircraft) {
    cout << "Aircraft ID: " << aircraft.getId() 
         << "\nAltitude: " << aircraft.getZ() 
         << "\nLongitude: " << aircraft.getX() 
         << "\nLatitude: " << aircraft.getY() 
         << "\nSpeed: " << aircraft.getSpeedX() << endl;
}