/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    LED_handler.c
 *
 * Manages LED output
 *
 * ========================================
*/

/*
 * ========================================
 * Header Files
 * ========================================
*/

/* Cypress Headers */
#include "project.h"

/* Project Headers */
#include "globals.h"
#include "LED_handler.h"

/*
 * ========================================
 * Function Definitions
 * ========================================
*/

void LED_on(uint8 color){
/* 
 * Activates the RGB Led in the designated color. If one of the PWM colors is desired,
 * the PWM controller must be woken up prior to calling this function.
*/
    
    SOLID_LED_CTRL_Write(OFF);
    
    switch (color){   

    case RED:
    case GREEN:
    case BLUE:
        SOLID_LED_CTRL_Write(color);
        break;
        
    case MAGENTA:
        PWM0_CTRL_Write(PWM_BLUE);
        PWM1_CTRL_Write(PWM_RED);
        break;
            
    case YELLOW:
        PWM0_CTRL_Write(PWM_GREEN);
        PWM1_CTRL_Write(PWM_RED);
        break;
    
    case CYAN:
        PWM0_CTRL_Write(PWM_GREEN);
        PWM1_CTRL_Write(PWM_BLUE);
        break;          
        
    }
    return;
}

void LED_off(){
/* 
 * Turns off the RGB LED. This funciton does not put the PWM controller back to sleep.
*/
    
    SOLID_LED_CTRL_Write(OFF);
    PWM0_CTRL_Write(OFF);
    PWM1_CTRL_Write(OFF); 
    
    return;
}

/* [] END OF FILE */
