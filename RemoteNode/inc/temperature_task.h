/*
 * temperature_task.h
 *
 *  Created on: Apr 14, 2019
 *      Author: deepe
 */

#ifndef INC_TEMPERATURE_TASK_H_
#define INC_TEMPERATURE_TASK_H_


//#include "common.h"
#include "tasks_driver.h"
#include "tmp102.h"

extern float latest_temperature;



/**
 * @brief Temperature Task
 * @param pvParameters
 */

void TemperatureTask(void *pvParameters);


/**
 * @brief Timer handler func for Temperature Task
 */
void TemperatureTimerHandler();


#endif /* INC_TEMPERATURE_TASK_H_ */
