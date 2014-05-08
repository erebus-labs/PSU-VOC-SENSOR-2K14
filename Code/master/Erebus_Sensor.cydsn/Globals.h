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
    extern uint16 sample_int_count;
    
    extern uint8 RTC_int_mask;
    
    extern uint8 sample_interval;
    
    // FLASH Variables
    extern const uint8 CYCODE hard_reset_flag; 
    extern const uint8 CYCODE MemoryLocation[];
    extern const volatile uint8* TailPtr;
    
#endif

/* [] END OF FILE */
