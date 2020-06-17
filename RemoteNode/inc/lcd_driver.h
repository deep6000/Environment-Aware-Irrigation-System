/*
 * lcd_driver.h
 *
 *  Created on: Apr 25, 2019
 *      Author: deepe
 *
 * https://mil.ufl.edu/3744/docs/lcdmanual/commands.html
 */

#ifndef INC_LCD_DRIVER_H_
#define INC_LCD_DRIVER_H_

#include "stdint.h"
#include "tasks_driver.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"

  /*LCD Commands*/

#define CLEAR_DISPLAY   (0x01)
#define CURSOR_HOME     (0x02)
#define ENTRY_MODE      (0x06)
#define DISPLAY_ON      (0x0C)
#define CURSOR_ON       (0x0A)
#define CURSOR_BLINK    (0x0F)
#define DISPLAY_OFF     (0x08)
#define DISPLAY_SHIFT   (0x10)
#define SYSTEM_SET      (0x38)
#define FIRST_LINE      (0x80)
#define SECOND_LINE     (0xC0)
#define THIRD_LINE      (0x90)
#define FOURTH_LINE     (0xD0)
#define BIT_MODE_8      (0x30)
#define BIT_MODE_4      (0x30)

// Microsecond Count for delay
#define MICROSECOND      (160000)


#define RS_1            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
#define RS_0            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);

//#define RW_1            GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_1, GPIO_PIN_1);
//#define RW_0            GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_1, 0);

#define Enable_1        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
#define Enable_0        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);

#define Write(data)     GPIOPinWrite(GPIO_PORTK_BASE, /*GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 */ GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0 ,data);


/**
 * @brief Initialize LCD gpio pins
 * @return void
 */
void InitializeLCD();
/**
 * @brief
 * @param character
 * @return void
 */
void LCDWriteChar(char character);
/**
 * @brief Write command to LCD
 * @param command
 */

void LCDWriteCommand(uint8_t command);

/**
 * @brief Write string to LCD
 * @param data
 * @param line
 */
void LCDWriteStr(char* data,int line);
/**
 * @brief Turn on Display
 * @return void
 */
void TurnOnLCD();
/**
 * @brief Clear LCd dislay
 * @return void
 */
void LCDClearDisplay();



#endif /* INC_LCD_DRIVER_H_ */
