/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This is a source code for Erase and Write funtionality of EEPROM component.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>
#include <project.h>


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
* Main function performs the following functions:
*  1: Start the EEPROM (Only for CY_PSOC3 or later)
*  2: Initializes the LCD
*  3: Print data written to eeprom memory in LCD
*  4: Print result of test in LCD
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void main()
{
    uint16 Index;
    reg8 * RegPointer;
    int err = 0u;
    cystatus eraseStatus;
    cystatus writeStatus;
    uint8 TestData1[SIZEOF_EEPROM_ROW] = {1u, 2u, 2u, 4u, 5u, 1u, 2u, 3u, 4u, 6u, 9u, 2u, 5u, 4u, 5u, 4u};

    /* Prepare components */
    #if (CY_PSOC3 || CY_PSOC5LP) 
        EEPROM_Start();
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    CharLCD_1_Start();
    eraseStatus = 0xff;
    writeStatus = 0xff;

    /* Erase all sectors. */
    for(Index = 0u; Index < CY_EEPROM_NUMBER_ARRAYS; Index++)
    {
        eraseStatus = EEPROM_EraseSector(Index);
    }

    /* Check that all EEPROM is zero */
    RegPointer = (reg8 *)CYDEV_EE_BASE;
    for(Index = 0u; Index < EEPROM_EEPROM_SIZE; Index++)
    {
        if(RegPointer[Index] != 0u)
        {
            CharLCD_1_Position(1u, 0u);
            CharLCD_1_PrintString("ERASE FAILED");
            err ++;
        }
    }

    /* Get the die temp. */
    if(CySetTemp() == CYRET_SUCCESS)
    {
        /* Write TestData1 to EEPROM row 0 */
        writeStatus = EEPROM_Write(TestData1, 0u);
    }

    /* Check Data */
    RegPointer = (reg8 *) CYDEV_EE_BASE;
    for(Index = 0u; Index < SIZEOF_EEPROM_ROW; Index++)
    {
        if(TestData1[Index] != RegPointer[Index])
        {
            CharLCD_1_Position(1u, 0u);
            CharLCD_1_PrintString("WRITE FAILED");
            err ++;
        }
        CharLCD_1_Position(0u, 0u);
        CharLCD_1_PrintInt8(RegPointer[Index]);
        CyDelay(500u);
    }

    if(eraseStatus == CYRET_SUCCESS && writeStatus == CYRET_SUCCESS && err == 0u)
    {
        CharLCD_1_Position(1u, 0u);
        CharLCD_1_PrintString("EEPROM TEST PASSED");
    }
    else
    {
        CharLCD_1_Position(1u, 0u);
        CharLCD_1_PrintString("EEPROM TEST FAILED");
    }

    for(;;)
    {
    }
}


/* [] END OF FILE */
