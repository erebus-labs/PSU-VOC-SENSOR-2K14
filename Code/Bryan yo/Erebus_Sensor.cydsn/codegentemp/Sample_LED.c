/*******************************************************************************
* File Name: Sample_LED.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Sample_LED.h"


/*******************************************************************************
* Function Name: Sample_LED_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Sample_LED_Write(uint8 value) 
{
    uint8 staticBits = (Sample_LED_DR & (uint8)(~Sample_LED_MASK));
    Sample_LED_DR = staticBits | ((uint8)(value << Sample_LED_SHIFT) & Sample_LED_MASK);
}


/*******************************************************************************
* Function Name: Sample_LED_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void Sample_LED_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Sample_LED_0, mode);
}


/*******************************************************************************
* Function Name: Sample_LED_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Sample_LED_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Sample_LED_Read(void) 
{
    return (Sample_LED_PS & Sample_LED_MASK) >> Sample_LED_SHIFT;
}


/*******************************************************************************
* Function Name: Sample_LED_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Sample_LED_ReadDataReg(void) 
{
    return (Sample_LED_DR & Sample_LED_MASK) >> Sample_LED_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Sample_LED_INTSTAT) 

    /*******************************************************************************
    * Function Name: Sample_LED_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Sample_LED_ClearInterrupt(void) 
    {
        return (Sample_LED_INTSTAT & Sample_LED_MASK) >> Sample_LED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
