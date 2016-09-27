#include "UART.h"
extern "C"{
#include "app_uart.h"
#include "pca10040.h"
}

UART::UART(uint8_t rx_pin, uint8_t tx_pin, uint32_t baud_rate){
	UART_rx_pin = rx_pin;
	UART_tx_pin = tx_pin;
	Baud_Rate = baud_rate;
	uart_config();
}

uint32_t UART::flush(void)	{
	uint32_t status = app_uart_flush();
	return status;
};

uint32_t UART::close(void)	{
	uint32_t status = app_uart_close();
	return status;
};

void UART::Read(uint8_t * buf, uint8_t NumBytes){
	for(int i=0 ; i<NumBytes; i++){
	app_uart_get(buf+i);
	}
};

void UART::Write(uint8_t * buf, uint8_t NumBytes){
	for(int i=0 ; i<NumBytes; i++){
	app_uart_put(buf[i]);
	}
};

void UART::uart_events_handler(app_uart_evt_t * p_event)
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
void UART::uart_config(void)
{
    uint32_t                     err_code;
    app_uart_comm_params_t comm_params =
    {
        UART_rx_pin,
        UART_tx_pin,
        RTS_PIN_NUMBER,
        CTS_PIN_NUMBER,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud57600
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_events_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);

    APP_ERROR_CHECK(err_code);
}
