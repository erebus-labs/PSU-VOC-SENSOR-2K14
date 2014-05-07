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

#ifndef _RTC_HANDLER_H_
    #define _RTC_HANDLER_H_
    
    #include "project.h"
    #include "Common.h"
    #include "EEPROM_Access.h"
    
    #define TIME_LENGTH 7

    #define NONE_MASK   0x00u
    #define SECOND_MASK 0x01u
    #define MINUTE_MASK 0x02u
    #define HOUR_MASK   0x04u
    #define DAY_MASK    0x08u
    
    void rtc_setup();
    uint8 sync_RTC(RTC_TIME_DATE* new_time);
    
    extern uint8 RTC_int_mask;
    
#endif

/* [] END OF FILE */
