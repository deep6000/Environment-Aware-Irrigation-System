/*
 * actuators.h
 *
 *  Created on: Apr 29, 2019
 *      Author: deepesh
 */

#ifndef INC_ACTUATORS_H_
#define INC_ACTUATORS_H_


#include "tasks_driver.h"

/**
 * @brief Intialize Acuators GPIOs
 */
void InitializeActuators();


/**
 * @brief Alert Task responsible for handling actuators
 * @param pvParameters
 */
void AlertTask(void *pvParameters);
/**
 * @brief Process turning on/off motor
 * @param motorstate
 * @return On or off
 */
uint8_t ProcessMotor(uint8_t motorstate);

/**
 * @brief Process turning on/off Buzzer
 * @param buzzerstate
 * @return On or off
 */
uint8_t ProcessBuzzer(uint8_t buzzerstate);

/**
 * @brief Process turning on/off Motor
 * @param motorstate
 * @return On or off
 */
void MotorState(uint8_t val);
/**
 * @brief Buzzerstate On/Off based on value
 * @param val
 */
void BuzzerState(uint8_t val);
/**
 * @brief State Red led
 * @param state
 */
void RedLed(uint8_t state);
/**
 * @brief State Yellow led
 * @param state
 */
void YellowLed(uint8_t state);

/**
 * @brief State Green led
 * @param state
 */
void GreenLed(uint8_t state);

/**
 * @brief Check which mode it should work in
 * @return void
 */
void ProcessModes();
#endif /* INC_ACTUATORS_H_ */
