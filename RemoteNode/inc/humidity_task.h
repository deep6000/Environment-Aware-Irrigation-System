/*
 * humidity_task.h
 *
 *  Created on: Apr 18, 2019
 *      Author: deepe
 */

#ifndef INC_HUMIDITY_TASK_H_
#define INC_HUMIDITY_TASK_H_


#include"tasks_driver.h"

/**
 * @brief Humidity callback
 * @param pvParameters
 */
void HumidityTask(void *pvParameters);
/**
 * @brief Humidity timer handler
 */
void HumidityTimerHandler();








#endif /* INC_HUMIDITY_TASK_H_ */
