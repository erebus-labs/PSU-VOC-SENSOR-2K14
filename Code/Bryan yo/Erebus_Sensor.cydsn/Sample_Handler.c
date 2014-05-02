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
#include "Sample_Handler.h"
#include "project.h"
#include "EmEEPROM_Access.h"
#include "EEPROM_Access.h"
#include "RTC_1.h"

uint16 sample_int_count;

void RTC_Prep()
{
    uint16 sample_unit;
    
    uint8 EE_SAMPLE_UNIT = 1u;
    
    //sample_unit = get_variable(EE_SAMPLE_UNIT);
    sample_unit = EE_SAMPLE_UNIT;
    
    switch (sample_unit)
    {
        case 1: /* Seconds */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_SEC_MASK);
            break;
        case 2: /* Minutes */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_MIN_MASK);
            break;
        case 3: /* Hours */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_HOUR_MASK);
            break;
        case 4: /* Days */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_DAY_MASK);
            break;
        case 5: /* Weeks */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_WEEK_MASK);
            break;
        case 6: /* Months */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_MONTH_MASK);
            break;
        case 7: /* Years */
            RTC_1_WriteIntervalMask(RTC_1_INTERVAL_YEAR_MASK);
            break;
    }
    
    sample_int_count = 0u;
 }

void RTC_Int_Handler()
{
    CyPmReadStatus(4u);
    
    
    if (sample_counter())
    {
        take_sample();
    }
    
    //CyPmSaveClocks();
    //CyPmSleep(1,2112);
    
}

uint16 sample_counter()
{
    uint16 sample_interval;
    
    
    uint16 EE_SAMPLE_INTERVAL = 2u;
    
    //sample_interval = get_variable(EE_SAMPLE_INTERVAL);
    sample_interval = EE_SAMPLE_INTERVAL;
        
    /* Take sample if interval has been reached */
    if (sample_int_count == sample_interval)
    {
        take_sample();
        sample_int_count = 0u;
        
        return 1u;
    }
    /* Increment counter and go back to sleep if interval has not been reached */
    else
    {
        sample_int_count++;
        
        return 0u;
    }
}

void take_sample()
{
    uint16 SampledData=0; 
    uint8 pin_stat;
    
    
    pin_stat = Sample_LED_Read();
    
    if (pin_stat)
    {
        Sample_LED_Write(0u);
    }
    else
    {
        Sample_LED_Write(1u);
    }
    
}
    
/* [] END OF FILE */
