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
#include <stdlib.h>
#include "main.h"

const uint8 CYCODE MemoryLocation[EmEEPROMSize]; 
volatile uint8* TailPtr = (uint8*) MemoryLocation;

int main()
{
    /* Initialization*/
    
    // Variable declarations

    // Enable and start EEPROM
    EEPROM_R_Start();
    
    // When sleep functions are implemented, use the following calls to retrieve EEPROM vars:
    // sample_unit = get_variable(EE_SAMPLE_UNIT);
    // sample_interval = get_variable(EE_SAMPLE_INTERVAL);
         
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable individual interrupts as necessary
    Vbus_IRQ_Start();
    TakeSample_IRQ_Start();
    
    for(;;){}
    
    return (0);
}

/* [] END OF FILE */
