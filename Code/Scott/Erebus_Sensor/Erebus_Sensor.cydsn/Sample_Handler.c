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
    
    /* Get sample from ADC */
    SampledData = ADC_Read16(); /* Function Starts, Converts, Stops, and Returns from ADC */
    
    /* Write sample value to Emulated EEPROM */
    Em_EEPROM_Write((uint8*) &SampledData, &(sample_block[sample_tail_index]), SAMPLE_SIZE);
       
    sample_tail_index = sample_tail_index + SAMPLE_SIZE;
    /* Check to make sure we're not incrementing the tail pointer past
     * the bounds of our sample array */
    if(sample_tail_index >= SAMPLE_BLOCK_SIZE){
        sample_tail_index = 0;
    }
    
    /* Check to make sure we aren't about to start overwriting existing data */
    if (sample_tail_index == sample_head_index){
        memory_full();
        goto exit;
    }
      
    /* Store incremented tail pointer back in Emulated EEPROM */
    Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[pointer_tail_index]), sizeof(uint16));

exit:
    
    ADC_Sleep();
    return;    
}



    
/* [] END OF FILE */
