/*
 * actuators.c
 *
 *  Created on: Apr 29, 2019
 *      Author: deepesh
 */
#include"actuators.h"
#include "queue_driver.h"


void InitializeActuators()
{


            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
            SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL))
            {
            }


            GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE,GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0 ,0x00);
 }


void AlertTask(void *pvParameters)
{
  Packet Received;
  while(1)
  {
      if(xQueueReceive( xQueue[xALERT], &Received, portMAX_DELAY ) != pdTRUE)
                 UARTprintf("QUEUE RECEIVE ERROR \n");
      UARTprintf("Received Alert task Level is %d\n",Received.level);
      switch(Received.level)
      {
          case INFO:
               if(strcmp(Received.message,"MOTOR_ON")== 0)
                   MotorState(1);
               if(strcmp(Received.message,"MOTOR_OFF") == 0)
                   MotorState(0);
               if(strcmp(Received.message,"BUZZER_ON")== 0)
                   BuzzerState(1);
               if(strcmp(Received.message,"BUZZER_OFF")== 0)
                  BuzzerState(0);
      }

  }
}

void MotorState(uint8_t val)
{
    if(val)
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, GPIO_PIN_0);
    else
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, 0);
}

void BuzzerState(uint8_t val)
{
    if(val)
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_PIN_1);

    else
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1,0);

}

uint8_t ProcessMotor(uint8_t motorstate)
{
    static uint8_t motor_on;
    if(motorstate)
        if(motor_on) return -1;
        else
        {
            motor_on=0;
            return 1;
        }
      else
      {
        if(!motor_on) return -1;
        else
        {
            motor_on = 0;
            return 0;
        }
     }
}


uint8_t ProcessBuzzer(uint8_t buzzerstate)
{
    static uint8_t buzzer_on;
    if(buzzerstate)
        if(buzzer_on) return -1;
        else
        {
            buzzer_on=0;
            return 1;
        }
      else
      {
        if(!buzzer_on)
            return -1;
        else
        {
            buzzer_on = 0;
            return 0;
        }

      }
}

void RedLed(uint8_t state)
{
    if(state)
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5, GPIO_PIN_5);
    else
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5, 0);
}

void YellowLed(uint8_t state)
{
    if(state)
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, GPIO_PIN_4);
    else
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, 0);
}

void GreenLed(uint8_t state)
{
    if(state)
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, GPIO_PIN_3);
    else
        GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, 0);
}

void ProcessModes()
{
    UART_TXPacket_t toSend;
    memset(&toSend,0,sizeof(toSend));
    if((DEGRADED_MODE_TEMP || DEGRADED_MODE_LIGHT  || DEGRADED_MODE_COMM) && DEGRADED_MODE_COMM)
    {
        YellowLed(1);
        RedLed(1);
        GreenLed(0);

    }
    if(DEGRADED_MODE_TEMP || DEGRADED_MODE_LIGHT || DEGRADED_MODE_COMM)
    {

        toSend.boardID = 0x01;
        toSend.level = DEGRADED_MODE_1;
        SendtoControl(&toSend);

        YellowLed(1);
        RedLed(0);
        GreenLed(0);
    }
    if(DEGRADED_MODE_MOISTURE)
    {
        toSend.boardID = 0x01;
        toSend.level = DEGRADED_MODE_2;
        SendtoControl(&toSend);
        YellowLed(0);
        RedLed(1);
        GreenLed(0);
    }
}
