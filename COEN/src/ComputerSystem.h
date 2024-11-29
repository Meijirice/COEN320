#ifndef SRC_SYSTEM_H_
#define SRC_SYSTEM_H_
#include "Aircraft.h"
#include <vector>
#include "Radar.h"
#include "OperatorConsole.h"


class ComputerSystem {
private:
	vector<Aircraft*> aircraftList;
	Radar* radar;
	OperatorConsole* opCon;

public:
	ComputerSystem();
	ComputerSystem(vector<Aircraft*> aicrafts, Radar* radar, OperatorConsole* operatorC);
	virtual ~ComputerSystem();
	void simulation();
};

#endif /* SRC_SYSTEM_H_ */
