/**
 * @file controlNodeFunctions.h
 * @author Madhumitha Tolakanahalli Pradeep
 *         Deepesh Sonigra
 * @brief unctions related to feedback from Control Node
 * @version 0.1
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019
 */

#ifndef CONTROLNODE_FUNCTIONS_H_
#define CONTROLNODE_FUNCTIONS_H_

#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>

#include "macros.h"
#include "common.h"
#include "comm_txrx.h"
#include "gpio_interrupt.h"

#define MOISTURE_ZERO		0
#define MOISTURE_LOW 		200
#define MOISTURE_OK 		400
#define MOISTURE_HIGH 		1100

#define TEMPERATURE_LOW 	20
#define TEMPERATURE_HIGH 	30

#define LUX_LOW				20
#define LUX_HIGH			100

#define HUMIDITY_LOW		1
#define HUMIDITY_HIGH		20

/**
 * @brief Handler for monitoring heartbeats from Remote Node
 * 
 */
void controlNode_HeartbeatHandler();

/**
 * @brief Handler for processing data packets from Remote Node
 * 
 * @param fd_UART 
 * @param RxPacket 
 * @param TxPacket 
 */
void controlNode_PacketHandler(int fd_UART, UART_RXPacket_t * RxPacket, UART_TXPacket_t * TxPacket);

/**
 * @brief Handler for Processing data from Remote Node
 * 
 * @param TxPacket 
 * @param temperature 
 * @param light 
 * @param moisture 
 */
void controlNode_DataHandler(UART_TXPacket_t * TxPacket, float temperature, float light, uint32_t moisture);

#endif /* CONTROLNODE_FUNCTIONS_H_ */
