extern "C"{
#include "nrf_drv_twi.h"
#include "Timers.h"
#include "app_error.h"
#include "nrf_drv_config.h"
#include "app_util_platform.h"
}

#define SIZE_OF_TWI_TX_BUFFER 190
#define SIZE_OF_TWI_RX_BUFFER 190

#ifndef PER
#define PER

//typedef nrf_drv_twi_t TWI; //Type of TWI instance

class TWI{
	public:
		uint8_t tx_buf[SIZE_OF_TWI_TX_BUFFER];
		uint8_t rx_buf[SIZE_OF_TWI_RX_BUFFER];
		uint8_t NumBytes;
		TWI(uint32_t, uint32_t);
		void init();
		ret_code_t Read(uint8_t addr, uint8_t * rx_buf, uint8_t NumBytes);
		ret_code_t Write(uint8_t addr, uint8_t * tx_buf, uint8_t NumBytes);
	private:
		static const nrf_drv_twi_t twi_instance;
		uint32_t SDA_pin;
		uint32_t SCL_pin;
};
#endif