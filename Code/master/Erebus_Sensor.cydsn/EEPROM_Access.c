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

uint8 update_settings(settings_group new_settings){
    
    uint8* buffer;
    float rows_used = 0;
    uint16 remainder = 0;
    uint8* src_ptr;
    uint8* dst_ptr;
    uint8 i = 0; // loop var
    float bytes_used = EEPROM_BYTES_USED;
    uint8 result = SUCCESS;
    cystatus status;
    
    // Allocate array to hold EEPROM variables
    
    rows_used = ceil(bytes_used/CYDEV_EEPROM_ROW_SIZE);
    buffer = malloc(((uint16) rows_used) * CYDEV_EEPROM_ROW_SIZE);
    
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
    
    // Modify variables in RAM
    buffer[0] = new_settings.sensor;
    buffer[1] = new_settings.sample_unit;
    buffer[2] = new_settings.sample_interval;
    
    // Erase EEPROM
    // Disable interrupts during EEPROM operation
    CyGlobalIntDisable;
    status = EEPROM_R_EraseSector(SECTOR_NUMBER);
    CyGlobalIntEnable;
    
    if (status != CYRET_SUCCESS){
        result = FAIL;
        goto exit;
    }
    
    // Write back modified EEPROM Variables
    i = 0;
    src_ptr = buffer;
    while ((i < rows_used) && (i < EEPROM_ROWS)){
        // Disable interrupts during EEPROM operation
        CyGlobalIntDisable;
        status = EEPROM_R_Write(src_ptr, i);
        CyGlobalIntEnable;
        
        if (status != CYRET_SUCCESS){
           result = FAIL;
        goto exit;
    }
        src_ptr = src_ptr + CYDEV_EEPROM_ROW_SIZE;
        ++i;
    }
     
    // Free buffer memory
    free(buffer);
    
exit:   
    return result;   
}

uint8 get_variable(uint16 var_index){
    uint8 value = 10;
    
    value = CY_GET_REG8(CYDEV_EE_BASE + var_index);
    
    return value;
}


/* [] END OF FILE */
