/*
 * light_task.c
 *
 *  Created on: Apr 14, 2019
 *      Author: deepe
 */


#include "light_task.h"
#include "queue_driver.h"


float latest_lux;
uint8_t DEGRADED_MODE_LIGHT = 0;

void LightTask(void *pvParameters)
{
        int8_t ret;
        TimerHandle_t xTimerLight;
        Packet Received;
        xTimerLight= xTimerCreate("LightTimer10Hz", pdMS_TO_TICKS(2000) ,
                                                pdTRUE,  (void*)0, LightTimerHandler);
        ret = apds9301_poweron();
        if(ret == ERROR)
                SendPacket(ALERT,xLOGGER,xLIGHT,"LIGHT SENSOR POWERUP FAIL");

        if((xTimerStart(xTimerLight, 0)) != pdTRUE);

        while(1)
        {
            if(xQueueReceive( xQueue[xLIGHT], &Received, portMAX_DELAY ) != pdTRUE)
                UARTprintf("QUEUE RECEIVE ERROR \n");
            else{
                if(Received.level == HEARTBEAT)
                SendPacket(HEARTBEAT,xHEARTBEAT,xLIGHT,"Heartbeat Sent");
            }
        }
        /* Suspend Task */
        vTaskSuspend(NULL);

}



void LightTimerHandler()
{
    int8_t ret;
    float lux;
    static uint8_t count;

    ret = calculateLuminosity(&lux);
    if(ret == ERROR)
    {
         count++;
         if(count > 10)
         {
        //   SendPacket(ALERT,xLOGGER,xLIGHT,"LIGHT SENSOR FAILURE");
           DEGRADED_MODE_LIGHT = 1;
           count = 0;
         }
         else
         {}
        // SendPacket(STATUS,xLOGGER,xLIGHT,"Trying to Connect Light Sensor");
    }
    else if(ret == SUCCESS)
    {
        DEGRADED_MODE_LIGHT = 0;
    latest_lux = lux;
    //SendPacket(DATA,xLOGGER,xLIGHT,"Lux : %f",latest_lux);
    }
}

