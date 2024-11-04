#ifndef CTIMER_H_
#define CTIMER_H_

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sync.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <stdint.h>

class cTimer {
	int channel_id;
	int connection_id;

	struct sigevent sig_event;
	struct itimerspec timer_spec;
	timer_t timer_id;

	char msg_buffer[100];

	uint64_t cycles_per_sec;
	uint64_t tick_cycles, tock_cycles;

	sigset_t sig_set;
	struct timespec tv;

public:
	cTimer(uint32_t,uint32_t);

	void setTimerSpec(uint32_t,uint32_t);
	void waitTimer();
	void startTimer();
	void tick();
	double tock();
	virtual ~cTimer();

	void wait_next_activation();
	cTimer(uint32_t period_sec, uint32_t period_msec, uint32_t offset_sec,uint32_t offset_msec );
	void set_timer(uint32_t p_sec, uint32_t p_nsec, uint32_t o_sec, uint32_t o_nsec );
};

#endif /* CTIMER_H_ */
