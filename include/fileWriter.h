
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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>

class fileWriter {
public:
	fileWriter();
	virtual ~fileWriter();

	void writeLow();
	void writeMed();
	void writeHigh();
	void writeOver();
};

#endif /* FILEWRITER_H_ */
