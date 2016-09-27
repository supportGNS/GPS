extern "C"{
#include "app_uart.h"
#include "pca10040.h"
}

/*UART buffer size. */
#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 256

#ifndef _UART_
#define _UART_

class UART{
	public:
		UART(uint8_t rx_pin, uint8_t tx_pin, uint32_t baud_rate);
		uint32_t flush(void);	
	  uint32_t close(void);	
		void Read(uint8_t * buf, uint8_t NumBytes);
		void Write(uint8_t * buf, uint8_t NumBytes);
	private:
		uint8_t UART_rx_pin;
		uint8_t UART_tx_pin;
		uint32_t Baud_Rate;
		void uart_config(void);
		static void uart_events_handler(app_uart_evt_t * p_event);
	  uint8_t NumBytes;
		uint8_t tx_buf[UART_TX_BUF_SIZE];
		uint8_t rx_buf[UART_RX_BUF_SIZE];
};
#endif