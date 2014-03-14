/*******************************************************************************
* File: main.c
*
* Version: 1.10
*
* Description:
*  The example project demonstrates the basic functionality of the Emulated
*  EEPROM component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>


int main()
{
    static const uint8 CYCODE eepromArray[]= /********** Are these memory locations? ****/
                                { 0x46, 0x69, 0x72, 0x73, 0x74, 0x20, 0x72, 0x75, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00 };
                                             /* F     i     r     s     t           r     u     n     */
    uint8 array[]              ={ 0x50, 0x6F, 0x77, 0x65, 0x72, 0x43, 0x79, 0x63, 0x6C, 0x65, 0x23, 0x20, 0x30, 0x00 };
                                /* P     o     w     e     r     C     y     c     l     e     #           0*/


    uint8 eeprom_cnt;
    cystatus status;
    volatile const uint8 * ptr;

    LCD_Start();
    Em_EEPROM_Start();
    LCD_ClearDisplay();
    
    LCD_PrintString("Em EEPROM demo");
    
    /* If the string in ROM begins with "F", replace it, otherwise increment counter  */
    if (*(volatile uint8 *) &eepromArray[0] == 0x46u)
    {
        LCD_Position(1u,0u);
        LCD_PrintString((char *)eepromArray);
        status = Em_EEPROM_Write(array,eepromArray,14u);
        if (CYRET_SUCCESS != status)
        {
            LCD_ClearDisplay();
            LCD_PrintString("Em EEPROM error");
            while (1u == 1u)
            {
                /* Will stay here */
            }
        }
    }
    else
    {
        ptr = &eepromArray[12];
        eeprom_cnt = *ptr;
        eeprom_cnt++;
        
        if(eeprom_cnt > 0x39u)
        {
            eeprom_cnt = 0x30u;
        }
        
        status = Em_EEPROM_Write(&eeprom_cnt,&eepromArray[12],1u);
        
        LCD_Position(1u,0u);
        LCD_PrintString((char *)eepromArray);
        
        if (CYRET_SUCCESS != status)
        {
            LCD_ClearDisplay();
            LCD_PrintString("Em EEPROM error");
            while (1u == 1u)
            {
                /* Will stay here */
            }
        }
    }
    
    while (1u == 1u)
    {
        /* Forever loop */
    }
}

/* [] END OF FILE */
