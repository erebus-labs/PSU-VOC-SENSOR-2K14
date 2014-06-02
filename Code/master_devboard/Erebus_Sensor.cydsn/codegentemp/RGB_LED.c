/*******************************************************************************
* File Name: RGB_LED.c  
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
#include "RGB_LED.h"


/*******************************************************************************
* Function Name: RGB_LED_Write
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
void RGB_LED_Write(uint8 value) 
{
    uint8 staticBits = (RGB_LED_DR & (uint8)(~RGB_LED_MASK));
    RGB_LED_DR = staticBits | ((uint8)(value << RGB_LED_SHIFT) & RGB_LED_MASK);
}


/*******************************************************************************
* Function Name: RGB_LED_SetDriveMode
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
void RGB_LED_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RGB_LED_0, mode);
	CyPins_SetPinDriveMode(RGB_LED_1, mode);
	CyPins_SetPinDriveMode(RGB_LED_2, mode);
}


/*******************************************************************************
* Function Name: RGB_LED_Read
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
*  Macro RGB_LED_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RGB_LED_Read(void) 
{
    return (RGB_LED_PS & RGB_LED_MASK) >> RGB_LED_SHIFT;
}


/*******************************************************************************
* Function Name: RGB_LED_ReadDataReg
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
uint8 RGB_LED_ReadDataReg(void) 
{
    return (RGB_LED_DR & RGB_LED_MASK) >> RGB_LED_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RGB_LED_INTSTAT) 

    /*******************************************************************************
    * Function Name: RGB_LED_ClearInterrupt
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
    uint8 RGB_LED_ClearInterrupt(void) 
    {
        return (RGB_LED_INTSTAT & RGB_LED_MASK) >> RGB_LED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
