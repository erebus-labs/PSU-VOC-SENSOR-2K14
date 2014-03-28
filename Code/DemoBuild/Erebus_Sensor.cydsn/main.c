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



const uint8 CYCODE MemoryLocation[EmEEPROMSize]; // Errors caused by the include of main.h which includes the externs and static
volatile uint8* TailPtr = (uint8*) MemoryLocation;

void main()
{
    /* Initialization*/
    uint16 blink_rate = 0;
    
    // Variable declarations

    
    // Enable and start EEPROM
    EEPROM_R_Start();
         
    // Enable global interrupts
    CyGlobalIntEnable;
    Vbus_IRQ_Start();
    TakeSample_IRQ_Start();
    
//    Blink_Timer_WritePeriod(CYDEV_EE_BASE[EEPROM_Address.blink_rate]);
    
    // Start LED Blinking
    
    Blink_Timer_Start();  
    blink_rate = get_variable(BLINK_RATE);
    Blink_Timer_WritePeriod(blink_rate);
    
    for(;;)
    {
 
    }
    
    return;
}

/* [] END OF FILE */
