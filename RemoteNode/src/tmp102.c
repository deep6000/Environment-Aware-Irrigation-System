

#include "tmp102.h"

/** */
return_status getTemperature(float *temperature)
{
    int8_t ret;
    uint16_t regval;


    ret = I2C2Get2Bytes(TMP_SLAVE_ADDRESS, TMP_REG_TEMPERATURE ,(uint8_t*)&regval);
    if(ret == READ_FAILURE)
    {
        return FAIL;
    }

        *temperature = regval_to_Temperature(regval);
        return SUCCESS;
}


float regval_to_Temperature(uint16_t regval)
{
    float temperature;
    regval = regval >> 4;
    if(regval > 0x7FF)
    {
        temperature = -1 * (0.0625 * regval);
    }
    else
        temperature = 0.0625 * regval;

    return temperature;
}
