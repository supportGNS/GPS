#include "TWI.h"
extern "C"{
#include "Timers.h"
#include "nrf_drv_twi.h"
#include "app_error.h"
}
const nrf_drv_twi_t TWI::twi_instance = NRF_DRV_TWI_INSTANCE(0);

TWI::TWI(uint32_t SCL_p, uint32_t SDA_p)
{
SCL_pin = SCL_p;
SDA_pin = SDA_p;
}

void TWI::init()
{
    ret_code_t err_code;
    const nrf_drv_twi_config_t twi_config = {
       SCL_pin,//SCL
       SDA_pin,//SDA
       NRF_TWI_FREQ_100K,
       APP_IRQ_PRIORITY_HIGH
    };
    
    err_code = nrf_drv_twi_init(&twi_instance, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&twi_instance);
		nrf_delay_ms(100);
}

ret_code_t TWI::Read(uint8_t addr, uint8_t * buf, uint8_t NumBytes){
	ret_code_t err_code;
	err_code = nrf_drv_twi_rx(&twi_instance, addr, (uint8_t*)buf, NumBytes);
	return err_code;
}

ret_code_t TWI::Write(uint8_t addr, uint8_t * buf, uint8_t NumBytes){
	ret_code_t err_code;
	err_code = nrf_drv_twi_tx(&twi_instance, addr, (uint8_t*)buf, NumBytes, true);
	return err_code;
}