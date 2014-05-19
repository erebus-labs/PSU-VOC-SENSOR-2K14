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

#include "Utility.h"

void reset_pointers(){
    
    uint16 zero = 0x00;
    uint16 tail_ix = TAIL_INDEX;
    uint16 head_ix = HEAD_INDEX;
        
    // reset master pointers 
    Em_EEPROM_Write((uint8*) &head_ix, (uint8*) &(master_sample_indices[HEAD_INDEX]), sizeof(uint16));
    Em_EEPROM_Write((uint8*) &tail_ix, (uint8*) &(master_sample_indices[TAIL_INDEX]), sizeof(uint16));
    
    // reset sample pointers to the top of the sample block
    Em_EEPROM_Write((uint8*) &zero, (uint8*) &(current_sample_indices[HEAD_INDEX]), sizeof(uint16));
    Em_EEPROM_Write((uint8*) &zero, (uint8*) &(current_sample_indices[TAIL_INDEX]), sizeof(uint16));
    
    return;
}

void memory_full(){
    
    StopCollection_IRQ_Stop();
    sample_enable = 0;
    mem_full_flag = 1;
    Em_EEPROM_Write(&mem_full_flag, &mem_full_flash_flag, sizeof(uint8));
    LED_on(RED);

    return;
}

void check_battery(){
    uint16 SampledData = 0;
    ADC_Wakeup();
    ADC_MUX_Select(BATT_PIN);
    
    SampledData = ADC_Read16(); /* Function Starts, Converts, Stops, and Returns from ADC */
    
    if (SampledData <= BATT_THRESHOLD){
        low_power_flag = 1;
    }
    else{
        low_power_flag = 0;
    }
    
    ADC_Sleep();
    ADC_MUX_FastSelect(SAMPLE_PIN);
    
    return;
}

/* [] END OF FILE */
