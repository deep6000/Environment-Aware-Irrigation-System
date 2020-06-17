/*
 * moisture_task.h
 *
 *  Created on: Apr 27, 2019
 *      Author: deepe
 */

#ifndef INC_MOISTURE_TASK_H_
#define INC_MOISTURE_TASK_H_

extern uint32_t latest_moisture;
/**
 * @brief Moisture Task handling moisture data
 * @param pvParameters
 */
void MoistureTask(void *pvParameters);


/**
 * @brief Moisture Timer Handler
 * @return void
 */
void MoistureTimerHandler();

/**
 *  @brief Process ADC values of Mositure
 * @param value
 * @return value processed
 */
uint32_t ProcessMoisture(uint32_t value);

#endif /* INC_MOISTURE_TASK_H_ */
