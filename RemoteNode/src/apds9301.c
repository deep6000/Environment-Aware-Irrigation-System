/*
 * apds9301.c
 *
 *  Created on: Apr 14, 2019
 *      Author: deepesh
 *
 */

#include "apds9301.h"


return_status apds9301_poweron()
{
    uint8_t ret;
    ret =I2C0SendByte(APDS9301_SLAVE_ADDR, APDS9301_REG_CMD, 0x03);
    if(ret == WRITE_FAILURE)
        return FAIl;
    else
        return SUCCESS;
}



return_status calculateLuminosity(float *light)
{
    uint32_t Ch1,Ch2;
    int8_t ret;
     ret = I2C0Get2Bytes(APDS9301_SLAVE_ADDR,APDS9301_REG_DATA0_LOW,(uint8_t*)&Ch1);
     if(ret == READ_FAILURE)
     {
         return FAIL;
     }
     ret =  I2C0Get2Bytes(APDS9301_SLAVE_ADDR,APDS9301_REG_DATA1_LOW,(uint8_t*)&Ch2);
     if(ret == READ_FAILURE)

               return FAIL;
     }
     float lux = 0;

        float ratio_ch2_ch1;
    if(Ch1 != 0)
        ratio_ch2_ch1= (float)Ch2/(float)Ch1;
    else
        ratio_ch2_ch1 = 0;

    if (ratio_ch2_ch1 > 0 && ratio_ch2_ch1 <= 0.50)
        lux = 0.0304*Ch1 - 0.062*Ch1*(pow(ratio_ch2_ch1,1.4));
    else if (ratio_ch2_ch1 > 0.50 && ratio_ch2_ch1 <= 0.61)
        lux = 0.0224*Ch1 - 0.031*Ch2;
    else if (ratio_ch2_ch1 > 0.61 && ratio_ch2_ch1 <= 0.80)
        lux = 0.0128*Ch1 - 0.0153*Ch2;
    else if (ratio_ch2_ch1 > 0.80 && ratio_ch2_ch1 <= 1.30)
        lux = 0.00146*Ch1 - 0.00112*Ch2;
    else if (ratio_ch2_ch1 > 1.30)
        lux = 0;
   *light = lux;
   return SUCCESS;
}
