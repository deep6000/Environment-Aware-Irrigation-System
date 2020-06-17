/*
 * apds9301.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Deepesh, Madhumitha
 *      @brief Functions to initialize apds9301 light sensor
 */

#ifndef INC_APDS9301_H_
#define INC_APDS9301_H_

#include "i2c_driver.h"
#include <math.h>

// APDS9301 related Macros
#define APDS9301_SLAVE_ADDR         (0x39)
/*Register Addresss*/
#define APDS9301_REG_CMD            (0x80) // MSB = 1
#define APDS9301_REG_CTRL           (0x00) | APDS9301_REG_CMD
#define APDS9301_REG_TIMING         (0x01) | APDS9301_REG_CMD
#define APDS9301_REG_TH_LOW_LOW     (0x02) | APDS9301_REG_CMD
#define APDS9301_REG_TH_LOW_HIGH    (0X03) | APDS9301_REG_CMD
#define APDS9301_REG_TH_HIGH_LOW    (0x04) | APDS9301_REG_CMD
#define APDS9301_REG_TH_HIGH_HIGH   (0x05) | APDS9301_REG_CMD
#define APDS9301_REG_INT_TH         (0x06) | APDS9301_REG_CMD
#define APDS9301_REG_ID             (0x0A) | APDS9301_REG_CMD
#define APDS9301_REG_DATA0_LOW      (0x0C) | APDS9301_REG_CMD
#define APDS9301_REG_DATA0_HIGH     (0x0D) | APDS9301_REG_CMD
#define APDS9301_REG_DATA1_LOW      (0x0E) | APDS9301_REG_CMD
#define APDS9301_REG_DATA1_HIGH     (0x0F) | APDS9301_REG_CMD

/**
 *  @brief Poweron the apds9301 sensor
 */
return_status apds9301_poweron();

/**
 * @brief calculates lux based on ch1 and ch2 data
 * @param double light
 * @return Success or Failure
 */
return_status calculateLuminosity(float *light);


#endif /* INC_APDS9301_H_ */
