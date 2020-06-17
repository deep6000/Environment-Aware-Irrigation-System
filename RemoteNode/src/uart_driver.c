/*
 * uart_driver.c
 *
 *  Created on: Apr 12, 2019
 *      Author: Deepesh Madhumitha
 *      Reference : Example code for Tiva1294
 */
#include "tasks_driver.h"
#include "uart_driver.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"


uint32_t UART_TYPE[4] = {UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE};

void IntializeUART(uart_t UART_NUM, uint32_t clock)
 {
     switch(UART_NUM)
     {
         case UART0:
         {
             // Enable the GPIO Peripheral used by the UART.
             MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
             MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
             while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
             {
             }

             // Configure GPIO Pins for UART mode.
             MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
             MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
             MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
             UARTConfigSetExpClk(UART_TYPE[UART_NUM],120000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
             UARTEnable(UART_TYPE[UART_NUM]);
         }
         break;
         case UART2:
         {
              // Enable the GPIO Peripheral used by the UART.
              ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
              // Enable UART2
              ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
              while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_UART2))
              {
              }
              ROM_IntMasterEnable();

              // Configure GPIO Pins for UART mode.
              GPIOPinConfigure(GPIO_PA6_U2RX);
              GPIOPinConfigure(GPIO_PA7_U2TX);
              ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
             // UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);
              ROM_UARTConfigSetExpClk(UART2_BASE, clock, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
             // ROM_IntEnable(INT_UART2);
             //Enabling UART interrupt for TRansmitter and Receiver.
              //ROM_UARTIntEnable(UART2_BASE, UART_INT_RT | UART_INT_RX | UART_INT_TX);


                  }
         break;

         case UART3:
         {
             // Enable the GPIO Peripheral used by the UART.
             ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
             // Enable UART0
             ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
             while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_UART3))
             {
             }

             // Configure GPIO Pins for UART mode.
             GPIOPinConfigure(GPIO_PA4_U3RX);
             GPIOPinConfigure(GPIO_PA5_U3TX);
             MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);
             UARTClockSourceSet(UART3_BASE, UART_CLOCK_PIOSC);
             MAP_UARTConfigSetExpClk(UART_TYPE[UART_NUM], clock, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

             UARTIntRegister(UART3_BASE, UART3IntHandler);
                               //Enabling UART interrupt for TRansmitter and Receiver.
             UARTIntEnable(UART3_BASE, UART_INT_RT | UART_INT_RX | UART_INT_TX);
             UARTEnable(UART_TYPE[UART_NUM]);

         }
         break;


     }


 }

void UARTSend(uart_t UART_NUM, uint8_t *buffer, uint32_t count)
{
    while(UARTBusy(UART_TYPE[UART_NUM]));
    while(count--)
    {
        UARTCharPut(UART_TYPE[UART_NUM], *buffer++);
    }


}

uint8_t UARTReceive(uart_t UART_NUM, uint8_t *buffer , int count)
{
    UART_RXPacket_t toReceive;
    memset(&toReceive,0,sizeof(UART_RXPacket_t));



    if(UARTCharsAvail(UART_TYPE[UART_NUM]) == false)
    {
            return 0;
    }

        int i = 0, loop = 0;
      uint8_t byte;
//   /   UARTprintf("Receive Packet size = %d\n", count);
      while(i < count && loop  <64 )
         {
             //
             // Read the next character from the UART

             byte = ROM_UARTCharGet(UART_TYPE[UART_NUM]);
             UARTprintf("BYTe Received is %d\n",byte);
             if(byte != -1)
             {
             *(buffer+i) = byte;
             i++;
             }
             else
             {
                 loop++;
             }
         }
     UARTprintf("Received in Function B_ID : %d, Log level = %d , Motor %d , Buzzer = %d\n",\
                toReceive.boardID,toReceive.loglevel,toReceive.motorstate,toReceive.buzzerstate);


//    while(i< count && loop < 64)
//    {
//        uint32_t byte = UARTCharGetNonBlocking(UART_TYPE[UART_NUM]);
//        if(byte != -1 )
//        {
//            *(buffer+i) = byte;
//              UARTprintf("Data = %d or %d\n",byte,*(buffer+i) );
//            loop = 0;
//            i++;
//        }
//        else
//             loop++;
//
//    }
//
//    */
    return 1;

}

void UART3IntHandler(void)
{

    IntMasterDisable();

    uint32_t ui32Status;
    uint32_t stat;

    ui32Status = ROM_UARTIntStatus(UART3_BASE, true);

    ROM_UARTIntClear(UART3_BASE, ui32Status);

    while(ROM_UARTCharsAvail(UART3_BASE))
       {
           //
           // Read the next character from the UART and write it back to the UART.
           //
           //UARTprintf("Msg recv is %c", ROM_UARTCharGetNonBlocking(UART3_BASE));
           stat = ROM_UARTCharGet(UART3_BASE);

        UARTprintf(" Char = %d\n",stat);
    }
    IntMasterEnable();

}

//void UART2IntHandler(void)
//{
//    uint8_t *buffer;
//    IntMasterDisable();
//    UART_RXPacket_t toReceive;
//    memset(&toReceive,0,sizeof(UART_RXPacket_t));
//    buffer = &toReceive;
//
//    uint32_t ui32Status;
//    uint8_t i= 0;
//
//    ui32Status = ROM_UARTIntStatus(UART2_BASE, true);
//
//    ROM_UARTIntClear(UART2_BASE, ui32Status);
//
//
//    while(ROM_UARTCharsAvail(UART2_BASE))
//       {
//
//        *(buffer+i) = ROM_UARTCharGet(UART2_BASE);
//         i++;
//
//    }
//    UARTprintf("Received bytes are %d\n",i);
//
//    IntMasterEnable();
////    UARTprintf("Received in B_ID : %d, Log level = %d , Moisture  = %d\n", \
////                                                      toReceive.boardID,toReceive.level,toReceive.moisture);
//
//   // UARTprintf("Received in B_ID : %d, Log level = %d , Motor %d , Buzzer = %d Str = %s\n", \
//                                                                                              toReceive.boardID,toReceive.loglevel,toReceive.motorstate,toReceive.buzzerstate,toReceive.LCDData);
////
//}

void UART7_handler()
{
    char uart_val;
    uart_val = UARTCharGet(UART7_BASE);
    UARTprintf("Received %d", uart_val);
}

