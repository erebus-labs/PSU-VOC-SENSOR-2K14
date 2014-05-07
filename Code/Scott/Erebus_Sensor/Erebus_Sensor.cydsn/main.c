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

/* Globals */

// Flash
const uint8 CYCODE MemoryLocation[EmEEPROMSize]; 
const volatile uint8* TailPtr = (uint8*) MemoryLocation;
const uint8 CYCODE hard_reset_flag;

// Flags
uint8 low_power_flag = 0;

int main()
{
    // Check for hard reset flag
    if (hard_reset_flag){
        hard_reset();   
    }
    /* Initialization*/

    // Start Components
    EEPROM_R_Start();
    LED_PWM_Start();
    ADC_Start();
    ADC_Sleep();
    
    // RTC
    RTC_Start();
    rtc_setup();
    
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable individual interrupts as necessary   
    Vbus_IRQ_Start();
    StartCollection_IRQ_Start();
    
    for(;;){
        
        CyDelay(100);
        
        #ifdef SLEEP_EN            
        CyPmSaveClocks();        
        
        RTC_DisableInt();
        
        CyPmSleep(PM_SLEEP_TIME_NONE,PM_SLEEP_SRC_ONE_PPS);     
        CyPmRestoreClocks(); 

        
        RTC_EnableInt();
        #endif
    }
    
    return (0);
}

/* [] END OF FILE */
