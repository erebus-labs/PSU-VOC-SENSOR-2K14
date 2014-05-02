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

#include "main.h"

// Flash variables
const uint8 CYCODE MemoryLocation[EmEEPROMSize]; 
const volatile uint8* TailPtr = (uint8*) MemoryLocation;
const uint8 CYCODE hard_reset_flag;

int main()
{
    Flash_Blink_TI_Start();
    /* Initialization*/
    rtc_setup();

    // Check for hard reset flag
    if (hard_reset_flag){
        hard_reset();   
    }

    // Start Components
    EEPROM_R_Start();
    RTC_Start();
    
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable individual interrupts as necessary
    Vbus_IRQ_Start();
    StartCollection_IRQ_Start();
    
    for(;;){}
    
    return (0);
}

/* [] END OF FILE */
