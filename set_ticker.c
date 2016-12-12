#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include "set_ticker.h"

static int counter = 30;

void setCounter(int count) {
	counter = count;
}

int getCounter() {
	return counter;
}

char *getCounter2() {
	char *buf = (char*)malloc(3*sizeof(char));
	sprintf(buf,"%2d", counter);
	return buf;	
}

int set_ticker(int n_msecs) {
	struct itimerval new_timeset;
	long n_sec, n_usecs;
	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;
	
	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
