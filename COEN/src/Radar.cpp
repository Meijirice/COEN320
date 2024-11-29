#include "Radar.h"
#include "Aircraft.h"
#include <iostream>
#include <vector>
#include "cTimer.h"
using namespace std;

Radar::Radar() {
}

Radar::Radar(vector<Aircraft*> airplanes) {
	aircrafts = airplanes;
}

Radar::~Radar() {
	// TODO Auto-generated destructor stub
}

void Radar::displayRadarScreen() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << list[i][j] << " ";
		}
		cout << " " << endl;
	}
	cout << "---------------------" << endl;
}
;

void Radar::simulation() {
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;

	while (true) {
		time = count * period_sec;

		if ((time % 5) == 0) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 11; j++) {
					list[i][j] = 0;
				}
			}
			for (Aircraft *aircraft : aircrafts) {
				int id;
				float x, y, z, speedX, speedY, speedZ;
				bool active;
				aircraft->radarResponse(id, x, y, z, speedX, speedY, speedZ, active);
				int locationX, locationY;

				locationX = x / 10000;
				locationY = y / 10000;
				if (active) {
					if (locationX <= 10 && locationY <= 10 && locationX >= 0 && locationY >= 0) {
						if(locationX == 10 && locationY == 8){
							cout << id;
						}
						list[locationY][locationX] = list[locationY][locationX] + 1;
					}
				}

			}

		}

		count++;
		timer.waitTimer();
	} //end_while

}
