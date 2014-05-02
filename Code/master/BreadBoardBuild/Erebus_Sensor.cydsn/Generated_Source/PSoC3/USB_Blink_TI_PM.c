/*******************************************************************************
* File Name: USB_Blink_TI_PM.c
* Version 2.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "USB_Blink_TI.h"
static USB_Blink_TI_backupStruct USB_Blink_TI_backup;


/*******************************************************************************
* Function Name: USB_Blink_TI_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  USB_Blink_TI_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void USB_Blink_TI_SaveConfig(void) 
{
    #if (!USB_Blink_TI_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            USB_Blink_TI_backup.TimerUdb = USB_Blink_TI_ReadCounter();
            USB_Blink_TI_backup.TimerPeriod = USB_Blink_TI_ReadPeriod();
            USB_Blink_TI_backup.InterruptMaskValue = USB_Blink_TI_STATUS_MASK;
            #if (USB_Blink_TI_UsingHWCaptureCounter)
                USB_Blink_TI_backup.TimerCaptureCounter = USB_Blink_TI_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            USB_Blink_TI_backup.TimerUdb = USB_Blink_TI_ReadCounter();
            USB_Blink_TI_backup.InterruptMaskValue = USB_Blink_TI_STATUS_MASK;
            #if (USB_Blink_TI_UsingHWCaptureCounter)
                USB_Blink_TI_backup.TimerCaptureCounter = USB_Blink_TI_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!USB_Blink_TI_ControlRegRemoved)
            USB_Blink_TI_backup.TimerControlRegister = USB_Blink_TI_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: USB_Blink_TI_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  USB_Blink_TI_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void USB_Blink_TI_RestoreConfig(void) 
{   
    #if (!USB_Blink_TI_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 USB_Blink_TI_interruptState;

            USB_Blink_TI_WriteCounter(USB_Blink_TI_backup.TimerUdb);
            USB_Blink_TI_WritePeriod(USB_Blink_TI_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            USB_Blink_TI_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            USB_Blink_TI_STATUS_AUX_CTRL |= USB_Blink_TI_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(USB_Blink_TI_interruptState);
            USB_Blink_TI_STATUS_MASK =USB_Blink_TI_backup.InterruptMaskValue;
            #if (USB_Blink_TI_UsingHWCaptureCounter)
                USB_Blink_TI_SetCaptureCount(USB_Blink_TI_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            USB_Blink_TI_WriteCounter(USB_Blink_TI_backup.TimerUdb);
            USB_Blink_TI_STATUS_MASK =USB_Blink_TI_backup.InterruptMaskValue;
            #if (USB_Blink_TI_UsingHWCaptureCounter)
                USB_Blink_TI_SetCaptureCount(USB_Blink_TI_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!USB_Blink_TI_ControlRegRemoved)
            USB_Blink_TI_WriteControlRegister(USB_Blink_TI_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: USB_Blink_TI_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  USB_Blink_TI_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void USB_Blink_TI_Sleep(void) 
{
    #if(!USB_Blink_TI_ControlRegRemoved)
        /* Save Counter's enable state */
        if(USB_Blink_TI_CTRL_ENABLE == (USB_Blink_TI_CONTROL & USB_Blink_TI_CTRL_ENABLE))
        {
            /* Timer is enabled */
            USB_Blink_TI_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            USB_Blink_TI_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    USB_Blink_TI_Stop();
    USB_Blink_TI_SaveConfig();
}


/*******************************************************************************
* Function Name: USB_Blink_TI_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  USB_Blink_TI_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void USB_Blink_TI_Wakeup(void) 
{
    USB_Blink_TI_RestoreConfig();
    #if(!USB_Blink_TI_ControlRegRemoved)
        if(USB_Blink_TI_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                USB_Blink_TI_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
