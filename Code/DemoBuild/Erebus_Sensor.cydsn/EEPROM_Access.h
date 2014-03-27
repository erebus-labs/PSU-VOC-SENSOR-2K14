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
    
    #define EE_ADDR (unsigned char*) CYDEV_EE_BASE
    #define EEPROM_ROWS CYDEV_EE_SIZE / CYDEV_EEPROM_ROW_SIZE
    #define SECTOR_NUMBER 0
    #define NUM_VARS 1 // the number of recognized user variables
    
    // User Variable Locations in EEPROM
    
    // The index and size of each user variable are defined here
    
    #define BLINK_RATE_INDEX    0x0000
    
    // EEPROM_BYTES_USED is boring for now - as more variables are
    // added, it will be calculated based on previous macros
    #define EEPROM_BYTES_USED BLINK_RATE_INDEX + 2

    // Function Prototypes
    
    uint8* get_variable(uint16 index, uint8 size);
    void update_variable(uint16 index, uint16 value);
    

#endif // ifndef _EEPROM_ACCESS_H_

/* [] END OF FILE */
