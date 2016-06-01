#ifndef TIMER_H
#define TIMER_H

#include "GLES2/gl2.h"

#include <time.h>

typedef struct Timer{
    struct timespec start;
}Timer;

void restart_timer(Timer* timer);
unsigned long return_timediff(Timer* timer);


#endif
