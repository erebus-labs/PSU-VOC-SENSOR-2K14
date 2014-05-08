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


void take_sample()
{
    uint16 SampledData = 0;
    ADC_Wakeup();
    
    /* ADC */
    SampledData = ADC_Read16(); /* Function Starts, Converts, Stops, and Returns from ADC */
    
    /* EEP */
    Em_EEPROM_Write((uint8*) (&SampledData),TailPtr,2u);
    
    TailPtr = TailPtr + 2;
    ADC_Sleep();
    return;    
}
    
/* [] END OF FILE */
