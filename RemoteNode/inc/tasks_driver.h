/*
 * tasks_driver.h
 *
 *  Created on: Apr 12, 2019
 *      Author: deepe
 */

#ifndef INC_TASKS_DRIVER_H_
#define INC_TASKS_DRIVER_H_

#include <math.h>
#include "i2c_driver.h"
#include "clock_driver.h"
#include "common.h"
#include "temperature_task.h"
#include "light_task.h"
#include "logger_task.h"
#include "communication_task.h"
#include "moisture_task.h"
#include "humidity_task.h"
#include "uart_driver.h"
#include "actuators.h"
#include "adc_driver.h"
#include "lcd_driver.h"
#include "spi_driver.h"
#include "heartbeat_task.h"



#include "drivers/pinout.h"
#include "driverlib/gpio.h"
#include "driverlib/inc/hw_memmap.h"
#include "utils/uartstdio.h"

//Sensor Header Files
#include "tmp102.h"
#include "apds9301.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include"timers.h"
#include "synchronization.h"

// number of active tasks
#define NUM_OF_TASKS                       (7)

// macros defining Task priority
#define xLOGGER_TASK_PRIORITY              ( tskIDLE_PRIORITY + 2 )
#define xTEMPERATURE_TASK_PRIORITY         ( tskIDLE_PRIORITY + 1 )
#define xLIGHT_TASK_PRIORITY               ( tskIDLE_PRIORITY + 1 )
#define xMOISTURE_TASK_PRIORITY            ( tskIDLE_PRIORITY + 1 )
#define xALERT_TASK_PRIORITY               ( tskIDLE_PRIORITY + 1 )
#define xCOMMUNICATION_TASK_PRIORITY       ( tskIDLE_PRIORITY + 1 )
#define xHEARTBEAT_TASK_PRIORITY            ( tskIDLE_PRIORITY + 1 )



TaskHandle_t xHandleTask[NUM_OF_TASKS];


void InitializeTasks();












#endif /* INC_TASKS_DRIVER_H_ */
