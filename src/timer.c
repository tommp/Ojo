#include "timer.h"


void restart_timer(Timer* timer){
    clock_gettime(CLOCK_REALTIME, &timer->start);
}

unsigned long return_timediff(Timer* timer){
    struct timespec current;
    clock_gettime(CLOCK_REALTIME, &current);
    long diff = current.tv_nsec - timer->start.tv_nsec;

    return diff / 1000000;
}
