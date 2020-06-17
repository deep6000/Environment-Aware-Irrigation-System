/* FreeRTOS 8.2 Tiva Demo
 *
 * main.c
 * author : Deepesh Madhumitha
 *
 *
 * This is a simple demonstration project of FreeRTOS 8.2 on the Tiva Launchpad
 * EK-TM4C1294XL.  TivaWare driverlib sourcecode is included.
 */


#include <eeprom_driver.h>
#include "main.h"

#include "driverlib/ssi.h"
#include "clock_driver.h"
#include "tasks_driver.h"
#include "driverlib/interrupt.h"
#include"bist.h"
#include"bme280.h"


/* Priorities at which the tasks are created. */




// Main function
int main(void)
{
    uint32_t OutputClockHz;
    char *data1 = "Welcome";
    char *data2 =  "Automatic";
    char *data3 = "Irrigation";
    char *data4 = "System";

    // Initialize system clock to 120 MHz
    OutputClockHz =  SystemClockInit();
    ROM_IntMasterEnable();
    // Initialize the GPIO pins for the Launchpad
    PinoutSet(false, false);
    //standard out
    IntializeSTDOUT();
    
    IntMasterEnable();
    //communication interface
    
    InitalizeRTC(OutputClockHz);
    
    InitalizeI2C(OutputClockHz);
    
    IntializeUART(UART2,OutputClockHz);
    UARTprintf("[%dms] [MAIN]\t\t[STATUS]\tSystem Powered Up\n", GetTimeMs());
    InitializeADC1();
    InitializeActuators();
    
    InitializeLCD();
    TurnOnLCD();
    LCDClearDisplay();
    LCDWriteStr(data1,1);
    LCDWriteStr(data2,2);
    LCDWriteStr(data3,3);
    LCDWriteStr(data4,4);
    CreateSemaphores();
     //InitalizeSPI(SPI1, OutputClockHz);



    UARTprintf("[%dms] [MAIN]\t\t[STATUS]\tPerforming Built in Self Test\n", GetTimeMs());
    
    if(bist())
    {
        UARTprintf("[%dms] [MAIN]\t\t[STATUS]\tBuilt in Self Test Failed \n", GetTimeMs());
        UARTprintf("[%dms] [MAIN]\t\t[STATUS]\tWorking in Degraded Mode \n", GetTimeMs());

    }
    else
    {
        UARTprintf("[%dms] [MAIN]\t\t[STATUS]\tBuilt in Self Test Successful\n", GetTimeMs());
        GreenLed(1);
    }

    ProcessModes();
    
    InitializeEEPROM();
    
    InitializeTasks();

    return 0;
}






void __error__(char *pcFilename, uint32_t ui32Line)
{
    // Place a breakpoint here to capture errors until logging routine is finished
    while (1)
    {
    }
}
