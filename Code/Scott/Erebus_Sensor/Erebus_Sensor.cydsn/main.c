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

// Globals
uint16 delay = 500;

    
void main()
{
    /* Initialization*/
    
    // Variable declarations

    
    // Enable and start EEPROM
 //   EEPROM_Real_Enable();
 //   EEPROM_Real_Start();
    
    // Enable global interrupts
    CyGlobalIntEnable;
    Vbus_IRQ_Start();
    
    // Start LED Blinking
    Blink_Timer_Start();   

    for(;;)
    {
 
    }
}

/* [] END OF FILE */
