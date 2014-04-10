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
#include "RTC_handler.h"
#include "project.h"
#include "EmEEPROM_Access.h"
#include "EEPROM_Access.h"
#include "RTC_1.h"
#include "project.h"


void rtc_init()
{
    uint16 sample_unit;
    
    sample_unit = get_variable(sample_unit);
    
    switch (sample_unit)
    {
        case 1: /* Seconds */
            RTC_1_WriteIntervalMask(0x01u);
            break;
        case 2: /* Minutes */
            RTC_1_WriteIntervalMask(0x02u);
            break;
        case 3: /* Hours */
            RTC_1_WriteIntervalMask(0x04u);
            break;
        case 4: /* Days */
            RTC_1_WriteIntervalMask(0x08u);
            break;
        case 5: /* Weeks */
            RTC_1_WriteIntervalMask(0x10u);
            break;
        case 6: /* Months */
            RTC_1_WriteIntervalMask(0x20);
            break;
        case 7: /* Years */
            RTC_1_WriteIntervalMask(0x30u);
            break;
    }
 }   
/* [] END OF FILE */
