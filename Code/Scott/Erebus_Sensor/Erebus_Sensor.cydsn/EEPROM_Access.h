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

    #include "Project.h"
    #include "cytypes.h"
    #include "math.h"
    #include "stdlib.h"

    // MACROS
    
    #define EEPROM_ROWS CYDEV_EE_SIZE / CYDEV_EEPROM_ROW_SIZE
    #define SECTOR_NUMBER 0

    // EEPROM Array index of each user variable 
    #define EE_SAMPLE_UNIT      0x0000
    #define EE_SAMPLE_INTERVAL  EE_SAMPLE_UNIT + 2
    #define EE_SENSOR           EE_SAMPLE_INTERVAL +2
       
    // RTC Time Unit Codes
    #define SAMPLE_SEC      0x01
    #define SAMPLE_MIN      0x02
    #define SAMPLE_HOUR     0x03
    #define SAMPLE_DAY      0x04
    
    // Total number of bytes used in EEPROM
    #define EEPROM_BYTES_USED EE_SENSOR + 2

    // Function Prototypes
    
    uint16 get_variable(uint16 index);
    void update_variable(uint16 index, uint16 value);
    
#endif // ifndef _EEPROM_ACCESS_H_

/* [] END OF FILE */
