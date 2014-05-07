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

#ifndef _LED_HANDLER_H_
    #define _LED_HANDLER_H_
    
    #include "project.h"
    #include "main.h"
    
    #define USB     0x01
    #define MEM     0x02
    #define LOWBATT 0x03
    #define ERROR   0x04
    #define SAMPLE  0x05
    
    #define OFF     0x00
    #define RED     0x01
    #define BLUE    0x02
    #define GREEN   0x03
    
    #define LED_DELAY 100
    void LED_on(uint8 target);   
    void LED_off(uint8 target);
    void blink_red();
    void blink_green();
    
#endif

/* [] END OF FILE */
