/*
 * temperature_task.c
 *
 *  Created on: Apr 14, 2019
 *      Author: deepe
 */



#include"temperature_task.h"
#include "queue_driver.h"

float latest_temperature;
uint8_t DEGRADED_MODE_TEMP = 0;

void TemperatureTask(void *pvParameters)
{
      Packet Received;
       TimerHandle_t xTimerTemperature;

       xTimerTemperature = xTimerCreate("TempTimer10Hz", pdMS_TO_TICKS(2000) ,
                                               pdTRUE,  (void*)0, TemperatureTimerHandler);

       if((xTimerStart(xTimerTemperature, 0)) != pdTRUE);

       while(1)
       {
           if(xQueueReceive( xQueue[xTEMPERATURE], &Received, portMAX_DELAY ) != pdTRUE)
            UARTprintf("QUEUE RECEIVE ERROR \n");
        else{
            if(Received.level == HEARTBEAT)
             SendPacket(HEARTBEAT,xHEARTBEAT,xTEMPERATURE,"Heartbeat Sent");
       }


       
       /* Suspend Task */
       vTaskSuspend(NULL);

}


void TemperatureTimerHandler()
{
       float temperature = 0;
       static uint8_t count;
       int8_t ret;
       ret = (getTemperature(&temperature));
       if(ret == ERROR)
       {
           count++;
           if(count > 10)
           {
         //    SendPacket(ALERT,xLOGGER,xTEMPERATURE,"Temperature Sensor Inactive");
             DEGRADED_MODE_TEMP = 1;
             count = 0;
           }
           else
           {}
          //   SendPacket(STATUS,xLOGGER,xTEMPERATURE,"Trying to Connect Temperature Sensor");
        }

      else
      {
       DEGRADED_MODE_TEMP = 0;
       latest_temperature = temperature;
      //SendPacket(DATA,xLOGGER,xTEMPERATURE,"Temperature : %f",latest_temperature);
      }

}

