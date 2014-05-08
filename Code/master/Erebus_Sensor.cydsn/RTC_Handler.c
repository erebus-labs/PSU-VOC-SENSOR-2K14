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
    uint8 sample_unit;
    
    sample_unit = get_variable(EE_SAMPLE_UNIT);
    // sample_interval is global, defined in Sample_Handler.c  
    sample_interval = get_variable(EE_SAMPLE_INTERVAL);
   
    switch (sample_unit)
    {
        case SAMPLE_SEC: /* Seconds */
            RTC_int_mask = SECOND_MASK;
            break;
        case SAMPLE_MIN: /* Minutes */
            RTC_int_mask = MINUTE_MASK;
            break;
        case SAMPLE_HOUR: /* Hours */
            RTC_int_mask = HOUR_MASK;
            break;
        case SAMPLE_DAY: /* Days */
            RTC_int_mask = DAY_MASK;
            break;
    }
    
    // Start by clearing interval interrupt masks - the appropriate interrupt will
    // be enabled by the start collection button interrupt
    RTC_WriteIntervalMask(NONE_MASK);
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
