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

#include "EEPROM_Access.h"

void update_variable(uint16 index, uint16 value){
    
    uint8* buffer;
    float rows_used = 0;
    uint16 remainder = 0;
    uint8* src_ptr;
    uint8* dst_ptr;
    uint8 i = 0; // loop var
    float bytes_used = EEPROM_BYTES_USED;
    cystatus status;
    
    EEPROM_LED_on();
    
    // Allocate array to hold EEPROM variables
    
    rows_used = ceil(bytes_used/16);
    buffer = malloc(((uint16) rows_used) * 16);
    dst_ptr = buffer;
    remainder = (rows_used * 16) - EEPROM_BYTES_USED;
    
    // Copy all variables into RAM
    for (i=0; i<EEPROM_BYTES_USED; ++i){
        *dst_ptr = CY_GET_REG8(CYDEV_EE_BASE + i);
        ++dst_ptr;      
    }
    
    // Fill remainder of buffer with zeros
    while (i < remainder){
        *dst_ptr = 0;
        ++i;
    }
    
    // Modify variable in RAM
    buffer[index] = (uint8) (value >> 0x8);
    buffer[index+1] = (uint8) value & 0xFF;
    
    // Erase EEPROM
    status = EEPROM_R_EraseSector(SECTOR_NUMBER);
    
    // Write back modified EEPROM Variables
    i = 0;
    src_ptr = buffer;
    while ((i < rows_used) && (i < EEPROM_ROWS)){
        EEPROM_R_Write(src_ptr, i);
        src_ptr = src_ptr + CYDEV_EEPROM_ROW_SIZE;
        ++i;
    }
     
    // Free buffer memory
    free(buffer);
    
   EEPROM_LED_off();
    
    return;   
}

uint16 get_variable(uint16 var_index){
    uint16 value = 10;
    
   EEPROM_LED_on();
    
    value = ((uint16) CY_GET_REG8(CYDEV_EE_BASE + var_index)) << 8;
    value = value | CY_GET_REG8(CYDEV_EE_BASE + var_index + 1);
    
   EEPROM_LED_off();
    
    return value;
}


/* [] END OF FILE */
