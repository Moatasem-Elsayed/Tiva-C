#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>


#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include <driverlib/sysctl.h>
#include <Output.h>
#include "driverlib/gpio.h"
#include "LCD.h"
#include "inc/tm4c123gh6pm.h"
//vdd=+
//vss=-
#define SENSOR_PORT                         GPIO_PORTF_BASE
#define SENSOR_PORT_ENABLE                  SYSCTL_PERIPH_GPIOF

#define SENSOR_PIN                          GPIO_PIN_0



int temperature=0;
int senseorvalue=0;
char Display[50]={0};
void Temperture_Init();
int TempertureRead();
char *convert_data(int val);
void Sensor_init();

int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    Lcd_init();
    Temperture_Init();
    Lamp_Init();
    Fan_Init();
    Sensor_init();
    Lcd_Goto(2,1);
    Lcd_Puts("Mohamed Gamal");
    while(1){
        int value=TempertureRead();
        char *ptr=convert_data(value);
        senseorvalue = GPIO_PORTF_DATA_R &0x01; //read data from PORTF

       // senseorvalue = ~senseorvalue; //switch is low active; LED is high active
        if(GPIOPinRead(SENSOR_PORT,SENSOR_PIN) == 0)
        {
            Lamp_on();
        }else
        {
            Lamp_off();
        }
        if(value>29)
        {
            Lcd_Goto(1,1);
            Lcd_Puts("Temp= ");
            Lcd_Puts(ptr);
            Lcd_Puts("C");
            Fan_on();
            SysCtlDelay(10000000);
        }else if(value<26)
        {
            Lcd_Goto(1,1);
            Lcd_Puts("Temp= ");
            Lcd_Puts(ptr);
            Lcd_Puts("C");
            Fan_off();
            SysCtlDelay(10000000);
        }

        //        Lcd_Putch((value%100)+48,1);
        //        Lcd_Putch((value%10)+48,1);
        //        Lcd_Putch((value)+48,1);

    }
}

void Temperture_Init()
{
    SYSCTL_RCGCGPIO_R |= 0x10;      /* enable clock to GPIO_PORTE */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */

    SysCtlDelay(50000);
    /* initialize PE3 for AIN0 input */
    GPIO_PORTE_AFSEL_R |= 8;        /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~8;         /* disable digital function */
    GPIO_PORTE_AMSEL_R |= 8;        /* enable analog function */
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 */
}

int TempertureRead()
{
    ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
    while((ADC0_RIS_R & 0x08) == 0)
        ;                       /* wait for conversion to complete */
    temperature = ((ADC0_SSFIFO3_R * 330) / 4096);
    ADC0_ISC_R = 8;             /* clear completion flag  */
    return temperature;
}

char *convert_data(int val)
{
    unsigned char i=0;
    static unsigned char arr[10]={0};
    if(val==0)
    {arr[i]='0';}
    else{
        while(val)//123
        {
            arr[8-i]=val%10+'0';
            val/=10;
            i++;
        }
    }
    return &arr[8-i+1];
}

void Sensor_init()
{
    SysCtlPeripheralEnable(SENSOR_PORT_ENABLE);

      GPIO_PORTF_LOCK_R = 0x4C4F434B;

      GPIO_PORTF_CR_R = 0x01;

      GPIOPinTypeGPIOInput(SENSOR_PORT, SENSOR_PIN);

      GPIO_PORTF_DEN_R = 0x1b;//PF4, PF3, PF1, PF0 as digital pins

      GPIO_PORTF_PUR_R = 0x11; //Enable pull up for PF0,PF1
    SysCtlDelay(50000);
    //GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register

}
