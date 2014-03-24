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

// MACROS

#define SECTOR_NUMBER 0

// STRUCTURES

// Contains EEPROM memory addresses for variables
typedef struct eeprom_Address{
    uint16 blink_rate;
}eeAddress;

// Provides a temporary storage location for all EEPROM vars during erasing
typedef struct eeprom_Temporary{
    uint8 blink_rate;
}eeTemporary;

// GLOBALS

extern eeAddress EEPROM_Addresses;

#endif // ifndef _EEPROM_ACCESS_H_

/* [] END OF FILE */
