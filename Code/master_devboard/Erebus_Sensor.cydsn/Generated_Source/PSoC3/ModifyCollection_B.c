/*******************************************************************************
* File Name: ModifyCollection_B.c  
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
#include "ModifyCollection_B.h"


/*******************************************************************************
* Function Name: ModifyCollection_B_Write
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
void ModifyCollection_B_Write(uint8 value) 
{
    uint8 staticBits = (ModifyCollection_B_DR & (uint8)(~ModifyCollection_B_MASK));
    ModifyCollection_B_DR = staticBits | ((uint8)(value << ModifyCollection_B_SHIFT) & ModifyCollection_B_MASK);
}


/*******************************************************************************
* Function Name: ModifyCollection_B_SetDriveMode
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
void ModifyCollection_B_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ModifyCollection_B_0, mode);
	CyPins_SetPinDriveMode(ModifyCollection_B_1, mode);
}


/*******************************************************************************
* Function Name: ModifyCollection_B_Read
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
*  Macro ModifyCollection_B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ModifyCollection_B_Read(void) 
{
    return (ModifyCollection_B_PS & ModifyCollection_B_MASK) >> ModifyCollection_B_SHIFT;
}


/*******************************************************************************
* Function Name: ModifyCollection_B_ReadDataReg
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
uint8 ModifyCollection_B_ReadDataReg(void) 
{
    return (ModifyCollection_B_DR & ModifyCollection_B_MASK) >> ModifyCollection_B_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ModifyCollection_B_INTSTAT) 

    /*******************************************************************************
    * Function Name: ModifyCollection_B_ClearInterrupt
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
    uint8 ModifyCollection_B_ClearInterrupt(void) 
    {
        return (ModifyCollection_B_INTSTAT & ModifyCollection_B_MASK) >> ModifyCollection_B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
