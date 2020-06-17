/*
 * heartbeat.c
 *
 *  Created on: Apr 27, 2019
 *      Author: deepe
 */

#include"heartbeat_task.h"
#include "queue_driver.h"

TID_t task_active[NUM_OF_TASKS-1];


void HeartbeatTask(void *pvParameters)
{
      Packet Received;
       TimerHandle_t xTimerHeartbeat;

       xTimerHeartbeat = xTimerCreate("HeartbeatTimer10Hz", pdMS_TO_TICKS(1000) ,
                                               pdTRUE,  (void*)0,  HeartbeatTimerHandler);

       if((xTimerStart(xTimerHeartbeat, 0)) != pdTRUE);

       while(1)
       {
            
        if(xQueueReceive( xQueue[xHEARTBEAT], &Received, portMAX_DELAY ) != pdTRUE)
            UARTprintf("QUEUE RECEIVE ERROR \n");
        else
        {
            if(Received.level == HEARTBEAT)
            task_active[task]--;
        }

     }
       }
       /* Suspend Task */
       vTaskSuspend(NULL);

}


void HeartbeatTimerHandler()
{

    for (TID_t task = xLOGGER ; task < xCOMMUNICATION; task ++){
        SendPacket(HEARTBEAT,task,xHEARTBEAT,"Heartbeat Sent");
        task_active[task]++;
        if(task_active[task] > 5)
         UARTprintf("[%dms] [HEARTBEAT]\t\t[ALERT]\t%d task INACTIVE\n", GetTimeMs(), task);

    }
   
    
      
}
