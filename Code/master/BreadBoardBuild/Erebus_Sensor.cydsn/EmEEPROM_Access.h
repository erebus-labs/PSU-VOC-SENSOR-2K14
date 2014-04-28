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

#ifndef _EMEEPROM_ACCESS_H_
    #define _EMEEPROM_ACCESS_H_
    #include "project.h"

    // Emulated EEPROM/FLASH
    #define EmEEPROMSize 1024 
    extern const uint8 CYCODE MemoryLocation[];
    extern const volatile uint8* TailPtr;
    
#endif
/* [] END OF FILE */
