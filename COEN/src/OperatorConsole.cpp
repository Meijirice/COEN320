#include "OperatorConsole.h"
#include <string>
#include <iostream>
#include <istream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "cTimer.h"
#include <string.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>


OperatorConsole::OperatorConsole(){
	pthread_mutex_init(&mutex, NULL);
}

OperatorConsole::OperatorConsole(vector<Aircraft*> myList){
	aircraftList = myList;
	pthread_mutex_init(&mutex, NULL);
}

Aircraft* OperatorConsole:: requestAircraftControlChange (int id) {
    for (Aircraft* ar: aircraftList) {
    	if (ar->getId()==id)
    		return ar;
    }
    return nullptr;
}

void OperatorConsole:: operator_console_request() {
	my_data_t myData;
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;
	string request = "false";
	int aircraftIDChangeRequest;

	pthread_mutex_lock(&mutex);

	cout << "Do you wish to access operator console? (yes or no)" << endl;
	cin >> request;

	if (request.compare("yes") == 0) {
		cout << "Please enter the aircraft ID you wish to control:" << endl;
		cin >> aircraftIDChangeRequest;

		aircraft = requestAircraftControlChange(aircraftIDChangeRequest);
		if (aircraft != nullptr)
			sporadic_task();
		else
			cout << "You have entered an invalid aircraft ID. Aircraft change request failed.";
		}

		pthread_mutex_unlock(&mutex);

}

void OperatorConsole::sporadic_task() {
	my_data_t myData;
	string cmd;
	float value;
	cout << "From the options below type which you would like to change: \n"
		 << "POSX\n"<< "POSY\n" <<"POSZ\n" << "SPEEDX\n" << "SPEEDY\n" << "SPEEDZ\n" << "SEND INFO TO RADAR"<<endl;
	cin >> cmd;
	myData.command = cmd;

	cout << "Enter value:" << endl;
	cin >> value;
	myData.data = value;

	printf("Operator Console retrieving your data inputs \n");
	if (myData.command.compare("POSX") == 0) {
		aircraft->setX(myData.data);
	}
	else if (myData.command.compare("POSY") == 0) {
		aircraft->setY(myData.data);
	}
	else if (myData.command.compare("POSZ") == 0) {
		aircraft->setZ(myData.data);
	}
	else if (myData.command.compare("SPEEDX") == 0) {
		aircraft->setSpeedX(myData.data);
	}
	else if (myData.command.compare("SPEEDY") == 0) {
		aircraft->setSpeedY(myData.data);
	}
	else if (myData.command.compare("SPEEDZ") == 0) {
		aircraft->setSpeedZ(myData.data);
	}
	else if (myData.command.compare("SEND INFO TO RADAR") == 0) {
		aircraft->printStatus();;
	}

}
