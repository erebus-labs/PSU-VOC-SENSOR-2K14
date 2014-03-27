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
    double rows_used = 0;
    uint16 remainder = 0;
    uint8* src_ptr = EE_ADDR;
    uint8* dst_ptr;
    uint8 i = 0; // loop var
    cystatus status;
    
    // Allocate array to hold EEPROM variables
    rows_used = ceil(EEPROM_BYTES_USED/16);
    buffer = malloc(rows_used * 16);
    dst_ptr = buffer;
    remainder = (rows_used * 16) - EEPROM_BYTES_USED;
    
    // Copy all variables into RAM
    for (i=0; i<EEPROM_BYTES_USED; ++i){
        *dst_ptr = *src_ptr;
        ++dst_ptr;
        ++src_ptr;        
    }
    
    // Fill remainder of buffer with zeros
    while (i < remainder){
        *dst_ptr = 0;
        ++i;
    }
    
    // Modify variable in RAM
    buffer[index] = (uint8) value >> 0x8;
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
    
    return;   
}


/* [] END OF FILE */
