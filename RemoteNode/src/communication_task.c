/*
 * communication_task.c
 *
 *  Created on: Apr 21, 2019
 *      Author: Deepesh, Madhumitha
 */
#include <eeprom_driver.h>
#include "tasks_driver.h"
#include "communication_task.h"
#include "uart_driver.h"
#include "eeprom_driver.h"
#include "actuators.h"

Timerstatus CommTimerStop = 1;
heartbeat_t heartbeat = 0;
heartbeat_t HB_Receive_fail = 0;
heartbeat_t heartbeatnotify = 0;
TimerHandle_t xTimerCommunication, xTimerHeartbeat, xTimerEEPROM;
uint8_t Motor_on = 0;
uint8_t DEGRADED_MODE_COMM = 0;
uint32_t address = EEPROM_START_ADDRESS;
uint8_t flag = 0;

void CommunicationTask(void *pvParameters)
{


       UART_TXPacket_t toSend;
       UART_RXPacket_t toReceive;
       memset(&toReceive,0, sizeof(toReceive));
       memset(&toSend,0, sizeof(toSend));


       xTimerCommunication= xTimerCreate("CommunicationTimer10Hz", pdMS_TO_TICKS(10000) ,
                                               pdTRUE,  (void*)0, vCommunicationTimerHandler);

       xTimerHeartbeat = xTimerCreate("HeartBeatTimer10Hz", pdMS_TO_TICKS(5000) ,
                                      pdTRUE,  (void*)0, vHeartbeatTimerHandler);

       xTimerEEPROM = xTimerCreate("EEPROMTimer10Hz", pdMS_TO_TICKS(10000) ,
                                                 pdTRUE,  (void*)0, vEEPROMTimerHandler);

       if((xTimerStart(xTimerHeartbeat, 0)) != pdTRUE)
       {
           UARTprintf("Error Timer create\n");
       }
       if((xTimerStart(xTimerCommunication, 0)) != pdTRUE)
             {
                 UARTprintf("Error Timer create\n");
             }

       while(1)
       {
         //  ProcessModes();
           memset(&toReceive,0, sizeof(toReceive));
            if(ReceivefromControl(&toReceive))
              {

                  switch(toReceive.loglevel)
                     {
                             case HEARTBEAT:
                             {
                                 UARTprintf("Received Heartbeat\n");
                                 heartbeat = 0;
                                 flag = 0;

                                 SendPacket(HEARTBEAT,xLOGGER,xCOMMUNICATION,"Remote Node Heartbeat Received");
                                 if(HB_Receive_fail)
                                     {
                                         UART_TXPacket_t toSend;
                                         memset(&toSend,0, sizeof(UART_TXPacket_t));
                                         xTimerStop(xTimerEEPROM,0);
                                         ReadFromEEPROM(address);
                                         if((xTimerStart(xTimerCommunication, 0)) != pdTRUE)
                                         {
                                             UARTprintf("Error Timer create\n");
                                         }

                                        HB_Receive_fail = 0;
                                   }

                             }
                             break;

                             case DATA:

                                 SendPacket(DATA, xLOGGER,xCOMMUNICATION, "Data Received From Remote");

                              if(toReceive.motorstate == 1)
                                   SendPacket(INFO, xALERT,xCOMMUNICATION,"MOTOR_ON");

                               else if(toReceive.motorstate == 0)
                                   SendPacket(INFO, xALERT,xCOMMUNICATION,"MOTOR_OFF");

                               if(toReceive.buzzerstate == 1)
                                   SendPacket(INFO, xALERT,xCOMMUNICATION,"BUZZER_ON");

                               else if(toReceive.buzzerstate == 0)
                                   SendPacket(INFO, xALERT,xCOMMUNICATION,"BUZZER_OFF");
                                  break;
                    }
                }
       }

       /* Suspend Task */
       vTaskSuspend(NULL);

}

void vCommunicationTimerHandler()
{
   UART_TXPacket_t toSend;
   memset(&toSend,0,sizeof(UART_TXPacket_t));

            toSend.boardID = 0x01;
            toSend.level = DATA;
            toSend.temperature = latest_temperature;
            toSend.light = latest_lux;
            toSend.moisture = latest_moisture ;
            SendtoControl(&toSend);
            SendPacket(INFO,xLOGGER,xCOMMUNICATION,"Packet Sent to Control ");

}
void vHeartbeatTimerHandler()
{
           UART_TXPacket_t toSend;
           ProcessModes();
           memset(&toSend,0,sizeof(UART_TXPacket_t));
           toSend.boardID = 0x01;
           toSend.level = HEARTBEAT;
           SendtoControl(&toSend);
           heartbeat++;
           SendPacket(HEARTBEAT,xLOGGER,xCOMMUNICATION,"Heartbeat Sent to Control");
           if(heartbeat > 5)
           {
               heartbeat = 0;

               HB_Receive_fail =1;
               DEGRADED_MODE_COMM = 1;
               if(flag == 0)
               {
               xTimerStart(xTimerEEPROM, 0);
               xTimerStop(xTimerCommunication,0);
               flag = 1;
               }

               SendPacket(HEARTBEAT_FAIL, xLOGGER, xCOMMUNICATION,"Communication to Remote Failed");
           }

}

void vEEPROMTimerHandler()
{

    UART_TXPacket_t toSend;
    memset(&toSend,0,sizeof(UART_TXPacket_t));
    toSend.boardID = 0x01;
    toSend.level = PREVIOUS_DATA;
    toSend.temperature = latest_temperature;
    toSend.light = latest_lux;
    toSend.moisture = latest_moisture;
    WriteintoEEPROM(&toSend,address);
    address += sizeof(UART_TXPacket_t);
}

void SendtoControl(UART_TXPacket_t *p_pkt)
{
    UARTSend(UART2, (uint8_t*)p_pkt, sizeof(UART_TXPacket_t));

}

uint8_t ReceivefromControl(UART_RXPacket_t *p_pkt)
{
    uint8_t status = 0;
    status = UARTReceive(UART2, (uint8_t*)p_pkt, sizeof(UART_RXPacket_t));
    return status;
}



