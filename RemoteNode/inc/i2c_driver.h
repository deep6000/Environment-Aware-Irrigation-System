/*
 * i2c_driver.h
 *
 *  Created on: Apr 12, 2019
 *      Author: deepe
 */

#ifndef INC_I2C_DRIVER_H_
#define INC_I2C_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/inc/hw_i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/hibernate.h"
#include "common.h"


/**
 * @brief Initialize I2c peripherals
 * @param clock
 * @return void
 */
void InitalizeI2C(uint32_t clock);

/**
 * @brief Send 1 byte to i2c bus
 * @param target_address
 * @param register_address
 * @param data
 * @return SUCCESS or FAILURE
 */

sensor_status I2C0SendByte(uint8_t target_address, uint8_t register_address, uint8_t data);
/**
 * @brief Send 1 byte to i2c bus
 * @param target_address
 * @param register_address
 * @param data
 * @return SUCCESS or FAILURE
 */

sensor_status I2C2SendByte(uint8_t target_address, uint8_t register_address, uint8_t data);


/**
 * @brief get 2 bytes of data
 * @param target_address
 * @param register_address
 * @param data
 * @return SUCCESS OR FAILURE
 */
sensor_status I2C0Get2Bytes(uint8_t target_address, uint8_t register_address,uint8_t *data);
/**
 * @brief get 2 bytes of data
 * @param target_address
 * @param register_address
 * @param data
 * @return SUCCESS OR FAILURE
 */
sensor_status I2C2Get2Bytes(uint8_t target_address, uint8_t register_address,uint8_t *data);

;
/**
 * @brief Get 1 byte
 * @param target_address
 * @param register_address
 * @return SUCCESS or FAILURE
 */
sensor_status I2CGetByte(uint8_t target_address, uint8_t register_address,uint8_t *data);


#endif /* INC_I2C_DRIVER_H_ */
