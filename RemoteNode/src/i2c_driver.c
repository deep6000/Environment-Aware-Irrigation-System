/*
 * i2c_driver.c
 *
 *  Created on: Apr 12, 2019
 *      Author: deepe
 */

#include "i2c_driver.h"




void InitalizeI2C(uint32_t clock)
{

    // Enable I2C2 Peripheral
        SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);

        // Enable GPION and configure Pin4 and Pin5
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

        GPIOPinConfigure(GPIO_PN4_I2C2SDA);
        GPIOPinConfigure(GPIO_PN5_I2C2SCL);

        GPIOPinTypeI2CSCL(GPIO_PORTN_BASE, GPIO_PIN_5);
        GPIOPinTypeI2C(GPIO_PORTN_BASE, GPIO_PIN_4);
        I2CMasterInitExpClk(I2C2_BASE, clock, false);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

               // Enable GPION and configure Pin4 and Pin5
               SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

               GPIOPinConfigure(GPIO_PB3_I2C0SDA);
               GPIOPinConfigure(GPIO_PB2_I2C0SCL);

               GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
               GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
               I2CMasterInitExpClk(I2C0_BASE, clock, false);
}

sensor_status I2C0SendByte(uint8_t target_address, uint8_t register_address, uint8_t data)
{
    static int count;
   //
   // Tell the master module what address it will place on the bus when
   // communicating with the slave.  Set the address to LUX_SENSOR
   // (as set in the slave module).  The receive parameter is set to false
   // which indicates the I2C Master is initiating a writes to the slave.  If
   // true, that would indicate that the I2C Master is initiating reads from
   // the slave.
   //
   I2CMasterSlaveAddrSet(I2C0_BASE, target_address, false);

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C0_BASE, register_address);

   //
   // Initiate send of data from the master.
   //
   I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C0_BASE));
#endif

   /*
   ** now wait for it to be non-busy
   */
   while(I2CMasterBusy(I2C0_BASE))
   {
       count++;
       if(count > 60000)
       {
           count = 0;
           return WRITE_FAILURE;
       }
   }

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C0_BASE, data);

   //
   // Initiate send of data from the master.
   //
   I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C0_BASE));
#endif
   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C0_BASE))
   {
       count++;
       if(count > 60000)
       {
           count = 0;
           return WRITE_FAILURE;
       }
   }
   return WRITE_SUCCESS;

}

sensor_status I2C2SendByte(uint8_t target_address, uint8_t register_address, uint8_t data)
{
    static int count;
   //
   // Tell the master module what address it will place on the bus when
   // communicating with the slave.  Set the address to LUX_SENSOR
   // (as set in the slave module).  The receive parameter is set to false
   // which indicates the I2C Master is initiating a writes to the slave.  If
   // true, that would indicate that the I2C Master is initiating reads from
   // the slave.
   //
   I2CMasterSlaveAddrSet(I2C2_BASE, target_address, false);

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C2_BASE, register_address);

   //
   // Initiate send of data from the master.
   //
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif

   /*
   ** now wait for it to be non-busy
   */
   while(I2CMasterBusy(I2C2_BASE))
   {
       count++;
       if(count > 60000)
       {
           count = 0;
           return WRITE_FAILURE;
       }
   }

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C2_BASE, data);

   //
   // Initiate send of data from the master.
   //
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif
   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C2_BASE))
   {
       count++;
       if(count > 60000)
       {
           count = 0;
           return WRITE_FAILURE;
       }
   }
   return WRITE_SUCCESS;

}

sensor_status I2CGetByte(uint8_t target_address, uint8_t register_address,uint8_t *data)
{
    static int count;
   //
   // Tell the master module what address it will place on the bus when
   // communicating with the slave.  Set the address to LUX_SENSOR
   // (as set in the slave module).  The receive parameter is set to false
   // which indicates the I2C Master is initiating a writes to the slave.  If
   // true, that would indicate that the I2C Master is initiating reads from
   // the slave.
   //
   I2CMasterSlaveAddrSet(I2C2_BASE, target_address, false);

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C2_BASE, register_address);

   //
   // Initiate send of data from the master.  Since the loopback
   // mode is enabled, the master and slave units are connected
   // allowing us to receive the same data that we sent out.
   //
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C2_BASE))
{
           count++;
              if(count > 60000)
              {
                  count = 0;
                  return READ_FAILURE;
              }

       }

   /*
   ** now switch to read mode
   */
   I2CMasterSlaveAddrSet(I2C2_BASE, target_address, true);

   /*
   ** read one byte
   */
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C2_BASE))
       {
           count++;
              if(count > 60000)
              {
                  count = 0;
                  return READ_FAILURE;
              }

       }
           return READ_SUCCESS;
}


