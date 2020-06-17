/*
 * common.c
 *
 *  Created on: Apr 18, 2019
 *      Author: deepe
 */



#include "common.h"
#include "stdio.h"
#include "clock_driver.h"
#include "queue_driver.h"
#include "tasks_driver.h"

return_status SendPacket(LogLevel_t level, TID_t ID_to, TID_t ID_from, char * format, ...)
{
     Packet Send;
     va_list args;
     memset(&Send,0, sizeof(Send));
     va_start(args,format);
     vsprintf((char*)Send.message,format,args);
     va_end(args);
     Send.ID = ID_from;
     Send.taskname = pcTaskGetName(xHandleTask[ID_from]);
     Send.level = level;
     Send.timestamp = GetTimeMs();

     if(xQueueSend( xQueue[ID_to], &Send, 0U )!= pdTRUE)
     {
          UARTprintf(" %s Queue : Send Error",pcTaskGetName(xHandleTask[ID_from]));
          return FAIL;
     }

     return SUCCESS;
}

Packet ReceivePacket(TID_t ID)
{
    Packet Received;
    // initialize he packet to 0;
    memset(&Received,0, sizeof(Received));

    if(xQueueReceive( xQueue[ID], &Received, portMAX_DELAY ) != pdTRUE)
   {
       UARTprintf("QUEUE RECEIVE ERROR \n");
   }
   return Received;

}
