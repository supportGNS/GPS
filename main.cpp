#include <stdio.h>
#include "TWI.h"
#include "UART.h"
extern "C"{
#include "boards.h"
#include "app_util_platform.h"
#include "app_uart.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "GPIO.h"
}
//Top_Projects_Keys
#define CPP //Use this to indicate a CPP Project
/*Pins to connect shield. */
#define BUFFER_SIZE 190
#define LORA_TX_PIN 6
#define LORA_RX_PIN 8

#define GPS_ADDR        (0x42U)

#define NUMBER_OF_SAMPLES 256

static volatile bool m_xfer_done = true;

int main(void)
{
GPIO pin(17);
pin.setPinOut();

TWI GPS_TWI(30, 25);
GPS_TWI.init();
nrf_delay_ms(100);
UART uart(LORA_RX_PIN,LORA_TX_PIN,57600);//Rx,Tx
uint8_t buff[256];
uart.Read(buff, 40);
uart.close();

UART uart2(8,6,57600);//Rx,Tx
uart2.Write(buff,40);
uart2.close();	
	
ret_code_t err_code;
uint8_t tx_data = 0xFD;
uint8_t rx_data[2];
uint8_t buf[BUFFER_SIZE];
nrf_delay_ms(100);
        /* Start transaction with a slave with the specified address. */
        do
        {
            __WFE();
        }while(m_xfer_done == false);
				printf("10\n\r");
	        nrf_delay_ms(100);
    while(true)
    {
		err_code = GPS_TWI.Write(GPS_ADDR, &tx_data, sizeof(tx_data));
		err_code = GPS_TWI.Read(GPS_ADDR, (uint8_t*)rx_data, sizeof(rx_data));
		 uint16_t totalBytes = ((uint16_t) rx_data[0] << 8) | rx_data[1];
		  if (!totalBytes) 
			  return 0; // GPS not ready to send data. Return
		  else{
		  while (totalBytes) {
			uint16_t bytes2Read;
			if (totalBytes > BUFFER_SIZE) {
			   bytes2Read = BUFFER_SIZE;
			} else {
			   bytes2Read = totalBytes;
			}
			//bytes = twiReadBytes(gpsAddress, 0xFF, (uint8_t *) buf, bytes2Read);
			tx_data = 0xFF;
			err_code = GPS_TWI.Write(GPS_ADDR, &tx_data, sizeof(tx_data));
			err_code = GPS_TWI.Read(GPS_ADDR, (uint8_t*)buf, bytes2Read);
			nrf_delay_ms(500);
				for (uint8_t i = 0; i < bytes2Read; i++) {
					printf("%c",buf[i]);
				}
			totalBytes -= bytes2Read;
		  }
		  }
        APP_ERROR_CHECK(err_code);
        m_xfer_done = false;
    }
}

/** @} */
