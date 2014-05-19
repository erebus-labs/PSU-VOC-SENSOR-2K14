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
    #include "Utility.h"
    #include "Globals.h"
    #include "Macros.h"
    
    void StartCollection();
    void StopCollection();
    void LED_on(uint8 color);   
    void LED_off();
    
    // In this struct, year is listed first to avoid compiler
    // padding - #pragma pack(n) is not a recognized directive
    // for the compiler
    
    /* If this structure is modified, make sure it still contains
     * an even number of bytes. Other flash storage routines rely
     * on 2-byte aligned accesses. */
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
        
        /* Add reserved pad bytes to force natural alignment
        uint8 rsvd1;
        uint8 rsvd2;
        uint8 rsvd3;
        uint8 rsvd4;
        */
    };
    
#endif
    
    
/* [] END OF FILE */
