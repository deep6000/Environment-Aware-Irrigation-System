/*
 * logger_task.c
 *
 *  Created on: Apr 14, 2019
 *      Author: deepesh
 */


#include "logger_task.h"
#include "queue_driver.h"

void LoggerTask(void *pvParameters)
{
    char *level_str[15] = {" ERROR", "DATA","STATUS","INFO","ALERT","HBEAT","HB_FAIL","HB_BACKUP","DMODE1","DMODE2"};

    Packet Received;

    while(1)
    {
        if(xQueueReceive( xQueue[xLOGGER], &Received, portMAX_DELAY ) != pdTRUE)
            UARTprintf("QUEUE RECEIVE ERROR \n");
        else{
            if(Received.level == HEARTBEAT)
             SendPacket(HEARTBEAT,xHEARTBEAT,xLOGGER,"Heartbeat Sent");
            else
                UARTprintf("[%dms] [%s]\t\t[%s]\t %s\n", Received.timestamp,Received.taskname,level_str[Received.level],Received.message);
        }
     }


}
