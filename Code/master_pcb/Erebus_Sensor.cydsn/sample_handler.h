/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    sample_handler.h
 *
 * Contains macros, header file inclusions, function prototypes,
 * and structures required by sampling-related functions
 *
 * ========================================
*/

#ifndef _SAMPLE_HANDLER_H_
    #define _SAMPLE_HANDLER_H_
    
    /*
     * ========================================
     * Header Files
     * ========================================
    */
    
    /* Cypress Headers */
    #include "project.h"
    
    /* Project Headers */
    #include "globals.h"
    #include "utility.h"
    
    /*
     * ========================================
     * Macros
     * ========================================
    */
    
    #define SAMPLE_BLOCK_SIZE   25000 
    #define STARTBLOCK          0x2000
    #define MASTER_ROWS         3
    #define FLASH_ROW_LENGTH    (CYDEV_FLS_ROW_SIZE + CYDEV_ECC_ROW_SIZE)
    #define HEAD_INDEX          0
    #define TAIL_INDEX          1
    #define MASTER_PTR_COUNT    2
    #define SAMPLE_SHIFT        4
    #define SAMPLE_MASK         0x0FFF
    
    /* RTC Periodic Interrupt Masks */    
    #define NONE_MASK   0x00u
    #define SECOND_MASK 0x01u
    #define MINUTE_MASK 0x02u
    #define HOUR_MASK   0x04u
    #define DAY_MASK    0x08u
    
    /* Sample Unit Choices */
    #define SAMPLE_SEC      0x00
    #define SAMPLE_MIN      0x01
    #define SAMPLE_HOUR     0x02
    #define SAMPLE_DAY      0x03 
    
    /*
     * ========================================
     * Structures
     * ========================================
    */
    
    /* In the header_package struct, year is listed first to
     * avoid compiler padding - #pragma pack(n) is not a
     * recognized directive for the Keil 8051 compiler used
     * by PSoC Creator */
    
    struct header_package{
        uint16 start_block;
        uint16 year;
        uint8 sample_sensor;
        uint8 sample_unit;
        uint8 sample_interval;
        uint8 second;
        uint8 minute;
        uint8 hour;
        uint8 day;
        uint8 month;
        
        /* Add reserved pad bytes to force natural alignment
         * These may be replaced with useful data as needed */
        uint8 rsvd1;
        uint8 rsvd2;
        uint8 rsvd3;
        uint8 rsvd4;
        
    };
    
    /*
     * ========================================
     * Function Prototypes
     * ========================================
    */
    
    void sampling_setup();
    void start_collection();
    void take_sample(); 
    void stop_collection();
    uint8 store_in_flash(uint8* buffer, uint8 num_bytes);
    void clear_samples();
    void reset_pointers();
    
#endif /* ifndef _SAMPLE_HANDLER_H_ */

/* [] END OF FILE */
