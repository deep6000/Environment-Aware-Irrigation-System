/*
 * bist.c
 *
 *  Created on: Apr 29, 2019
 *      Author: deepe
 */
#include "bist.h"

uint8_t bist()
{
    size_t count = 0;
    uint8_t flag = 0;
    int8_t ret;
    uint32_t value;
    UART_TXPacket_t toSend;
    UART_RXPacket_t toReceive;
    float temperature, lux;
    DEGRADED_MODE_COMM = 0;
    DEGRADED_MODE_HUMIDITY = 0;
    DEGRADED_MODE_TEMP= 0;
    DEGRADED_MODE_LIGHT = 0;
    DEGRADED_MODE_MOISTURE = 0;

    while(count < 10)
    {
            ret = (getTemperature(&temperature));
            if(ret == ERROR)
            {
              count++;

            }
            else
            {

                break;
            }
    }
    if(count > 9){
        flag |= 0x01;
        UARTprintf("[%dms] [BIST]\t\t[ALERT]\tTEMPERATURE SENSOR INACTIVE\n", GetTimeMs());
        DEGRADED_MODE_TEMP = 1;
    }

    count = 0;
    // LIGHT
    while(count > 10){
        ret = apds9301_poweron();
           if(ret == ERROR)
                count++;
           else
               break;
           
       }
       if(count > 9){
           flag |= 0x02;
           UARTprintf("[%dms] [BIST]\t\t[ALERT]\tLIGHT SENSOR NOT POWERED\n", GetTimeMs());
           DEGRADED_MODE_LIGHT = 1;
       }

       count = 0;
       while(count < 10){
        ret = calculateLuminosity(&lux) ;
        if(ret == ERROR)
            count++;
        else
            break;   
        }
        if(count > 9){
            flag |= 0x02;
            UARTprintf("[%dms] [BIST]\t\t[ALERT]\tLIGHT SENSOR INACTIVE\n", GetTimeMs());
            DEGRADED_MODE_LIGHT = 1;
        }
        count = 0;
        while(count < 10){
            value = getADC1Value();
            value = ProcessMoisture(value);
            if(value == 4095)
            {
                count ++;
            }
            else
            break;
        }
        if(count > 9){
            flag |= 0x04;
            UARTprintf("[%dms] [BIST]\t\t[ALERT]\tMOISTURE SENSOR INACTIVE\n", GetTimeMs());
            DEGRADED_MODE_MOISTURE = 1;
        }
        count = 0;
        toSend.boardID = 0x01;
        toSend.level = HEARTBEAT;
        SendtoControl(&toSend);
        // create 5 secs delay
        vTaskDelay(5000);
        if(ReceivefromControl(&toReceive))
        {
            if(!(toReceive.loglevel == HEARTBEAT))
            UARTprintf("[%dms] [BIST]\t\t[COMM]\t COMM LOGLEVEL INACCURATE\n", GetTimeMs());
        }
        else{
            flag = |= 0x08;
            DEGRADED_MODE_COMM = 1;
        }
          return flag;

        


}



