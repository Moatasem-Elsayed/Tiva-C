/*
 * Output.c
 *
 *  Created on: May 25, 2021
 *      Author: PC1
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <Output.h>
void Fan_Init()
{
   // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    SysCtlPeripheralEnable(FAN_PORT_ENABLE);
    SysCtlDelay(50000);
    GPIOPinTypeGPIOOutput(FAN_PORT, FAN_PIN);
//    SysCtlDelay(50000);
 }
void Fan_on()
{
    GPIOPinWrite(FAN_PORT, FAN_PIN,  FAN_PIN );

  }
void Fan_off()
{
    GPIOPinWrite(FAN_PORT, FAN_PIN,  0x00 );

 }


void Lamp_Init()
{
     SysCtlPeripheralEnable(LAMP_PORT_ENABLE);
     SysCtlDelay(50000);
     GPIOPinTypeGPIOOutput(LAMP_PORT, LAMP_PIN);

}
void Lamp_on()
{
    GPIOPinWrite(LAMP_PORT, LAMP_PIN,  LAMP_PIN );

}
void Lamp_off()
{
    GPIOPinWrite(LAMP_PORT, LAMP_PIN,  0x00 );

}


