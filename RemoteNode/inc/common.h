/*
 * common.h
 *
 *  Created on: Apr 17, 2019
 *      Author: deepe
 */



#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include <stdio.h>
#include <stdint.h>



typedef enum
{
    FAIL = -1,
    SUCCESS = 1,
}return_status;

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
    PREVIOUS_DATA,
}LOG_LEVEL_t;



typedef enum sensor_status
{
    READ_FAILURE = -1,
    WRITE_FAILURE = -2,
    READ_SUCCESS = 1,
    WRITE_SUCCESS = 2,
}sensor_status;

typedef enum TID_t
{
    xLOGGER         = 0,
    xTEMPERATURE    = 1,
    xLIGHT          = 2,
    xMOISTURE       = 3,
    xALERT          = 4,
    xCOMMUNICATION  = 5,
    xHEARTBEAT      = 6,
}TID_t;

typedef enum
{
    MOTORSTATE_OFF,
    MOTORSTATE_ON,

} MOTOR_STATE_T;

typedef enum
{
    BUZZERSTATE_OFF,
    BUZZERTATE_ON,

} BUZZERSTATE_T;

typedef uint32_t BoardID_t;
typedef uint32_t LogLevel_t;

typedef uint32_t MotorState_t;
typedef uint32_t BuzzerState_t;


typedef struct Packet
{
    TID_t ID;
    LogLevel_t level;
    uint32_t timestamp;
    char message[100];
    char* taskname;
}Packet;

typedef struct  __attribute__((__packed__))
{
    BoardID_t boardID;
   LogLevel_t level;
    float temperature;
    float light;
    uint32_t moisture;

} UART_TXPacket_t;




typedef struct  __attribute__((__packed__))
{
    BoardID_t boardID;
    LogLevel_t loglevel;
    MotorState_t motorstate;
    BuzzerState_t buzzerstate;

} UART_RXPacket_t;


extern uint8_t NORMAL_MODE;
extern uint8_t DEGRADED_MODE_TEMP;
extern uint8_t DEGRADED_MODE_LIGHT;
extern uint8_t DEGRADED_MODE_HUMIDITY;
extern uint8_t DEGRADED_MODE_MOISTURE;
extern uint8_t DEGRADED_MODE_COMM;

/**
 * @brief Send packet to Task ID from to Task ID to
 * @param level
 * @param ID_to
 * @param ID_from
 * @param format
 * @return return status
 */
return_status SendPacket(LogLevel_t level, TID_t ID_to, TID_t ID_from, char * format, ...);

/**
 * @brief Receive packet for task specified
 * @param ID
 * @return Packet
 */
Packet ReceivePacket(TID_t ID);

#endif /* INC_COMMON_H_ */
