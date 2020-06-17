/*
 * tmp102.h
 *
 *  Created on: Apr 14, 2019
 *      Author: deepe
 */

#ifndef INC_TMP102_H_
#define INC_TMP102_H_

#include "i2c_driver.h"



#define TMP_SLAVE_ADDRESS           (0X48)
/**
 * TMP102 Reg address
 */
#define TMP_REG_TEMPERATURE         (0x00)
#define TMP_REG_CONFIGURATION       (0x01)
#define TMP_REG_TLOW                (0x02)
#define TMP_REG_THIGH               (0x03)
#define TMP_REG_TEMPERATURE         (0x00)
#define TMP_REG_CONFIGURATION       (0x01)
#define TMP_REG_TLOW                (0x02)
#define TMP_REG_THIGH               (0x03)

#define TEMPERATURE_THRESHOLD         (22)

/**
 *
 * @return SUCCESS or FAILURE
 */
return_status getTemperature(float *temperature);

/**
 *@brief convert register val to digital
 * @param regval
 * @return
 */
float regval_to_Temperature(uint16_t regval);

#endif /* INC_TMP102_H_ */
