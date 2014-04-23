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

void rtc_init()
{
    uint16 sample_unit;
    
    sample_unit = get_variable(EE_SAMPLE_UNIT);
    
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
    
    sample_int_count = 0;
 }

void RTC_Int_Handler()
{
    sample_counter();
}

void sample_counter()
{
    uint16 sample_interval;
    
    sample_interval = get_variable(EE_SAMPLE_INTERVAL);
    
    /* Take sample if interval has been reached */
    if (sample_int_count == sample_interval)
    {
        take_sample();
        sample_int_count = 0;
        
        CyPmSaveClocks();
        CyPmSleep(1,2112);
    }
    /* Increment counter and go back to sleep if interval has not been reached */
    else
    {
        sample_int_count = sample_int_count++;
        
        CyPmSaveClocks();
        CyPmSleep(1,2112);
        
    }
    
}

void take_sample()
{
    uint16 SampledData=0; 
    
    Em_EEPROM_Start(); 
    ADC_Start();
    
    /* ADC */
    SampledData = ADC_Read16(); /* Function Starts, Converts, Stops, and Returns from ADC */
    if (SampledData & 0x8000)
   	{
    	SampledData = 0;        /* Ignore negative ADC results */
   	}
   	else if (SampledData >= 0xfff)
   	{
    	SampledData = 0xfff;    /* Ignore high ADC results */
    }
    
    
    /* EEP */
    Em_EEPROM_Write(&SampledData,TailPtr,2u);
    
    TailPtr = TailPtr + 2;
    
    CyPmSaveClocks();
    CyPmSleep(1,2112);
    
}
    
/* [] END OF FILE */
