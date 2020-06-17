/*
 * clock_driver.c
 *
 *  Created on: Apr 12, 2019
 *      Author: deepesh
 */


#include"clock_driver.h"

uint32_t SystemClockInit()
{
    uint32_t output_clock_rate_hz;
    output_clock_rate_hz = ROM_SysCtlClockFreqSet(
                               (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                               SYSTEM_CLOCK);
    ASSERT(output_clock_rate_hz == SYSTEM_CLOCK);
    return output_clock_rate_hz;
}


void InitalizeRTC(uint32_t clock)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(clock);
    HibernateClockConfig(HIBERNATE_OSC_LOWDRIVE);
    HibernateRTCEnable();
}

uint32_t GetTimeMs()
{
    float time1, time2;
    uint32_t secs, subsecs,time;
    secs = HibernateRTCGet();
    subsecs =  HibernateRTCSSGet();
    time1 = (float)((secs*1000));
    time2 = (float)((subsecs*1000)/32768);
    time =(uint32_t) (time1 + time2);
    return time;
}
