/*
 * uart_driver.h
 *
 *  Created on: Apr 12, 2019
 *      Author: deepe
 */

#ifndef INC_UART_DRIVER_H_
#define INC_UART_DRIVER_H_


#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"

#include "driverlib/uart.h"


#define IntializeSTDOUT()               UARTStdioConfig(0, 115200, SYSTEM_CLOCK);
//IntializeUART(UART0, BR_115200,clock);
#define InitializeReceiver(clock)            IntializeUART(UART2, 9600,clock);
#define InitializeCommunication(clock)       IntializeUART(UART3, 9600,clock);



typedef enum BAUDRATE
{
    BR_9600     = 9600,
    BR_38400    = 38400,
    BR_57200    = 57200,
    BR_115200   = 115200,
    BR_230400   = 230400,
    BR_460800   = 460800,
    BR_921600   = 921600,

}BAUDRATE;

typedef enum UART_NO
{
    UART0 = 0,
    UART1 = 1,
    UART2 = 2,
    UART3 = 3,
    UART7 = 7,

}uart_t;

extern uint32_t UART_TYPE[4];
/**
 * @brief Initialize uart port gpios and clocks
 * @param UART_NUM
 * @param BR
 */
void IntializeUART(uart_t UART_NUM, uint32_t clock);

/**
 * @brief Send packet to uart
 * @param UART_NUM
 * @param buffer
 * @param count
 */
void UARTSend(uart_t UART_NUM, uint8_t *buffer, uint32_t count);

/**
 * @brief receive a paket from uart3
 * @param UART_NUM
 * @param buffer
 * @param count
 * @return
 */
uint8_t UARTReceive(uart_t UART_NUM,uint8_t *buffer , int count);


/**
 *
 */
void UART3IntHandler(void);


void UART2IntHandler(void);

#endif /* INC_UART_DRIVER_H_ */
