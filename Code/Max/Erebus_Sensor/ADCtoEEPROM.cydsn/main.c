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
#include <project.h>
#define EmEEPROMSize 1024 
static const uint8 CYCODE MemoryLocation[EmEEPROMSize];
volatile const uint8 * TailPtr = MemoryLocation;


int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Em_EEPROM_Start();
    ADC_Start();
    
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    TakeSample_IRQ_Start();
    for(;;)
    {
        
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
