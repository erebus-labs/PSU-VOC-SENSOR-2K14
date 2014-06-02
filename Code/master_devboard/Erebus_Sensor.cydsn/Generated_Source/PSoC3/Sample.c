/*******************************************************************************
* File Name: Sample.c  
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
#include "Sample.h"


/*******************************************************************************
* Function Name: Sample_Write
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
void Sample_Write(uint8 value) 
{
    uint8 staticBits = (Sample_DR & (uint8)(~Sample_MASK));
    Sample_DR = staticBits | ((uint8)(value << Sample_SHIFT) & Sample_MASK);
}


/*******************************************************************************
* Function Name: Sample_SetDriveMode
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
void Sample_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Sample_0, mode);
}


/*******************************************************************************
* Function Name: Sample_Read
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
*  Macro Sample_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Sample_Read(void) 
{
    return (Sample_PS & Sample_MASK) >> Sample_SHIFT;
}


/*******************************************************************************
* Function Name: Sample_ReadDataReg
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
uint8 Sample_ReadDataReg(void) 
{
    return (Sample_DR & Sample_MASK) >> Sample_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Sample_INTSTAT) 

    /*******************************************************************************
    * Function Name: Sample_ClearInterrupt
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
    uint8 Sample_ClearInterrupt(void) 
    {
        return (Sample_INTSTAT & Sample_MASK) >> Sample_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
