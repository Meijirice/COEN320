
#ifndef FILEWRITER_H_
#define FILEWRITER_H_

#include <iostream>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "cTimer.h"
#include <sys/dispatch.h>
#include <sys/siginfo.h>
#include <sys/trace.h>

#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include "Aircraft.h"

class fileWriter {
public:
	fileWriter();
	virtual ~fileWriter();

	void write_low();
	void write_medium();
	void write_high();
	void write_overload();
	vector <Aircraft*> create_aircrafts (char* filep);
	char* select_input ();

};

#endif /* FILEWRITER_H_ */
