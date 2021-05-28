/*
 * Output.c
 *
 *  Created on: May 25, 2021
 *      Author: PC1
 */

#ifndef OUTPUT_C_
#define OUTPUT_C_


#define FAN_PORT                         GPIO_PORTD_BASE
#define FAN_PORT_ENABLE                  SYSCTL_PERIPH_GPIOD

#define LAMP_PORT                         GPIO_PORTE_BASE
#define LAMP_PORT_ENABLE                  SYSCTL_PERIPH_GPIOE

#define FAN_PIN                          GPIO_PIN_6
#define LAMP_PIN                         GPIO_PIN_0



void Fan_Init();
void Fan_on();
void Fan_off();


void Lamp_Init();
void Lamp_on();
void Lamp_off();

#endif /* OUTPUT_C_ */
