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
    #include "EmEEPROM_Access.h"
    #include "EEPROM_Access.h"
    #include "USB_Access.h"
    
    void StartCollection_ISR();
    void EndCollection_ISR();
    void Hibernate_ISR();

    // In this struct, year is listed first to avoid compiler
    // padding - #pragma pack(n) is not a recognized directive
    // for the compiler
    
    struct header_package{
        uint16 start_block;
        uint16 sample_sensor;
        uint16 sample_unit;
        uint16 sample_interval;
        uint16 year;
        uint8 second;
        uint8 minute;
        uint8 hour;
        uint8 day;
        uint8 month;
        uint8 pad; // required to align for host when dumping data
    };
    
#endif
    
    
/* [] END OF FILE */
