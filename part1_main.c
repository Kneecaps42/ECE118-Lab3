/* 
 * File:   part1_main.c
 * Author: root
 *
 * Created on April 27, 2026, 1:55 PM
 */

#ifdef PART1

#include "BOARD.h"
#include "serial.h"
#include "RC_Servo.h"
#include "LED.h"
#include "IO_Ports.h"
#include "pwm.h"
#include "AD.h"
#include <stdint.h>
#include <stdio.h>

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    RC_Init();
    AD_Init();
    LED_Init();
    
    RC_AddPins(RC_PORTX03);
    AD_AddPins(AD_PORTW3);
    LED_AddBanks(LED_BANK1 || LED_BANK2 || LED_BANK3);
    
    printf("Running part 1: RC Servo\n");
    
    while(1)
    {
        
    }
    
    BOARD_End();
    return 0;
}

#endif