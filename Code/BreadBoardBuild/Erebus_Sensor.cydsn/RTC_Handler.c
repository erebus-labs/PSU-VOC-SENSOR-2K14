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

uint8 sync_RTC(RTC_TIME_DATE* new_time){
    RTC_DisableInt();
    RTC_WriteTime(new_time);
    RTC_EnableInt();
    
    return SUCCESS;
}
/* [] END OF FILE */
