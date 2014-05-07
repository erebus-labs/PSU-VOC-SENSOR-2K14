/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "LED_Handler.h"

static uint8 state;

void LED_on(uint8 target){
    
    switch (target){   
    
        case USB:
            /* Green */
            LED0_CTRL_Write(GREEN);
            LED1_CTRL_Write(GREEN);
            break;
        
        case ERROR:
            /* Red */
            LED0_CTRL_Write(RED);
            LED1_CTRL_Write(RED);
            break;
            
        case LOWBATT:
            /* Yellow */
            LED0_CTRL_Write(GREEN);
            LED1_CTRL_Write(RED);
            break;
        
        case SAMPLE:
            /* BLUE */
            LED0_CTRL_Write(BLUE);
            LED1_CTRL_Write(GREEN);
            break;  
            
        case MEM:
            /* Cyan */
            LED0_CTRL_Write(BLUE);
            LED1_CTRL_Write(BLUE);  
            break;
    }
    return;
}

void LED_off(uint8 target){
    
    switch (target){
        
        case USB:
            /* Green */
            LED0_CTRL_Write(OFF);
            LED1_CTRL_Write(OFF);
            break;
   
        case SAMPLE:
                
            if (low_power_flag){
                LED0_CTRL_Write(GREEN);
                LED1_CTRL_Write(RED);
            }
            
            else{
                LED0_CTRL_Write(OFF);
                LED1_CTRL_Write(OFF);
            }      
            break;  
            
        case MEM:         
            if (Vbus_Read()){
                LED0_CTRL_Write(GREEN);
                LED1_CTRL_Write(GREEN);
            }
            else{
                LED0_CTRL_Write(OFF);
                LED1_CTRL_Write(OFF);
            } 
            break;
    }
    
    return;
}

void blink_green(){
    
    uint8 i;
    
    /* This loop has an odd structure so that there is no delay after it's turned off
       the last time */
    
    LED_on(USB); // pretend it's USB since USB is solid green
    for(i=4;i>0;--i){

        CyDelay(LED_DELAY);
        LED_off(USB);
        CyDelay(LED_DELAY);
        LED_on(USB);

    }
    CyDelay(LED_DELAY);
    LED_off(USB);
    
    return;
}

void blink_red(){
    
    uint8 i;
    
    /* This loop has an odd structure so that there is no delay after it's turned off
       the last time */
    
    LED_on(ERROR); // pretend it's ERROR since ERROR is solid red
    for(i=4;i>0;--i){

        CyDelay(LED_DELAY);
        LED_off(USB); // leave off as USB - ERROR has no off
        CyDelay(LED_DELAY);
        LED_on(ERROR);

    }
    CyDelay(LED_DELAY);
    LED_off(USB);
    
    return;
}

/* [] END OF FILE */
