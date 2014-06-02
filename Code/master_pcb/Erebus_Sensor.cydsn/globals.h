/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    globals.h
 *
 * Contains all global variable declarations
 *
 * ========================================
*/

#ifndef _GLOBALS_H_
    #define _GLOBALS_H_
    
    /*
     * ========================================
     * Header Files
     * ========================================
    */
    
    /* Cypress Headers */
    #include "project.h"

    /*
     * ========================================
     * Variable Declarations
     * ========================================
    */
    
    /* Awaiting Action Flags */ 
    extern uint8 start_sampling_waiting;
    extern uint8 stop_sampling_waiting;
    extern uint8 take_sample_waiting;
    extern uint8 USB_waiting;
    extern uint8 battery_check_waiting;
    extern uint8 low_battery_blink_waiting;
    
    /* Condition Flags */
    extern uint8 sample_enable_flag;
    extern uint8 low_power_flag;
    extern uint8 mem_full_flag;
    
    extern uint8 stop_collection_enabled;
    extern uint8 start_collection_enabled;
    
    /* Counters for Events */
    extern uint8 sample_interrupt_count;
    extern uint8 battery_check_count;
    extern uint8 low_batt_blink_count;
    
    /* RTC Parameters
     * These are kept in SRAM to prevent EEPROM reads during RTC
     * interrupts */
    extern uint8 sample_unit;
    extern uint8 sample_interval;    

    /* Nonvolatile Variables stored in Flash */
    extern const uint8 CYCODE sample_block[]; 
    extern const uint16 CYCODE current_sample_indices[];
    extern const uint16 CYCODE master_sample_indices[];
    extern const uint8 CYCODE mem_full_flash_flag;
    
    /* SRAM Head/Tail Indexes */
    /* These are copies of the head/tail indexes stored in
     * current_sample_indices[] and master_sample_indices[] in
     * Flash - they are kept around to prevent additional
     * Flash reads while sampling */
    extern volatile uint16 pointer_head_index;
    extern volatile uint16 pointer_tail_index;
    extern volatile uint16 sample_head_index;
    extern volatile uint16 sample_tail_index;
    
#endif /* ifndef _GLOBALS_H_ */

/* [] END OF FILE */
