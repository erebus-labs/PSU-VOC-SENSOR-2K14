/*******************************************************************************
* File Name: Sensor_In.c  
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
#include "Sensor_In.h"


/*******************************************************************************
* Function Name: Sensor_In_Write
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
void Sensor_In_Write(uint8 value) 
{
    uint8 staticBits = (Sensor_In_DR & (uint8)(~Sensor_In_MASK));
    Sensor_In_DR = staticBits | ((uint8)(value << Sensor_In_SHIFT) & Sensor_In_MASK);
}


/*******************************************************************************
* Function Name: Sensor_In_SetDriveMode
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
void Sensor_In_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Sensor_In_0, mode);
}


/*******************************************************************************
* Function Name: Sensor_In_Read
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
*  Macro Sensor_In_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Sensor_In_Read(void) 
{
    return (Sensor_In_PS & Sensor_In_MASK) >> Sensor_In_SHIFT;
}


/*******************************************************************************
* Function Name: Sensor_In_ReadDataReg
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
uint8 Sensor_In_ReadDataReg(void) 
{
    return (Sensor_In_DR & Sensor_In_MASK) >> Sensor_In_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Sensor_In_INTSTAT) 

    /*******************************************************************************
    * Function Name: Sensor_In_ClearInterrupt
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
    uint8 Sensor_In_ClearInterrupt(void) 
    {
        return (Sensor_In_INTSTAT & Sensor_In_MASK) >> Sensor_In_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
