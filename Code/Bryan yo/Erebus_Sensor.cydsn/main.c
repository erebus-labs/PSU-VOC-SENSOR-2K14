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
#include "Sample_Handler.h"
#include "RTC_1.h"


const uint8 CYCODE MemoryLocation[EmEEPROMSize]; // Errors caused by the include of main.h which includes the externs and static
volatile uint8* TailPtr = (uint8*) MemoryLocation;

void main()
{
    /* Initialization*/
    uint16 blink_rate = 0;
    
    
    // Variable declarations

    
    // Start RTC and associated functions
    RTC_1_Start();
    RTC_1_EnableInt();
    RTC_1_Enable();
    
    // Enable and start EEPROM
    EEPROM_R_Start();
         
    // Enable global interrupts
    CyGlobalIntEnable;
    Vbus_IRQ_Start();
    //TakeSample_IRQ_Start();
    
//    Blink_Timer_WritePeriod(CYDEV_EE_BASE[EEPROM_Address.blink_rate]);
    
    // Start LED Blinking
    
    //Blink_Timer_Start();  
    //blink_rate = get_variable(BLINK_RATE);
    //Blink_Timer_WritePeriod(blink_rate);
    
    
    rtc_prep();
    

    while(1u)
    {
        
        CyDelay(100);
        
        CyPmSaveClocks();
        
        RTC_1_DisableInt();
        
        CyPmSleep(PM_SLEEP_TIME_NONE,PM_SLEEP_SRC_ONE_PPS);
        
        CyPmRestoreClocks(); 
        
        RTC_1_EnableInt();
        
    }
    
    return;
}

/* [] END OF FILE */
