
/* 
 * File:   part5main.c
 * Author: root
 *
 * Created on April 27, 2026, 1:55 PM
 */

#ifdef PART5

#include "xc.h"
#include "BOARD.h"
#include "serial.h"
#include "LED.h"
#include "IO_Ports.h"
#include "pwm.h"
#include "AD.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "Stepper.h"

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    Stepper_Init();
    AD_Init();
    LED_Init();
    SERIAL_Init();
    TIMERS_Init();
    
  
    AD_AddPins(AD_PORTW3);
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    
    
    printf("Running part 5: Stepper Motor");
    
    unsigned int adcRaw = 0, dutyCycle = 0, ledLevel = 0, LEDPattern = 0;
    
    // While loop below
    
    while(1)
    {
        //if new data is avail
        if(AD_IsNewDataReady()) 
        {
            
                //read and store pin value
                adcRaw = AD_ReadADPin(AD_PORTW3); 
                

        }
        
        //setting lED
         ledLevel = (adcRaw * 8) / 1023;
         
        if (ledLevel >= 8) {
            LEDPattern = 0xFF;
        } else {
            LEDPattern = (1 << ledLevel) - 1;
        }
         
        LED_SetBank(LED_BANK1, LEDPattern & 0x0F);
        LED_SetBank(LED_BANK2, (LEDPattern >> 4) & 0x0F);
        LED_SetBank(LED_BANK3, (LEDPattern >> 4) & 0x0F);
    }
    // While loop above
    
    BOARD_End();
    return 0;
}
    

#endif
