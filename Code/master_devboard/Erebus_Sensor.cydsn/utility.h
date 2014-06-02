/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    utility.h
 *
 * Contains macros, header file inclusions, and function prototypes
 * required by utility functions
 *
 * ========================================
*/

#ifndef _UTILITY_H_
    #define _UTILITY_H_
        
    /*
     * ========================================
     * Header Files
     * ========================================
    */
    
    /* Cypress Headers */
    #include "project.h"
    
    /* Project Headers */
    #include "globals.h"
    
    /*
     * ========================================
     * Macros
     * ========================================
    */
        
    /* Analog Multiplexer for ADC */
    #define SAMPLE_PIN  0x0
    #define BATTERY_PIN 0x1
    
    /* Battery Level Checking */
    /* BATT_CHECK_INTERVAL: Number of minutes between battery checks
     * BATT_THRESHOLD:      Trigger level of low-battery warning - reading from ADC */
    #define BATT_CHECK_INTERVAL     1
    #define BATT_THRESHOLD          1392
    #define LOWBATT_BLINK_INTERVAL  3
    #define LOWBATT_BLINK_DELAY     100
    
    /* Sample Parameter Variable Indexes in EEPROM */
    #define EE_SENSOR           0x0
    #define EE_SAMPLE_UNIT      EE_SENSOR + 1
    #define EE_SAMPLE_INTERVAL  EE_SAMPLE_UNIT + 1

    
    /*
     * ========================================
     * Funciton Prototypes
     * ========================================
    */
    
    void check_battery();
    void memory_full();       
    uint8 get_EEPROM_variable(uint16 var_index);
    void clear_button_interrupts();
    
#endif /* ifndef _UTILITY_H_ */

/* [] END OF FILE */
