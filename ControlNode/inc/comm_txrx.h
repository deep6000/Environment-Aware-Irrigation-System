/**
 * @file comm_txrx.h
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief UART Transmit and Receive functions
 * @version 0.1
 * @date 2019-04-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef COMM_TXRX_H_
#define COMM_TXRX_H_

#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>

#include "posixtimers.h"
#include "logger.h"
#include "uart_driver.h"
#include "controlNodeFunctions.h"


extern const char * UARTdevice;
extern int fd_UART;

/**
 * @brief Timer Handler for Comm task
 * 
 */
void comm_task_timer_handler();

/**
 * @brief Comm Function to transmit data over UART to Remote Node
 * 
 * @param TxPacket 
 * @param fd_UART_Tx 
 * @return int 
 */
int comm_trasmit(UART_TXPacket_t * TxPacket, int fd_UART_Tx);

/**
 * @brief Comm Function to receive data over UART from Remote Node
 * 
 * @param RxPacket 
 * @param fd_UART_Rx 
 * @return int 
 */
int comm_recv(UART_RXPacket_t * RxPacket, int fd_UART_Rx);

/**
 * @brief Thread handler for Comm task
 * 
 * @param arg 
 * @return void* 
 */
void * comm_task(void *arg);
#endif /* COMM_TXRX_H_ */
