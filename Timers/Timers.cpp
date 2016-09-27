#include "Timers.h"
extern "C"{
#include <stdio.h> 
#include "compiler_abstraction.h"
#include "nrf.h"
#include "nrf_delay.h"
}

void Delay_msec(uint32_t volatile delay_in_msec){
		 nrf_delay_ms(delay_in_msec);
}
