/*
 * eeprom.h
 *
 *  Created on: May 1, 2019
 *      Author: deepe
 */

#ifndef INC_EEPROM_DRIVER_H_
#define INC_EEPROM_DRIVER_H_

#include"tasks_driver.h"

#define EEPROM_START_ADDRESS 0x00

extern uint32_t address;
extern uint8_t EEPROM_FULL;
/**
 * @brief Initialize EEPROM
 * @return SUCCESS or FAILURE
 */
return_status InitializeEEPROM();

/**
 *
 * @param toStore
 * @param address
 * @return
 */
return_status WriteintoEEPROM(UART_TXPacket_t *toStore, uint16_t address);

/**
 *
 * @param address
 * @return
 */
return_status ReadFromEEPROM(uint32_t address);


#endif /* INC_EEPROM_DRIVER_H_ */
