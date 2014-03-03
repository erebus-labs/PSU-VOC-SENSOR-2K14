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
    char8 buffer[BUFFER_LEN] = {0};
    char8* ptr = buffer;
    uint8 count = 0;
    
    // Enable and start EEPROM
 //   EEPROM_Real_Enable();
 //   EEPROM_Real_Start();
    
    // Enable global interrupts
    CyGlobalIntEnable;
    Timer_1_Start();   
    // Start USB
    USBUART_1_Start(0u, USBUART_1_3V_OPERATION);
    /* Wait for Device to enumerate */
    while(!USBUART_1_GetConfiguration());
    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_1_CDC_Init();
    
    
    for(;;)
    {
        if(USBUART_1_DataIsReady() != 0u)               /* Check for input data from PC */
        {   
            do
            {
                *ptr = USBUART_1_GetChar();           /* Read received data and re-enable OUT endpoint */
                ++ptr;
                ++count;
            }while (buffer[count-1] != '\n' && count < BUFFER_LEN);
            
            buffer[count] = '\0';
            delay = (uint16) atoi(buffer);
            count = 0;
            ptr = buffer;
            Timer_1_WritePeriod(delay);
        }
        
        
        
        
    }
}

/* [] END OF FILE */
