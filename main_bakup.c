#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_uart.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "MyTime.h"
/*Pins to connect shield. */
#define ARDUINO_I2C_SCL_PIN 26
#define ARDUINO_I2C_SDA_PIN 27
#define BUFFER_SIZE 128

/*UART buffer size. */
#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 1

/*Common addresses definition for accelereomter. */
#define GPS_ADDR        (0x42U)

#define NUMBER_OF_SAMPLES 256

/* Buffer for samples. */
//static int m_sample_buffer[NUMBER_OF_SAMPLES] = {0};
/* Indicates if reading operation from accelerometer has ended. */
static volatile bool m_xfer_done = true;
/* TWI instance. */
static const nrf_drv_twi_t m_twi_GPS = NRF_DRV_TWI_INSTANCE(0);
//unsigned volatile int *(0x040003508)= 30U;                                //PSELSCL  
//unsigned volatile int* 0x04000350C= 7U;                                    //PSELSDA
/**
 * @brief UART events handler.
 */
static void uart_events_handler(app_uart_evt_t * p_event)
{
    switch (p_event->evt_type)
    {
        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}

/**
 * @brief UART initialization.
 */
static void uart_config(void)
{
    uint32_t                     err_code;
    const app_uart_comm_params_t comm_params =
    {
        RX_PIN_NUMBER,
        TX_PIN_NUMBER,
        RTS_PIN_NUMBER,
        CTS_PIN_NUMBER,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud115200
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_events_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);

    APP_ERROR_CHECK(err_code);
}

/**
 * @brief TWI events handler.
 */

/**
 * @brief UART initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;
    printf("1\n");
    const nrf_drv_twi_config_t twi_GPS_config = {
       .scl                = 30,
       .sda                = 25,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };
    
    err_code = nrf_drv_twi_init(&m_twi_GPS, &twi_GPS_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi_GPS);
}

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    uart_config();
   // int a = __GNUC__, c = __GNUC_PATCHLEVEL__;
    printf("\n\rTWI sensor example\r\n");
    twi_init();
       //int m_sample;
    ret_code_t err_code;
    uint8_t tx_data = 0xFD;
	uint8_t rx_data[2];
	uint8_t buf[BUFFER_SIZE];
	printf("9\n\r");
        nrf_delay_ms(100);
        /* Start transaction with a slave with the specified address. */
        do
        {
            __WFE();
        }while(m_xfer_done == false);
//        err_code = nrf_drv_twi_tx(&m_twi_GPS, GPS_ADDR, &reg, sizeof(reg), true);
		//printf("Error Code = %d",(int)err_code);
		//reg = 0xFD;
				printf("10\n\r");
    while(true)
    {
		err_code = nrf_drv_twi_tx(&m_twi_GPS, GPS_ADDR, &tx_data, sizeof(tx_data), true);
		printf("Error code is %d\n\r",(uint)err_code);
		printf("7\n");
		err_code = nrf_drv_twi_rx(&m_twi_GPS, GPS_ADDR, (uint8_t*)rx_data, sizeof(rx_data));
			
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
			err_code = nrf_drv_twi_tx(&m_twi_GPS, GPS_ADDR, &tx_data, sizeof(tx_data), true);
			err_code = nrf_drv_twi_rx(&m_twi_GPS, GPS_ADDR, (uint8_t*)buf, bytes2Read);
			nrf_delay_ms(500);
			for (uint8_t i = 0; i < bytes2Read; i++) {
				printf("%c",buf[i]);
			}
			totalBytes -= bytes2Read;
		  }
		  }
		
		
		//printf("%d%d\n",rx_data[0],rx_data[1]);
        APP_ERROR_CHECK(err_code);
        m_xfer_done = false;
    }
}

/** @} */
