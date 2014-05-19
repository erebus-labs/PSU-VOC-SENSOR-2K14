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

#ifndef _GLOBAL_H_
    #define _GLOBAL_H_
    
    #include "project.h"

    // RAM Variables
    extern uint8 low_power_flag;
    extern uint8 USB_waiting;
    extern uint8 DataStart_waiting;
    extern uint8 DataStop_waiting;
    extern uint8 Sample_waiting;
    extern uint8 sample_int_count;
    extern uint8 sample_unit;
    extern uint8 sample_interval;    
    extern uint8 RTC_int_mask;
    extern uint8 battery_check_count;
    extern uint8 LowPowerBlink_waiting;
    extern uint8 BatteryCheck_waiting;
    extern uint8 low_batt_blink_count;
    extern uint8 sample_enable;
    extern uint8 mem_full_flag;
    
    extern volatile uint16 pointer_head_index;
    extern volatile uint16 pointer_tail_index;
    extern volatile uint16 sample_head_index;
    extern volatile uint16 sample_tail_index;
    
    // FLASH Variables
    extern const uint8 CYCODE sample_block[]; 
    extern const uint16 CYCODE current_sample_indices[];
    extern const uint16 CYCODE master_sample_indices[];
    extern const uint8 CYCODE mem_full_flash_flag;
    
    
    
#endif

/* [] END OF FILE */
