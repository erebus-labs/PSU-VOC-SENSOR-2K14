/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    LED_handler.h
 *
 * Contains macros, header file inclusions, and function prototypes
 * required by LED-related functions
 *
 * ========================================
*/

#ifndef _LED_HANDLER_H_
    #define _LED_HANDLER_H_
    
    /*
     * ========================================
     * Header Files
     * ========================================
    */
    
    /* Cypress Headers */
    #include "project.h"
    
    /* Project Headers */
    #include "globals.h"
    
    /*
     * ========================================
     * Macros
     * ========================================
    */
    
    /* Available Colors */
    #define OFF     0x00
    #define GREEN   0x01
    #define RED     0x02
    #define MAGENTA 0x03
    #define BLUE    0x04
    #define YELLOW  0x05
    #define CYAN    0x06
    
    /* PWM Color Codes */
    #define PWM_GREEN   0x01
    #define PWM_RED     0x02
    #define PWM_BLUE    0x03

    /* Other */
    #define LED_DELAY   25
    /* LED_DELAY specifies how many milliseconds chip should stall
     * while temporarily blinking an LED for a user to see */
    
    /*
     * ========================================
     * Function Prototypes
     * ========================================
    */
    
    void LED_on(uint8 color);   
    void LED_off();
    
#endif /* ifndef _LED_HANDLER_H_ */
        
/* [] END OF FILE */
