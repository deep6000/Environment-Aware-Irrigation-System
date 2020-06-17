/*
 * synchronization.c
 *
 *  Created on: Apr 27, 2019
 *      Author: deepe
 */

#include "tasks_driver.h"
#include "synchronization.h"


void CreateSemaphores(void)
{
    //Creating Temperature Semaphore
    g_UART = xSemaphoreCreateBinary();
    if(g_UART == NULL)
    {
        UARTprintf("\n\nTemperature Semaphore not created.\n");
    }
}
