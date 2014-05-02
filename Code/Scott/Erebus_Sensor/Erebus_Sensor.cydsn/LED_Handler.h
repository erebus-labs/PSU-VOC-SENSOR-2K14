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
    
    #define USB     0x01
    #define MEM     0x02
    #define LOWBATT 0x03
    #define ERROR   0x04
    #define SAMPLE  0x05
    
    void USB_LED_on();
    void USB_LED_off();
    void EEPROM_LED_on();
    void EEPROM_LED_off();
    void flash_LED_on();
    void flash_LED_off();    
    
#endif

/* [] END OF FILE */
