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


void main()
{
    /* Initialization*/
    
    // Variable declarations

    
    // Enable and start EEPROM
    EEPROM_R_Start();
    
    // Enable global interrupts
    CyGlobalIntEnable;
    Vbus_IRQ_Start();
    
//    Blink_Timer_WritePeriod(CYDEV_EE_BASE[EEPROM_Address.blink_rate]);
    
    // Start LED Blinking
    Blink_Timer_Start();   

    for(;;)
    {
 
    }
    
    return;
}

/* [] END OF FILE */
