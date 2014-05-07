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

#ifndef _INTERFACE_H_
    #define _INTERFACE_H_
    
    #include "project.h"
    #include "EEPROM_Access.h"
    #include "RTC_Handler.h"
    #include "USB_Access.h"
    #include "Globals.h"
    #include "Macros.h"
    
    void StartCollection();
    void StopCollection();
    void LED_on(uint8 target);   
    void LED_off(uint8 target);
    
    // In this struct, year is listed first to avoid compiler
    // padding - #pragma pack(n) is not a recognized directive
    // for the compiler
    
    struct header_package{
        uint16 start_block;
        uint16 year;
        uint8 sample_sensor;
        uint8 sample_unit;
        uint8 sample_interval;
        uint8 second;
        uint8 minute;
        uint8 hour;
        uint8 day;
        uint8 month;
    };
    
#endif
    
    
/* [] END OF FILE */
