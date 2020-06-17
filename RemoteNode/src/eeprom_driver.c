/*
 * eeprom.c
 *
 *  Created on: May 1, 2019
 *      Author: deepe
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/eeprom.h"
#include "utils/uartstdio.h"
#include "eeprom_driver.h"
#include "common.h"
#include"tasks_driver.h"

typedef struct E2PROM
{
    float value1;
    float value2;
    uint32_t value3;
} E2PROM;

uint8_t EEPROM_FULL = 0;

return_status InitializeEEPROM()
{
    uint16_t count = 0;
    uint32_t returnCode;

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    /*******************************/

    /* EEPROM SETTINGS */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0); // EEPROM activate

    do
    {
        count++;
        if (count > 65535)
          return FAIL;
        returnCode=EEPROMInit(); // EEPROM start
    }
    while(returnCode!=EEPROM_INIT_OK);
    return SUCCESS;
}

return_status WriteintoEEPROM(UART_TXPacket_t *toStore, uint16_t address)
{
    UARTprintf("Address EEPROM writing to is %x\n",address);
    if(address > (EEPROM_START_ADDRESS + (50 * sizeof(UART_TXPacket_t))))
    {
        address = EEPROM_START_ADDRESS;
        EEPROM_FULL = 1;
    }
        EEPROMProgram((uint32_t *)toStore, address, sizeof(UART_TXPacket_t));
    return SUCCESS;
}

return_status ReadFromEEPROM(uint32_t address)
{

    UART_TXPacket_t toSend;
    uint32_t end_address= address;
    uint32_t address_not_full = EEPROM_START_ADDRESS;
    if(EEPROM_FULL)
    {
        while(end_address != (address - sizeof(UART_TXPacket_t)))
        {
            UARTprintf("Address EEPROM reading to is %x\n",address);
        EEPROMRead((uint32_t *)&toSend, address, sizeof(UART_TXPacket_t)); //Read from struct at EEPROM start from 0x0000
        if(address > (EEPROM_START_ADDRESS + (50 * sizeof(UART_TXPacket_t))))
         address = EEPROM_START_ADDRESS;

         SendtoControl(&toSend);
         address  += sizeof(UART_TXPacket_t);
        }
        EEPROM_FULL = 0;
    }
    else
        while(address_not_full != (address -(sizeof(UART_TXPacket_t))))
        {
            UARTprintf("Address EEPROM reading to is %x\n",address_not_full);
            EEPROMRead((uint32_t *)&toSend, address_not_full, sizeof(toSend));
            address_not_full  += sizeof(UART_TXPacket_t);
            SendtoControl(&toSend);
        }
}

