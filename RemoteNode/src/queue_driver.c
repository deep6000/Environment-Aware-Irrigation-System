/*
 * queue_driver.c
 *
 *  Created on: Apr 17, 2019
 *      Author: deepe
 */

#include "queue_driver.h"

// initialize all queue handle to NULL
QueueHandle_t xQueue[NUM_OF_TASKS] = {NULL};


void CreateQueue()
{


      xQueue[xLOGGER]      =  xQueueCreate( QUEUE_LENGTH_LOGGER, sizeof(Packet));
      xQueue[xTEMPERATURE] =  xQueueCreate( QUEUE_LENGTH_TEMPERATURE, sizeof(Packet));
      xQueue[xLIGHT]       =  xQueueCreate( QUEUE_LENGTH_LIGHT, sizeof(Packet));
      xQueue[xALERT]       =  xQueueCreate(QUEUE_LENGTH_ALERT,sizeof(Packet));
      xQueue[xHEARTBEAT]    =  xQueueCreate( QUEUE_LENGTH_HEARTBEAT, sizeof(Packet));
      xQueue[xMOISTURE]    =  xQueueCreate( QUEUE_LENGTH_MOSITURE, sizeof(Packet));

}


