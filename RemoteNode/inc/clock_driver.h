/*
 * clock_driver.h
 *
 *  Created on: Apr 12, 2019
 *      Author: Deepesh, Madhumitha
 */

#ifndef INC_CLOCK_DRIVER_H_
#define INC_CLOCK_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "drivers/pinout.h"
#include "driverlib/hibernate.h"
#include "driverlib/debug.h"


// System clock rate, 120 MHz
#define SYSTEM_CLOCK    120000000U

uint32_t SystemClockInit();


void InitalizeRTC(uint32_t clock);

uint32_t GetTimeMs();





#endif /* INC_CLOCK_DRIVER_H_ */
