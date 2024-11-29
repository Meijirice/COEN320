#ifndef OPERATORCONSOLE_H_
#define OPERATORCONSOLE_H_


#include "Aircraft.h"
#include <vector>


typedef struct _my_data {
	std::string command;
	float data;
} my_data_t;


class OperatorConsole {
    private:
		Aircraft* aircraft;
	    vector<Aircraft*> aircraftList;
        pthread_mutex_t mutex;

    public:
        // Constructor
        OperatorConsole();
        OperatorConsole(vector<Aircraft*> arList);

        // Method to allow controller to change which aircraft they wish to control
        Aircraft* requestAircraftControlChange (int ID);

        void operator_console_request();
        void sporadic_task();

};

#endif
