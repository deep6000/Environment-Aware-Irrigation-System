/*
 * synchronization.h
 *
 *  Created on: Apr 27, 2019
 *      Author: deepe
 */

#ifndef INC_SYNCHRONIZATION_H_
#define INC_SYNCHRONIZATION_H_

#include "semphr.h"

xSemaphoreHandle g_UART;
/**
 * @brief create Semaphores
 * @return void
 */
void CreateSemaphores(void);


#endif /* INC_SYNCHRONIZATION_H_ */