sensor_status I2C0Get2Bytes(uint8_t target_address, uint8_t register_address,uint8_t *data)
{
    static int count;
   //
   // Tell the master module what address it will place on the bus when
   // communicating with the slave.  Set the address to LUX_SENSOR
   // (as set in the slave module).  The receive parameter is set to false
   // which indicates the I2C Master is initiating a writes to the slave.  If
   // true, that would indicate that the I2C Master is initiating reads from
   // the slave.
   //
   I2CMasterSlaveAddrSet(I2C0_BASE, target_address, false);

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C0_BASE, register_address);

   //
   // Initiate send of data from the master.  Since the loopback
   // mode is enabled, the master and slave units are connected
   // allowing us to receive the same data that we sent out.
   //
   I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C0_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C0_BASE))
   {
       count++;
       if(count > 60000)
       {
           count = 0;
           return READ_FAILURE;
       }
}


   /*
   ** now switch to read mode
   */
   I2CMasterSlaveAddrSet(I2C0_BASE, target_address, true);

   /*
   ** read one byte
   */
   I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C0_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C0_BASE))
   {
       count++;
          if(count > 60000)
          {
              count = 0;
              return READ_FAILURE;
          }

   }

   *(data+1) = I2CMasterDataGet(I2C0_BASE);

   /*
   ** read one byte
   */
   I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
   SysCtlDelay(1000);
#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C0_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C0_BASE))
   {

       count++;
          if(count > 60000)
          {
              count = 0;
              return READ_FAILURE;
          }
   }

   *(data+0) = I2CMasterDataGet(I2C0_BASE);

   return READ_SUCCESS;

}




sensor_status I2C2Get2Bytes(uint8_t target_address, uint8_t register_address,uint8_t *data)
{
    static int count;
   //
   // Tell the master module what address it will place on the bus when
   // communicating with the slave.  Set the address to LUX_SENSOR
   // (as set in the slave module).  The receive parameter is set to false
   // which indicates the I2C Master is initiating a writes to the slave.  If
   // true, that would indicate that the I2C Master is initiating reads from
   // the slave.
   //
   I2CMasterSlaveAddrSet(I2C2_BASE, target_address, false);

   //
   // Place the data to be sent in the data register
   //
   I2CMasterDataPut(I2C2_BASE, register_address);

   //
   // Initiate send of data from the master.  Since the loopback
   // mode is enabled, the master and slave units are connected
   // allowing us to receive the same data that we sent out.
   //
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C2_BASE))
   {
       count++;
       if(count > 6000)
       {
           count = 0;
           return READ_FAILURE;
       }
}


   /*
   ** now switch to read mode
   */
   I2CMasterSlaveAddrSet(I2C2_BASE, target_address, true);

   /*
   ** read one byte
   */
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C2_BASE))
   {
       count++;
          if(count > 60000)
          {
              count = 0;
              return READ_FAILURE;
          }

   }

   *(data+1) = I2CMasterDataGet(I2C2_BASE);

   /*
   ** read one byte
   */
   I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
   SysCtlDelay(1000);
#ifdef BUSY_WAIT
   //
   // Wait until master module is says it's busy. Errata I2C#08
   //
   while(!I2CMasterBusy(I2C2_BASE));
#endif

   //
   // Wait until master module is done
   //
   while(I2CMasterBusy(I2C2_BASE))
   {

       count++;
          if(count > 60000)
          {
              count = 0;
              return READ_FAILURE;
          }
   }

   *(data+0) = I2CMasterDataGet(I2C2_BASE);

   return READ_SUCCESS;

}



