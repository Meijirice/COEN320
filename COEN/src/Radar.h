#ifndef RADAR_H_
#define RADAR_H_
#include "Aircraft.h"
#include <vector>

using namespace std;

extern bool radar_is_active;

class Radar {
	vector<Aircraft*> aircrafts;
	int list[10][10]={0};


public:
	Radar(vector<Aircraft*> acList);
	Radar();
	void simulation();
	void displayRadarScreen();
	virtual ~Radar();
	vector <Aircraft*> getAircraftVector();

};
#endif /* RADAR_H_ */
