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

#include "RTC_Handler.h"

uint8 RTC_int_mask = 0x0u;

void rtc_setup()
{

    // sample_interval and sample_unit are global, defined in main.c    
    sample_unit = get_variable(EE_SAMPLE_UNIT);
    sample_interval = get_variable(EE_SAMPLE_INTERVAL);
    
    RTC_int_mask = MINUTE_MASK | SECOND_MASK;
    
    switch (sample_unit)
    {
        case SAMPLE_HOUR: /* Hours */
            RTC_int_mask = RTC_int_mask | HOUR_MASK;
            break;
        case SAMPLE_DAY: /* Days */
            RTC_int_mask = RTC_int_mask | DAY_MASK;
            break;
    }
    
    RTC_WriteIntervalMask(RTC_int_mask);
    RTC_EnableInt();
    
    return;
 }

uint8 sync_RTC(RTC_TIME_DATE* new_time){
    
    RTC_DisableInt();
    RTC_WriteTime(new_time);
    RTC_EnableInt();
    
    return SUCCESS;
}
/* [] END OF FILE */
