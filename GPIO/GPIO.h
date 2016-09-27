extern "C"{
#include <nrf_drv_gpiote.h>
#include "nrf_gpiote.h"
}

#ifndef bla
#define bla

class GPIO{
	public:
		GPIO(uint32_t pin_number);
		void setPinOut();
		void PinHIGH();
		void PinLOW();
		void PinToggle();
	private:
		uint32_t pin_number;
};
#endif