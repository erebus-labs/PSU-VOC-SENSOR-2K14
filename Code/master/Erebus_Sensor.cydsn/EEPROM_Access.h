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

#ifndef _EEPROM_ACCESS_H_
    #define _EEPROM_ACCESS_H_

    // This file contains data required to access variables stored in real EEPROM

    // INCLUSIONS

    #include <math.h>
    #include <stdlib.h>
    #include "Project.h"
    #include "cytypes.h"
    #include "LED_Handler.h"
    #include "USB_Access.h" // included for FAIL and SUCCESS macros

    // MACROS
    
    #define EEPROM_ROWS CYDEV_EE_SIZE / CYDEV_EEPROM_ROW_SIZE
    #define SECTOR_NUMBER 0

    // EEPROM Array index of each user variable 
    #define EE_SENSOR           0x0
    #define EE_SAMPLE_UNIT      EE_SENSOR + 1
    #define EE_SAMPLE_INTERVAL  EE_SAMPLE_UNIT + 1

    #define EEPROM_BYTES_USED   0x3
    #define NUM_SETTINGS        0x3
       
    // RTC Time Unit Codes
    #define SAMPLE_SEC      0x00
    #define SAMPLE_MIN      0x01
    #define SAMPLE_HOUR     0x02
    #define SAMPLE_DAY      0x03

    // Structures
    typedef struct eeprom_settings{
        uint8 sensor;
        uint8 sample_unit;
        uint8 sample_interval;
    }settings_group;
       
    // Function Prototypes
    
    uint8 get_variable(uint16 index);
    uint8 update_settings(settings_group new_settings);
    
#endif // ifndef _EEPROM_ACCESS_H_

/* [] END OF FILE */
