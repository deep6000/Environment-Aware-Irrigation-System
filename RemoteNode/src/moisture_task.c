/*
 * Moisture_task.c
 *
 *  Created on: Apr 27, 2019
 *      Author: deepe
 */

#include"tasks_driver.h"
#include"moisture_task.h"

uint32_t latest_moisture;
uint8_t DEGRADED_MODE_MOISTURE = 0;

void MoistureTask(void *pvParameters)
{

    Packet Received;    
    TimerHandle_t xTimerMoisture;

    xTimerMoisture= xTimerCreate("MoistureTimer10Hz", pdMS_TO_TICKS(2000) ,
                                                pdTRUE,  (void*)0, MoistureTimerHandler);

    if((xTimerStart(xTimerMoisture, 0)) != pdTRUE);
    while(1){
        if(xQueueReceive( xQueue[xMOISTURE], &Received, portMAX_DELAY ) != pdTRUE)
        UARTprintf("QUEUE RECEIVE ERROR \n");
        else{
            if(Received.level == HEARTBEAT)
                SendPacket(HEARTBEAT,xHEARTBEAT,xMOISTURE,"Heartbeat Sent");

        }
        /* Suspend Task */
        vTaskSuspend(NULL);
}


void MoistureTimerHandler()
{
   static int count;
   static uint32_t value = 0;
   value = getADC1Value();
   value = ProcessMoisture(value);
   if(value == 4095)
   {
       count++;
       if(count > 10)
       {
               SendPacket(ALERT,xLOGGER,xMOISTURE,"Moisture Sensor Fail");
                count  = 0;
                DEGRADED_MODE_MOISTURE = 1;
       }
       else
       {
       SendPacket(ALERT,xLOGGER,xMOISTURE," Trying to Connect to Sensor",value);

       }
    }
   else
   {
       latest_moisture = value;
       SendPacket(DATA,xLOGGER,xMOISTURE,"Moisture : %d",value);
       DEGRADED_MODE_MOISTURE = 0;
   }
   if(DEGRADED_MODE_COMM)
   {
       if(latest_moisture < 400)
           MotorState(1);
        else
            MotorState(0);
   }
}

uint32_t ProcessMoisture(uint32_t value)
{
    if(value < 300)
        value = 0;
    if(value < 1000)
        value = value/3;
    if(value> 1500 && value<3000)
        value = value/2;
        if(value> 3700)
            value = 4095;
    return value;
}
