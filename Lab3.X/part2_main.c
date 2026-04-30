/* 
 * File:   part2main.c
 * Author: root
 *
 * Created on April 27, 2026, 1:55 PM
 */

#ifdef PART2

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


/*
 * 
 */
int main(void)
{
    BOARD_Init();
    PWM_Init();
    AD_Init();
    LED_Init();
    SERIAL_Init();
    TIMERS_Init();
    
    IO_PortsSetPortInputs(PORTY, PIN8);
    IO_PortsSetPortOutputs(PORTZ, PIN4);
    IO_PortsSetPortOutputs(PORTZ, PIN6);

    AD_AddPins(AD_PORTW3);
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    
    PWM_AddPins(PWM_PORTX11);
    PWM_SetFrequency(1);
    
    printf("Running part 2: DC Motor");
    
    unsigned int adcRaw = 0, dutyCycle = 0, ledLevel = 0, LEDPattern = 0, dir = 0;
    
    // While loop below
    
    while(1)
    {
        //if new data is avail
        if(AD_IsNewDataReady()) 
        {
            
                //read and store direction pin value
                dir = PORTY08_BIT;
                
                if(dir == 1){
                    IO_PortsSetPortBits(PORTZ, PIN4);
                    IO_PortsClearPortBits(PORTZ, PIN6);  
                }
                
                else{
                    IO_PortsClearPortBits(PORTZ, PIN4);
                    IO_PortsSetPortBits(PORTZ, PIN6); 
                }
                
                //printf("Direction: %d \n", (int)dir);
                
                //read and store pin value
                adcRaw = AD_ReadADPin(AD_PORTW3); 
                
                //tramsate 10-bit ADC into pwm
                dutyCycle = (adcRaw *1000) / 1023;
                printf("Duty Cycle: %d \n", (int)dutyCycle);
                
                //setting duty cycle
                PWM_SetDutyCycle(PWM_PORTX11, dutyCycle);     
                
                
        }
        
        //setting lED
         ledLevel = (adcRaw * 8) / 1023;
         
        if (ledLevel >= 8) {
            LEDPattern = 0xFF;
        } else {
            LEDPattern = (1 << ledLevel) - 1;
        }
         
        LED_SetBank(LED_BANK1, LEDPattern & 0x0F);
        
        LED_SetBank(LED_BANK3, (LEDPattern >> 4) & 0x0F);
        
        if(dir == 1){
            LED_SetBank(LED_BANK2, 0x00);                   
        }
        else{
            LED_SetBank(LED_BANK2, 0xFF);
        }
        
    }
    // While loop above
    
    BOARD_End();
    return 0;
}
    

#endif
