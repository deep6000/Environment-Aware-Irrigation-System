/*
 * logger_task.h
 *
 *  Created on: Apr 14, 2019
 *      Author: deepe
 */

#ifndef INC_LOGGER_TASK_H_
#define INC_LOGGER_TASK_H_


//#include "common.h"
#include "tasks_driver.h"
#include "utils/uartstdio.h"
//#include "queue_driver.h"



/**
 * Logger Task Callback func
 * @param pvParameters
 */
void LoggerTask(void *pvParameters);


#endif /* INC_LOGGER_TASK_H_ */
