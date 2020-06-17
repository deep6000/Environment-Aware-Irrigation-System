/*
 * light_task.h
 *
 *  Created on: Apr 14, 2019
 *      Author: deepe
 */

#ifndef INC_LIGHT_TASK_H_
#define INC_LIGHT_TASK_H_


#include "tasks_driver.h"
//#include "queue_driver.h"
#include "apds9301.h"

extern float latest_lux;
/**
 *  @brief Callback func for Light Task create
 * @param pvParameters
 */
void LightTask(void *pvParameters);


/**
 * @brief Timer Handler Func for Light Task
 */
void LightTimerHandler();




#endif /* INC_LIGHT_TASK_H_ */
