/**
 * @file common.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Contains common functions and variables used by other files
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdlib.h>
#include <mqueue.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

#include "macros.h"

#define CONTROL_NODES 1
#define REMOTE_NODES 1
#define NODES (CONTROL_NODES + REMOTE_NODES)

#define SIZE_OF_RX_PACKET (sizeof(UART_RXPacket_t))
#define SIZE_OF_TX_PACKET (sizeof(UART_TXPacket_t))
#define SIZE_OF_LOG_PACKET (sizeof(LogPacket_t))
#define SIZE_OF_HB_PACKET (sizeof(HeartbeatPacket_t))

volatile sig_atomic_t kill_signal_logger;
volatile sig_atomic_t kill_signal_main;
volatile sig_atomic_t kill_signal_comm;
volatile sig_atomic_t kill_signal_hb;

volatile sig_atomic_t alive_logger;
volatile sig_atomic_t alive_main;
volatile sig_atomic_t alive_comm;
volatile sig_atomic_t alive_hb;
mqd_t mq_log;

mqd_t mq_main;

sem_t semLog;

typedef uint32_t BoardID_t;
typedef uint32_t LogLevel_t;
typedef uint8_t TID_t;
typedef uint32_t MotorState_t;
typedef uint32_t BuzzerState_t;

typedef enum
{
	ERROR,
	DATA,
	STATUS,
	INFO,
	ALERT,
	HEARTBEAT,
	HEARTBEAT_FAIL,
	HEARTBEAT_BACKUP,
	DEGRADED_MODE_1,
	DEGRADED_MODE_2,
	DEGRADED_MODE_3,
	PREVIOUS_DATA
    
} LOG_LEVEL_T;

typedef enum
{
    TID_LOGGER = 0,
    TID_COMM = 1,
    TID_HEARTBEAT = 2,
    TID_MAIN = 3,

} TID_T;

typedef enum
{
    MOTORSTATE_ON  = 2,
    MOTORSTATE_OFF = 1,
    
} MOTOR_STATE_T;

typedef enum
{
	REMOTE_NODE_ID = 1,
	CONTROL_NODE_ID = 0

} NODEID_T;

typedef enum
{
    BUZZERSTATE_ON = 1,
    BUZZERSTATE_OFF = 0,
    
} BUZZERSTATE_T;

typedef struct __attribute__((__packed__))
{
	BoardID_t boardID;
	LogLevel_t loglevel;
    MotorState_t motorstate;
    BuzzerState_t buzzerstate;
    
} UART_TXPacket_t;


#ifdef LO
typedef struct
{
	BoardID_t boardID;
	LogLevel_t loglevel;
    MotorState_t motorstate;
    BuzzerState_t buzzerstate;
    char LCDData[10];

} UART_RXPacket_t;
#endif

typedef struct __attribute__((__packed__))
{
	BoardID_t boardID;
	LogLevel_t loglevel;
    float temperature;
    float light;
    //float humidity;
    uint32_t moisture;

} UART_RXPacket_t;

typedef struct
{
	BoardID_t boardID;
	TID_t TID;
	LogLevel_t loglevel;
	char data[40];

} LogPacket_t;

typedef struct __attribute__((__packed__))
{
	TID_t TID;

} HeartbeatPacket_t;

/**
 * @brief Function to send internal heartbeat to main task
 * 
 * @param tid 
 * @return int 
 */
int send_heartbeat(TID_t tid);

#endif /* COMMON_H_ */
