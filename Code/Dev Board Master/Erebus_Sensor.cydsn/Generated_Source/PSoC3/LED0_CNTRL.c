/*******************************************************************************
* File Name: LED0_CNTRL.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "LED0_CNTRL.h"

#if !defined(LED0_CNTRL_Sync_ctrl_reg__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
* Function Name: LED0_CNTRL_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void LED0_CNTRL_Write(uint8 control) 
{
    LED0_CNTRL_Control = control;
}


/*******************************************************************************
* Function Name: LED0_CNTRL_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 LED0_CNTRL_Read(void) 
{
    return LED0_CNTRL_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
