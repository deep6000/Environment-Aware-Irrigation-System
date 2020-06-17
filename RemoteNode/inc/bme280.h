/*
 * bme280.h
 *
 *  Created on: May 1, 2019
 *      Author: deepe
 */

#ifndef INC_BME280_H_
#define INC_BME280_H_

#include"spi_driver.h"
#include"lcd_driver.h"

#define SPI_READ        (0x80)
#define WHO_AM_I_REG   0xD0
#define RESET_REG      0xE0
#define SOFT_RESET     0xB6
#define CTRL_HUM_REG   0xF2
#define STATUS_REG     0xF3
#define CTRL_MEAS_REG  0xF4
#define CONFIG_REG     0xF5
#define DATA_REG       0xF7
#define DIG_T1_REG     0x88
#define DIG_T2_REG     0x8A
#define DIG_T3_REG     0x8C
#define DIG_P1_REG     0x8E
#define DIG_P2_REG     0x90
#define DIG_P3_REG     0x92
#define DIG_P4_REG     0x94
#define DIG_P5_REG     0x96
#define DIG_P6_REG     0x98
#define DIG_P7_REG     0x9A
#define DIG_P8_REG     0x9C
#define DIG_P9_REG     0x9E
#define DIG_H1_REG     0xA1
#define DIG_H2_REG     0xE1
#define DIG_H3_REG     0xE3
#define DIG_H4_REG     0xE4
#define DIG_H5_REG     0xE5
#define DIG_H6_REG     0xE7
 typedef enum Mode
    {
      MODE_SLEEP = 0x00,
      MODE_FORCED = 0x01,
      MODE_NORMAL = 0x03
    }Mode;

 typedef enum Sampling
   {
     SAMPLING_X1   = 0x01,
     SAMPLING_X2   = 0x02,
     SAMPLING_X4   = 0x03,
     SAMPLING_X8   = 0x04,
     SAMPLING_X16  = 0x05
   }Sampling;
   enum Iirc
   {
     IIRC_OFF = 0x00,
     IIRC_2 = 0x01,
     IIRC_4 = 0x02,
     IIRC_8 = 0x03,
     IIRC_16 = 0x04
   };
   enum Standby
   {
     STANDBY_0_5_MS = 0x00,
     STANDBY_62_5_MS = 0x01,
     STANDBY_125_MS = 0x02,
     STANDBY_250_MS = 0x03,
     STANDBY_500_MS = 0x04,
     STANDBY_1000_MS = 0x05,
     STANDBY_10_MS = 0x06,
     STANDBY_20_MS = 0x07
   };

extern Sampling Hsampling;
extern Mode ModeofOperation;

uint8_t _dig_H1, _dig_H3;
int16_t _dig_H2, _dig_H4, _dig_H5;
int8_t _dig_H6;
int32_t _hv_x1_u32r;

int32_t _pressureCounts,_temperatureCounts,_humidityCounts;

int32_t _t_fine;

/**
 * @brief Initialize BME
 * @return void
 */
return_status InitializeBME280();
/**
 * @brief Configure BME
 * @return ERROR or SUCCESS
 */
return_status ConfigureBME280();

/**
 * @brief Read Trimming Parameters
 * @return  ERROR or SUCCESS
 */
return_status ReadTrimmingParameters();

/**
 * @brief Compensate Humidity parameters
 * @param humidityCounts
 * @param t_fine
 * @param humidity
 */
void CompensateHumidity(int32_t humidityCounts, int32_t t_fine, float* humidity);
/**
 * @brief Get humidity
 * @param value
 * @return ERROR or SUCCESS
 */
return_status GetHumidity(float* value);
/**
 * @brief get data counts
 * @param pressureCounts
 * @param temperatureCounts
 * @param humidityCounts
 * @return ERROR or SUCCESS
 */
return_status getDataCounts(int32_t* pressureCounts, int32_t* temperatureCounts, int32_t* humidityCounts);
/**
 * @brief Read From Registers
 * @param address
 * @param bytes
 * @param buffer
 * @return ERROR or SUCCESS
 */

return_status ReadRegisters(uint8_t address,uint8_t bytes, uint8_t * buffer);

/**
 * @brief Write into Registers
 * @param  address
 * @param  data
 * @return ERROR /SUCCESS
 */
return_status WriteRegister(uint8_t address, uint8_t data);



#endif /* INC_BME280_H_ */
