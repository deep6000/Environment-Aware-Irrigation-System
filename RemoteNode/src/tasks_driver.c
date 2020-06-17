/*
 * tasks_driver.c
 *
 *  Created on: Apr 12, 2019
 *  Author: Deepesh, Madhumitha
 */

#include "tasks_driver.h"
#include "queue_driver.h"




void InitializeTasks()
{
    xTaskCreate(HeartbeatTask, (const portCHAR *)"ALERT",
                configMINIMAL_STACK_SIZE, NULL,xALERT_TASK_PRIORITY ,&xHandleTask[xHEARTBEAT]);

    xTaskCreate(LoggerTask, (const portCHAR *)"LOGGER",
                configMINIMAL_STACK_SIZE, NULL,  xLOGGER_TASK_PRIORITY , &xHandleTask[xLOGGER]);

   xTaskCreate(TemperatureTask, (const portCHAR *)"TEMP",
                  configMINIMAL_STACK_SIZE, NULL, xTEMPERATURE_TASK_PRIORITY, &xHandleTask[xTEMPERATURE]);

    xTaskCreate(LightTask, (const portCHAR *)"LIGHT",
                            configMINIMAL_STACK_SIZE, NULL,xLIGHT_TASK_PRIORITY ,&xHandleTask[xLIGHT]);

    xTaskCreate(MoistureTask, (const portCHAR *)"MOISTURE",
                configMINIMAL_STACK_SIZE, NULL,xMOISTURE_TASK_PRIORITY ,&xHandleTask[xMOISTURE]);

    xTaskCreate(CommunicationTask, (const portCHAR *)"COMM",
                configMINIMAL_STACK_SIZE, NULL,xCOMMUNICATION_TASK_PRIORITY ,&xHandleTask[xCOMMUNICATION]);

    xTaskCreate(AlertTask, (const portCHAR *)"ALERT",
                configMINIMAL_STACK_SIZE, NULL,xALERT_TASK_PRIORITY ,&xHandleTask[xALERT]);

    CreateQueue();
    vTaskStartScheduler();
}




