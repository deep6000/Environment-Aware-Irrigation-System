/*
 * spi_driver.c
 *
 * Created on: Apr 18, 2019
 * Author    : Deepesh Madhumitha
 * Reference : Tiva examples/peripherals/ssi/spi_master.c
 */

#include"spi_driver.h"


const uint32_t SPI[4] = {SSI0_BASE, SSI1_BASE, SSI2_BASE, SSI3_BASE};

const uint32_t SPI_SYSCTL[4] = {SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_SSI1, SYSCTL_PERIPH_SSI2, SYSCTL_PERIPH_SSI3};

void InitalizeSPI(spi_t SPI_NUM, uint32_t clock)
{
    if(SPI_NUM==SPI1)
       {
         //
         // The SSI0 peripheral must be enabled for use.
         //
           SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);

          //
          // Configure the pin muxing for SSI0 functions on port A2, A3, A4, and A5.
          // This step is not necessary if your part does not support pin muxing.
          // TODO: change this to select the port/pin you are using.
          //
           SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
           SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
           SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
           SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

           while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
           while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));


          //
          // Configure the pin muxing for SSI0 functions on port A2, A3, A4, and A5.
          // This step is not necessary if your part does not support pin muxing.
          // TODO: change this to select the port/pin you are using.
          //

           GPIOPinConfigure(GPIO_PB5_SSI1CLK);
         //  GPIOPinConfigure(GPIO_PA3_SSI0FSS);
           GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);
           GPIOPinConfigure(GPIO_PE5_SSI1XDAT1);
           GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);

           GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_5|GPIO_PIN_4);
           GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_5);

           CS_0;
           SSIConfigSetExpClk(SSI1_BASE, clock, SSI_FRF_MOTO_MODE_0,
                              SSI_MODE_MASTER, SPI_CLOCK_1MHZ, 8);
           EnableSPI(SPI_NUM);


       }
}
 static inline void EnableSPI(spi_t spi)
{
     SSIEnable(SPI[spi]);
}

static inline void SPI_flush(spi_t spi)
{
    while(SSIBusy(SPI[spi]));
}

/**
* @brief - Read a byte SPI
* @param - spi_t
* @return uint8_t
**/
uint8_t SPIReadByte(spi_t spi)
{
    uint32_t data = 0;
    SSIDataGet(SPI[spi], &data);
    return ((uint8_t)(data & 0xFF));
}

/**
* @brief - Read a byte SPI bus without blocking
* @param - spi_t
* @return uint8_t
**/
uint8_t SPIReadByteNonBlocking(spi_t spi)
{

    uint32_t data;
    SSIDataGetNonBlocking(SPI[spi], &data);
    return ((uint8_t)(data & 0xFF));
}

/**
* @brief - Write a byte SPI bus
* @param - spi_t
* @param - byte uint8_t
**/
void SPIWriteByte(spi_t spi, uint8_t byte)
{

    SSIDataPut(SPI[spi],((uint32_t)byte & 0x000000FF));
    SPI_flush(spi);
}

/**
* @brief - Write a byte SPI bus without blocking
* @param - spi_t
* @param - byte uint8_t
**/
void SPIWriteByteNonBlocking(spi_t spi, uint8_t byte)
{

    SPI_flush(spi);
    SSIDataPutNonBlocking(SPI[spi],((uint32_t)byte & 0x000000FF));
    SPI_flush(spi);
}

void SPIWritePayload(spi_t spi, uint8_t*p, uint8_t length)
{
    uint8_t i = 0;
    while (i < length)
    {
        SPIWriteByte(spi, *(p+i));
        ++i;
    }
}


void SPIReadPayload(spi_t spi, uint8_t* p, uint8_t length)
{
    uint8_t i=0;
    while (i<length)
    {
       SPIWriteByte(spi,0xFF);
        *(p+i) = SPIReadByte(spi);
        ++i;
    }
}
