/* Author: Christian Tiriolo
 * Shown during COEN320 tutorials
 */


#include "cTimer.h"

cTimer::cTimer(uint32_t sec, uint32_t msec) {
	channel_id = ChannelCreate(0);
	connection_id = ConnectAttach(0,0,channel_id,0,0);
	if(connection_id == -1){
		std::cerr << "Timer, Connect Attach error : " << errno << "\n";
	}
	
	SIGEV_PULSE_INIT(&sig_event, connection_id, SIGEV_PULSE_PRIO_INHERIT, 1, 0);
	//debugcout << "TIMER pulse initiated" << endl;
	//
	if (timer_create(CLOCK_REALTIME, &sig_event, &timer_id) == -1){
		std::cerr << "Timer, Init error : " << errno << "\n";
	}
	
	setTimerSpec(sec,1000000* msec);
			
	cycles_per_sec = SYSPAGE_ENTRY(qtime)->cycles_per_sec;
	

}

cTimer::cTimer(uint32_t period_sec, uint32_t period_msec, uint32_t offset_sec,uint32_t offset_msec ) {
	const int signal = SIGALRM;

	sigemptyset(&sig_set); // initialize a signal set
	sigaddset(&sig_set, signal); // add SIGALRM to the signal set
	sigprocmask(SIG_BLOCK, &sig_set, NULL); //block the signal


	/* set the signal event a timer expiration */
	memset(&sig_event, 0, sizeof(struct sigevent));
	sig_event.sigev_notify = SIGEV_SIGNAL;
	sig_event.sigev_signo = signal;



	if (timer_create(CLOCK_REALTIME, &sig_event, &timer_id) == -1){
		std::cerr << "Timer, Init error : " << errno << "\n";
	}

	set_timer(period_sec,1000000* period_msec,offset_sec,1000000* offset_msec);//Set the timer offset and period (both expressed in sec and nsec)
}

cTimer::~cTimer() {
	// TODO Auto-generated destructor stub
}

void cTimer::startTimer(){
	timer_settime(timer_id, 0, &timer_spec, NULL);
}
void cTimer::setTimerSpec(uint32_t sec, uint32_t nano){
	timer_spec.it_value.tv_sec = sec;
	timer_spec.it_value.tv_nsec = nano;
	timer_spec.it_interval.tv_sec = sec;
	timer_spec.it_interval.tv_nsec = nano;
	timer_settime(timer_id, 0, &timer_spec, NULL);
}
void cTimer::waitTimer(){
	int rcvid;
	rcvid = MsgReceive(channel_id, &msg_buffer, sizeof(msg_buffer), NULL);
}
void cTimer::tick(){
	tick_cycles = ClockCycles();
}
double cTimer::tock(){
	tock_cycles = ClockCycles();
	return (double)((int)(((double)(tock_cycles-tick_cycles)/cycles_per_sec)*100000))/10;
}

void cTimer::wait_next_activation() {
	int dummy;
	/* suspend calling process until a signal is pending */
	sigwait(&sig_set, &dummy);
}

void cTimer::set_timer(uint32_t p_sec, uint32_t p_nsec, uint32_t o_sec, uint32_t o_nsec ){
	timer_spec.it_value.tv_sec = o_sec;
	timer_spec.it_value.tv_nsec = o_nsec;
	timer_spec.it_interval.tv_sec = p_sec;
	timer_spec.it_interval.tv_nsec = p_nsec;
	timer_settime(timer_id, 0, &timer_spec, NULL);//Start the timer
}


