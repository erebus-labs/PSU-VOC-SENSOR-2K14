/*******************************************************************************
* File Name: V_bus.c  
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
#include "V_bus.h"


/*******************************************************************************
* Function Name: V_bus_Write
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
void V_bus_Write(uint8 value) 
{
    uint8 staticBits = (V_bus_DR & (uint8)(~V_bus_MASK));
    V_bus_DR = staticBits | ((uint8)(value << V_bus_SHIFT) & V_bus_MASK);
}


/*******************************************************************************
* Function Name: V_bus_SetDriveMode
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
void V_bus_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(V_bus_0, mode);
}


/*******************************************************************************
* Function Name: V_bus_Read
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
*  Macro V_bus_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 V_bus_Read(void) 
{
    return (V_bus_PS & V_bus_MASK) >> V_bus_SHIFT;
}


/*******************************************************************************
* Function Name: V_bus_ReadDataReg
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
uint8 V_bus_ReadDataReg(void) 
{
    return (V_bus_DR & V_bus_MASK) >> V_bus_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(V_bus_INTSTAT) 

    /*******************************************************************************
    * Function Name: V_bus_ClearInterrupt
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
    uint8 V_bus_ClearInterrupt(void) 
    {
        return (V_bus_INTSTAT & V_bus_MASK) >> V_bus_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
