/*
 * lcd_driver.c
 *
 *  Created on: Apr 25, 2019
 *      Author: deepesh
 */


#include"lcd_driver.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"


void InitializeLCD()
{

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        {
        }

        /* Configure pins as output */
        GPIOPinTypeGPIOOutput( GPIO_PORTK_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ); /* GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);*/
        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

}

void LCDWriteChar(char character)
{
    Write(character & 0xF0);
    RS_1;
    Enable_1;
    SysCtlDelay(4 * MICROSECOND);
    Enable_0;
    SysCtlDelay(4 * MICROSECOND);
    Write((character<<4) & 0xF0);
    RS_1;
    Enable_1;
    SysCtlDelay(4 * MICROSECOND);
    Enable_0;
    SysCtlDelay(4 * MICROSECOND);
}


void LCDWriteCommand(uint8_t command)
{
    Write(command);
    RS_0;
    Enable_1;
    SysCtlDelay(4 * MICROSECOND);
    Enable_0;
    SysCtlDelay(10 * MICROSECOND);
    Write((command <<4) & 0xF0);
    Enable_1;
    SysCtlDelay(10 * MICROSECOND);
    Enable_0;
    SysCtlDelay(10 * MICROSECOND);
}

void LCDWriteStr(char* data, int line)
{
    int length = strlen(data);
    switch(line)
    {
    case 1 :
        LCDWriteCommand(FIRST_LINE);
    break;
    case 2 :
        LCDWriteCommand(SECOND_LINE);
    break;
    case 3 :
        LCDWriteCommand(THIRD_LINE);
    break;
    case 4 :
        LCDWriteCommand(FOURTH_LINE);
     break;
    }
    SysCtlDelay(4 * MICROSECOND);
    int i = 0;
    while(length--)
    {
       LCDWriteChar(*(data +i));
       i++;
       SysCtlDelay(4 * MICROSECOND);
    }
}

void TurnOnLCD()
{
    LCDWriteCommand(BIT_MODE_4);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(BIT_MODE_4);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(BIT_MODE_4);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(BIT_MODE_4);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(SYSTEM_SET);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(DISPLAY_ON);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(ENTRY_MODE);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(CLEAR_DISPLAY);
    SysCtlDelay(4 * MICROSECOND);
    LCDWriteCommand(CURSOR_HOME);
    SysCtlDelay(8 * MICROSECOND);

}



void LCDClearDisplay()
{
    SysCtlDelay(4* MICROSECOND);
    LCDWriteCommand(CLEAR_DISPLAY);
    SysCtlDelay(10 * MICROSECOND);
}


