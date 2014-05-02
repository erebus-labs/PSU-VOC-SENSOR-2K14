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

static uint16 sample_int_count;
static uint16 sample_interval;

void rtc_setup()
{
    uint16 sample_unit;
    
    sample_unit = get_variable(EE_SAMPLE_UNIT);
    sample_interval = get_variable(EE_SAMPLE_INTERVAL);
    
    switch (sample_unit)
    {
        case SAMPLE_SEC: /* Seconds */
            RTC_WriteIntervalMask(0x01u);
            break;
        case SAMPLE_MIN: /* Minutes */
            RTC_WriteIntervalMask(0x02u);
            break;
        case SAMPLE_HOUR: /* Hours */
            RTC_WriteIntervalMask(0x04u);
            break;
        case SAMPLE_DAY: /* Days */
            RTC_WriteIntervalMask(0x08u);
            break;
    }
    
    sample_int_count = 0;
 }

void RTC_Int_Handler()
{
    sample_counter();
}

void sample_counter()
{
    
    /* Take sample if interval has been reached */
    if (sample_int_count == sample_interval)
    {
        take_sample();
        sample_int_count = 0;
    }
    /* Increment counter and go back to sleep if interval has not been reached */
    else
    {
        sample_int_count = sample_int_count++;
    }
    
    CyPmSaveClocks();
    CyPmSleep(1,SLEEPMASK);
    
}

void take_sample()
{
    uint16 SampledData = 0;

    ADC_Start();
    
    /* ADC */
    SampledData = ADC_Read16(); /* Function Starts, Converts, Stops, and Returns from ADC */
    
    /* EEP */
    flash_LED_on();
    Em_EEPROM_Write((uint8*) (&SampledData),TailPtr,2u);
    flash_LED_off();
    
    TailPtr = TailPtr + 2;
    
    CyPmSaveClocks();
    CyPmSleep(1,SLEEPMASK);
    
}
    
/* [] END OF FILE */
