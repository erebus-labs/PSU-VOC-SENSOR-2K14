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

static uint16 sample_int_count = 0;
uint8 sample_interval;

void sample_counter()
{
    // Begin interrupt handling
    CyPmReadStatus(4u);
    //End interrupt handling
    
    /* Take sample if interval has been reached */   
    ++sample_int_count;
    
    if (sample_int_count == sample_interval)
    {
        take_sample();
        sample_int_count = 0;
    }
 
    return;   
}

void take_sample()
{
    uint16 SampledData = 0;
    LED_on(SAMPLE);
    ADC_Wakeup();
    
    /* ADC */
    SampledData = ADC_Read16(); /* Function Starts, Converts, Stops, and Returns from ADC */
    
    /* EEP */
    Em_EEPROM_Write((uint8*) (&SampledData),TailPtr,2u);
    
    TailPtr = TailPtr + 2;
    ADC_Sleep();
    LED_off(SAMPLE);
    
    return;    
}
    
/* [] END OF FILE */
