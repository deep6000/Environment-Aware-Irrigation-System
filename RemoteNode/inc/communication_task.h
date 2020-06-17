/*
 * communication_task.h
 *
 *  Created on: Apr 21, 2019
 *      Author: deepe
 */

#ifndef INC_COMMUNICATION_TASK_H_
#define INC_COMMUNICATION_TASK_H_
#include <stdint.h>
#include <stdio.h>

typedef uint8_t heartbeat_t;
typedef uint8_t Timerstatus;

extern heartbeat_t heartbeat;
extern Timerstatus CommTimerStop;




/**
 * @brief Communication task call back function
 * @param pvParameters
 */
void CommunicationTask(void *pvParameters);

/**
 * @brief Timer callback function for comm task
 * @return void
 */
void vCommunicationTimerHandler();

/**
 * @brief Send packet to control node
 * @param p_pkt
 */
/**
 *@brief Heartbeat TImer Handler sending Heartbeat
 *@return void
 */
void vHeartbeatTimerHandler();

/**
 *
 */
void vEEPROMTimerHandler();
/**
 * @brief Send packet to control node
 * @param p_pkt
 */
void SendtoControl(UART_TXPacket_t *p_pkt);

/**
 * @brief Receive packet from control node
 * @param p_pkt
 * @return
 */
uint8_t ReceivefromControl(UART_RXPacket_t *p_pkt);

#endif /* INC_COMMUNICATION_TASK_H_ */
