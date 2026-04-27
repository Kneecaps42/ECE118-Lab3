/* 
 * File:   part1_main.c
 * Author: root
 *
 * Created on April 27, 2026, 1:55 PM
 */

#ifdef PART1

#include "xc.h"
#include "BOARD.h"
#include "serial.h"
#include "RC_Servo.h"
#include "LED.h"
#include "IO_Ports.h"
#include "pwm.h"
#include "AD.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "timers.h"

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    RC_Init();
    AD_Init();
    LED_Init();
    SERIAL_Init();
    TIMERS_Init();
    
    RC_AddPins(RC_PORTX03);
    AD_AddPins(AD_PORTW3);
    LED_AddBanks(LED_BANK1 || LED_BANK2 );
    
    printf("Running part 1: RC Servo\n");
    
    while(1)
    {
        //if new data is avail
        if(AD_IsNewDataReady() == TRUE) {
            
            //read and store pin value
            unsigned int adcRaw = AD_ReadADPin(AD_PORTW3); 
            unsigned int adcTrimmed = (adcRaw >> 6) & 0x0F;
            unsigned int LEDTrimmed = (adcRaw >> 7) & 0x0F;
        
    
            //conversion from ad value to pwm 
            //1500 middle, +-45 = 400us range
            //1100 + 7*5 * 53 = ~1500
            //1500 - (7.5 * 53) = ~1100
            //1500 + (7.5 * 53) = ~1900
            unsigned int pwmVal = 1100 + (adcTrimmed * 53);
            
            
            //setting lED
            unsigned int LEDPattern = 0x01;
            for(int i = 0; i< LEDTrimmed;i++){
             LEDPattern |= LEDPattern << 1;
            }
            
            LED_SetBank(LED_BANK1, LEDPattern);
            LED_SetBank(LED_BANK2, LEDPattern >>4 );
            
            
            LED_SetBank(LED_BANK3, adcTrimmed);
            
            //setting servo 
            RC_SetPulseTime(RC_PORTX03, pwmVal);
                     
                     
    }
    
    BOARD_End();
    return 0;
}

}
#endif