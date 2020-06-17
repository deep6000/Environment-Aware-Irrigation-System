/*
 * bist.h
 *
 *  Created on: Apr 29, 2019
 *      Author: deepe
 */

#ifndef INC_BIST_H_
#define INC_BIST_H_

#include"tasks_driver.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"

#define WAIT_TIME   (1000000)

/**
 *
 * @return SUCCESS FAILURE
 */
uint8_t bist();


#endif /* INC_BIST_H_ */
