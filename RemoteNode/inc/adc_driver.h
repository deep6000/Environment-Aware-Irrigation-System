/*
 * ad_driver.h
 *
 *  Created on: Apr 24, 2019
 *      Author: deepe
 */

#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

#include "driverlib/adc.h"



/**
 * @brief Initialize ADC0
 */
  void InitializeADC0();
/**
 *
 * @return uint32_t ADC value
 */
  uint32_t getADC0Value();

/**
 * @brief Initialize ADC1
 * @return void
 */
  void InitializeADC1();

/**
 * @brief get Mositure value
 * @return ADC value
 */
  uint32_t getADC1Value();







#endif /* INC_ADC_DRIVER_H_ */
