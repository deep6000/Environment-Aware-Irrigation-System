/*
 * adc_driver.c
 *
 *  Created on: Apr 24, 2019
 *      Author: deepe
 */


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "adc_driver.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom_map.h"
#include "tasks_driver.h"



void InitializeADC1()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);


     while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1));

     GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_2);
     ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

     ADCSequenceStepConfigure(ADC1_BASE,3,0,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
     MAP_ADCReferenceSet(ADC1_BASE, ADC_REF_EXT_3V);

     ADCSequenceEnable(ADC1_BASE, 3);

}


void InitializeADC0()
{
      SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);


        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));

        GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);
        ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

        ADCSequenceStepConfigure(ADC0_BASE,3,0,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
        MAP_ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V);

        ADCSequenceEnable(ADC0_BASE, 3);
        ADCIntClear(ADC0_BASE, 3);
}

uint32_t getADC0Value()
{
      uint32_t ADC0Value;

           ADCProcessorTrigger(ADC0_BASE, 3);
                  while(!ADCIntStatus(ADC0_BASE, 3, false))
                  {
                  }
                  ADCIntClear(ADC0_BASE, 3);
                  ADCSequenceDataGet(ADC0_BASE, 3, &ADC0Value);

                  return ADC0Value;
}

uint32_t getADC1Value()
{
      uint32_t ADC1Value[1];

      ADCProcessorTrigger(ADC1_BASE, 3);
      while(!ADCIntStatus(ADC1_BASE, 3, false))
      {
      }
      ADCIntClear(ADC1_BASE, 3);
      ADCSequenceDataGet(ADC1_BASE, 3, ADC1Value);

      return ADC1Value[0];
}



