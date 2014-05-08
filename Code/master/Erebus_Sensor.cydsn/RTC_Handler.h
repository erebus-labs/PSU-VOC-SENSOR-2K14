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
    #include "EEPROM_Access.h"
    
    void rtc_setup();
    uint8 sync_RTC(RTC_TIME_DATE* new_time);  
    
#endif

/* [] END OF FILE */
