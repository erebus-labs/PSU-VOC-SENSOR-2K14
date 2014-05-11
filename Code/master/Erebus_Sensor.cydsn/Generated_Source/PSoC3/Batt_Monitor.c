/*******************************************************************************
* File Name: Batt_Monitor.c  
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
#include "Batt_Monitor.h"


/*******************************************************************************
* Function Name: Batt_Monitor_Write
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
void Batt_Monitor_Write(uint8 value) 
{
    uint8 staticBits = (Batt_Monitor_DR & (uint8)(~Batt_Monitor_MASK));
    Batt_Monitor_DR = staticBits | ((uint8)(value << Batt_Monitor_SHIFT) & Batt_Monitor_MASK);
}


/*******************************************************************************
* Function Name: Batt_Monitor_SetDriveMode
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
void Batt_Monitor_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Batt_Monitor_0, mode);
}


/*******************************************************************************
* Function Name: Batt_Monitor_Read
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
*  Macro Batt_Monitor_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Batt_Monitor_Read(void) 
{
    return (Batt_Monitor_PS & Batt_Monitor_MASK) >> Batt_Monitor_SHIFT;
}


/*******************************************************************************
* Function Name: Batt_Monitor_ReadDataReg
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
uint8 Batt_Monitor_ReadDataReg(void) 
{
    return (Batt_Monitor_DR & Batt_Monitor_MASK) >> Batt_Monitor_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Batt_Monitor_INTSTAT) 

    /*******************************************************************************
    * Function Name: Batt_Monitor_ClearInterrupt
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
    uint8 Batt_Monitor_ClearInterrupt(void) 
    {
        return (Batt_Monitor_INTSTAT & Batt_Monitor_MASK) >> Batt_Monitor_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
