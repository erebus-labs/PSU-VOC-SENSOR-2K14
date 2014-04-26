/*******************************************************************************
* File Name: TakeSample_B.c  
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
#include "TakeSample_B.h"


/*******************************************************************************
* Function Name: TakeSample_B_Write
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
void TakeSample_B_Write(uint8 value) 
{
    uint8 staticBits = (TakeSample_B_DR & (uint8)(~TakeSample_B_MASK));
    TakeSample_B_DR = staticBits | ((uint8)(value << TakeSample_B_SHIFT) & TakeSample_B_MASK);
}


/*******************************************************************************
* Function Name: TakeSample_B_SetDriveMode
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
void TakeSample_B_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TakeSample_B_0, mode);
}


/*******************************************************************************
* Function Name: TakeSample_B_Read
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
*  Macro TakeSample_B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TakeSample_B_Read(void) 
{
    return (TakeSample_B_PS & TakeSample_B_MASK) >> TakeSample_B_SHIFT;
}


/*******************************************************************************
* Function Name: TakeSample_B_ReadDataReg
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
uint8 TakeSample_B_ReadDataReg(void) 
{
    return (TakeSample_B_DR & TakeSample_B_MASK) >> TakeSample_B_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TakeSample_B_INTSTAT) 

    /*******************************************************************************
    * Function Name: TakeSample_B_ClearInterrupt
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
    uint8 TakeSample_B_ClearInterrupt(void) 
    {
        return (TakeSample_B_INTSTAT & TakeSample_B_MASK) >> TakeSample_B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
