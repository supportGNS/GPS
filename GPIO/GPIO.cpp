#include "GPIO.h"
GPIO::GPIO(uint32_t pin_num){
	pin_number = pin_num;
}

void GPIO::setPinOut(void){
		 nrf_gpio_cfg_output(pin_number);
}

void GPIO::PinHIGH(void){
		 nrf_gpio_pin_set(pin_number);
}

void GPIO::PinLOW(void){
		 nrf_gpio_pin_clear(pin_number);	
}

void GPIO::PinToggle(void){
		nrf_gpio_pin_toggle(pin_number);		
}