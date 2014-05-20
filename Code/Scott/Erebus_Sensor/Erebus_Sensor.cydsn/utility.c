/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    utility.c
 *
 * Contains miscellaneous utility functions needed throughout the firmware
 *
 * ========================================
*/

#include "utility.h"

uint8 get_EEPROM_variable(uint16 var_index){
    uint8 value = 10;
    
    value = CY_GET_REG8(CYDEV_EE_BASE + var_index);
    
    return value;
}

void memory_full(){
    
    mem_full_flag = 1;
    Em_EEPROM_Write(&mem_full_flag, &mem_full_flash_flag, sizeof(uint8));

    return;
}

void check_battery(){
    uint16 SampledData = 0;
    ADC_Wakeup();
    ADC_MUX_FastSelect(BATTERY_PIN);
    
    SampledData = ADC_Read16();
    
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

void clear_button_interrupts(){
                
    // Clear any pending stop or start interrupts
    StopCollection_B_ClearInterrupt();
    StopCollection_IRQ_ClearPending();
    stop_sampling_waiting = 0;
    StartCollection_B_ClearInterrupt();
    StartCollection_IRQ_ClearPending();  
    start_sampling_waiting = 0;  
    
    return;
}

/* [] END OF FILE */
