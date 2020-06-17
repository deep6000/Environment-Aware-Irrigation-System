/*
 * spi_driver.h
 *
 *  Created on: Apr 18, 2019
 *      Author: Deepesh Madhumitha
 */

#ifndef INC_SPI_DRIVER_H_
#define INC_SPI_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "driverlib/debug.h"



#define SPI_CLOCK_1MHZ      (1000000)
#define SPI_CLOCK_2MHZ      (2000000)
#define CS_1                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
#define CS_0                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);

typedef enum{
    SPI0,
    SPI1,
    SPI2,
    SPI3
}spi_t;

extern const uint32_t SPI[4];

extern const uint32_t SPI_SYSCTL[4];

/**
 * @brief Initalize SPI driver
 * @param SPI_NUM
 * @param clock
 */
void InitalizeSPI(spi_t SPI_NUM, uint32_t clock);

/**
 * @brief Enable spi
 * @param spi
 */
static inline void EnableSPI(spi_t spi);

/**
 * @brief Flush Spi
 * @param spi
 */
static inline void SPI_flush(spi_t spi);

/**
* @brief - Read a byte SPI
* @param - spi_t
* @return uint8_t
**/
uint8_t SPIReadByte(spi_t spi);


/**
* @brief - Read a byte SPI bus without blocking
* @param - spi_t
* @return uint8_t
**/
uint8_t SPIReadByteNonBlocking(spi_t spi);


/**
* @brief - Write a byte SPI bus
* @param - spi_t
* @param - byte uint8_t
**/
void SPIWriteByte(spi_t spi, uint8_t byte);

/**
* @brief - Write a byte SPI bus without blocking
* @param - spi_t
* @param - byte uint8_t
**/
void SPIWriteByteNonBlocking(spi_t spi, uint8_t byte);

/**
 * @brief Write payload of length specified
 * @param spi
 * @param p
 * @param length
 */

void SPIWritePayload(spi_t spi, uint8_t*p, uint8_t length);

/**
 * @brief read payload of length specified
 * @param spi
 * @param p
 * @param length
 */
void SPIReadPayload(spi_t spi, uint8_t* p, uint8_t length);


#endif /* INC_SPI_DRIVER_H_ */
