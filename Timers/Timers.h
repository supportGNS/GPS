extern "C"{
#include "nrf_delay.h"
#include <stdio.h> 
#include "compiler_abstraction.h"
#include "nrf.h"
#include "app_timer.h"
}

#ifndef _TIMER_
#define _TIMER_
class Timer{
	public:
		uint8_t timeout;
};
#endif