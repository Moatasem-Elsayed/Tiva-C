#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "LCD.h"

//vdd=+
//vss=-

int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    Lcd_init();
    while(1){
        Lcd_Goto(1,1);
        Lcd_Puts("Muhammet Tayyip");
        Lcd_Goto(2,5);
        Lcd_Puts("CANKAYA ");
        SysCtlDelay(SysCtlClockGet()/2);
        Lcd_Temizle();

        Lcd_Goto(1,3);
        Lcd_Puts("GEBZE TEKNIK");
        Lcd_Goto(2,3);
        Lcd_Puts("UNIVERSITESI");
        SysCtlDelay(SysCtlClockGet()/2);
        Lcd_Temizle();}
}
