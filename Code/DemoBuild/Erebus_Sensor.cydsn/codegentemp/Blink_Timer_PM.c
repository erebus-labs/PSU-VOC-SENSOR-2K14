/*******************************************************************************
* File Name: Blink_Timer_PM.c
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

#include "Blink_Timer.h"
static Blink_Timer_backupStruct Blink_Timer_backup;


/*******************************************************************************
* Function Name: Blink_Timer_SaveConfig
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
*  Blink_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Blink_Timer_SaveConfig(void) 
{
    #if (!Blink_Timer_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            Blink_Timer_backup.TimerUdb = Blink_Timer_ReadCounter();
            Blink_Timer_backup.TimerPeriod = Blink_Timer_ReadPeriod();
            Blink_Timer_backup.InterruptMaskValue = Blink_Timer_STATUS_MASK;
            #if (Blink_Timer_UsingHWCaptureCounter)
                Blink_Timer_backup.TimerCaptureCounter = Blink_Timer_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Blink_Timer_backup.TimerUdb = Blink_Timer_ReadCounter();
            Blink_Timer_backup.InterruptMaskValue = Blink_Timer_STATUS_MASK;
            #if (Blink_Timer_UsingHWCaptureCounter)
                Blink_Timer_backup.TimerCaptureCounter = Blink_Timer_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Blink_Timer_ControlRegRemoved)
            Blink_Timer_backup.TimerControlRegister = Blink_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Blink_Timer_RestoreConfig
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
*  Blink_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Blink_Timer_RestoreConfig(void) 
{   
    #if (!Blink_Timer_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 Blink_Timer_interruptState;

            Blink_Timer_WriteCounter(Blink_Timer_backup.TimerUdb);
            Blink_Timer_WritePeriod(Blink_Timer_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Blink_Timer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Blink_Timer_STATUS_AUX_CTRL |= Blink_Timer_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Blink_Timer_interruptState);
            Blink_Timer_STATUS_MASK =Blink_Timer_backup.InterruptMaskValue;
            #if (Blink_Timer_UsingHWCaptureCounter)
                Blink_Timer_SetCaptureCount(Blink_Timer_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Blink_Timer_WriteCounter(Blink_Timer_backup.TimerUdb);
            Blink_Timer_STATUS_MASK =Blink_Timer_backup.InterruptMaskValue;
            #if (Blink_Timer_UsingHWCaptureCounter)
                Blink_Timer_SetCaptureCount(Blink_Timer_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Blink_Timer_ControlRegRemoved)
            Blink_Timer_WriteControlRegister(Blink_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Blink_Timer_Sleep
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
*  Blink_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Blink_Timer_Sleep(void) 
{
    #if(!Blink_Timer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Blink_Timer_CTRL_ENABLE == (Blink_Timer_CONTROL & Blink_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Blink_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Blink_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Blink_Timer_Stop();
    Blink_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Blink_Timer_Wakeup
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
*  Blink_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Blink_Timer_Wakeup(void) 
{
    Blink_Timer_RestoreConfig();
    #if(!Blink_Timer_ControlRegRemoved)
        if(Blink_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Blink_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
