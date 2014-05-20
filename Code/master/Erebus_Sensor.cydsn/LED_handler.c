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

#include "LED_handler.h"

void LED_on(uint8 color){
    
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
    
    SOLID_LED_CTRL_Write(OFF);
    PWM0_CTRL_Write(OFF);
    PWM1_CTRL_Write(OFF); 
    
    return;
}

/* [] END OF FILE */
