/*******************************************************************************
* File Name: USBUART_1_Vbus_ps.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_1_Vbus_ps.h"

#if !defined(USBUART_1_Vbus_ps_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: USBUART_1_Vbus_ps_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 USBUART_1_Vbus_ps_Read(void) 
{ 
    return USBUART_1_Vbus_ps_Status;
}


/*******************************************************************************
* Function Name: USBUART_1_Vbus_ps_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void USBUART_1_Vbus_ps_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    USBUART_1_Vbus_ps_Status_Aux_Ctrl |= USBUART_1_Vbus_ps_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: USBUART_1_Vbus_ps_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void USBUART_1_Vbus_ps_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    USBUART_1_Vbus_ps_Status_Aux_Ctrl &= (uint8)(~USBUART_1_Vbus_ps_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: USBUART_1_Vbus_ps_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void USBUART_1_Vbus_ps_WriteMask(uint8 mask) 
{
    #if(USBUART_1_Vbus_ps_INPUTS < 8u)
    	mask &= (uint8)((((uint8)1u) << USBUART_1_Vbus_ps_INPUTS) - 1u);
	#endif /* End USBUART_1_Vbus_ps_INPUTS < 8u */
    USBUART_1_Vbus_ps_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: USBUART_1_Vbus_ps_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 USBUART_1_Vbus_ps_ReadMask(void) 
{
    return USBUART_1_Vbus_ps_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
