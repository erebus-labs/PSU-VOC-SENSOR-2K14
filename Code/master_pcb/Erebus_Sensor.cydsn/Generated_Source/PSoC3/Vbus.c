/*******************************************************************************
* File Name: Vbus.c  
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
#include "Vbus.h"


/*******************************************************************************
* Function Name: Vbus_Write
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
void Vbus_Write(uint8 value) 
{
    uint8 staticBits = (Vbus_DR & (uint8)(~Vbus_MASK));
    Vbus_DR = staticBits | ((uint8)(value << Vbus_SHIFT) & Vbus_MASK);
}


/*******************************************************************************
* Function Name: Vbus_SetDriveMode
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
void Vbus_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Vbus_0, mode);
}


/*******************************************************************************
* Function Name: Vbus_Read
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
*  Macro Vbus_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Vbus_Read(void) 
{
    return (Vbus_PS & Vbus_MASK) >> Vbus_SHIFT;
}


/*******************************************************************************
* Function Name: Vbus_ReadDataReg
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
uint8 Vbus_ReadDataReg(void) 
{
    return (Vbus_DR & Vbus_MASK) >> Vbus_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Vbus_INTSTAT) 

    /*******************************************************************************
    * Function Name: Vbus_ClearInterrupt
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
    uint8 Vbus_ClearInterrupt(void) 
    {
        return (Vbus_INTSTAT & Vbus_MASK) >> Vbus_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
