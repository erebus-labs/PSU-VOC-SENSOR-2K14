/*******************************************************************************
* File Name: USB_LED.c  
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
#include "USB_LED.h"


/*******************************************************************************
* Function Name: USB_LED_Write
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
void USB_LED_Write(uint8 value) 
{
    uint8 staticBits = (USB_LED_DR & (uint8)(~USB_LED_MASK));
    USB_LED_DR = staticBits | ((uint8)(value << USB_LED_SHIFT) & USB_LED_MASK);
}


/*******************************************************************************
* Function Name: USB_LED_SetDriveMode
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
void USB_LED_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(USB_LED_0, mode);
}


/*******************************************************************************
* Function Name: USB_LED_Read
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
*  Macro USB_LED_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 USB_LED_Read(void) 
{
    return (USB_LED_PS & USB_LED_MASK) >> USB_LED_SHIFT;
}


/*******************************************************************************
* Function Name: USB_LED_ReadDataReg
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
uint8 USB_LED_ReadDataReg(void) 
{
    return (USB_LED_DR & USB_LED_MASK) >> USB_LED_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(USB_LED_INTSTAT) 

    /*******************************************************************************
    * Function Name: USB_LED_ClearInterrupt
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
    uint8 USB_LED_ClearInterrupt(void) 
    {
        return (USB_LED_INTSTAT & USB_LED_MASK) >> USB_LED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
