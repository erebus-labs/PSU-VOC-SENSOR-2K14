/*******************************************************************************
* File Name: EEPROM_Blink_TI_PM.c
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

#include "EEPROM_Blink_TI.h"
static EEPROM_Blink_TI_backupStruct EEPROM_Blink_TI_backup;


/*******************************************************************************
* Function Name: EEPROM_Blink_TI_SaveConfig
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
*  EEPROM_Blink_TI_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EEPROM_Blink_TI_SaveConfig(void) 
{
    #if (!EEPROM_Blink_TI_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            EEPROM_Blink_TI_backup.TimerUdb = EEPROM_Blink_TI_ReadCounter();
            EEPROM_Blink_TI_backup.TimerPeriod = EEPROM_Blink_TI_ReadPeriod();
            EEPROM_Blink_TI_backup.InterruptMaskValue = EEPROM_Blink_TI_STATUS_MASK;
            #if (EEPROM_Blink_TI_UsingHWCaptureCounter)
                EEPROM_Blink_TI_backup.TimerCaptureCounter = EEPROM_Blink_TI_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            EEPROM_Blink_TI_backup.TimerUdb = EEPROM_Blink_TI_ReadCounter();
            EEPROM_Blink_TI_backup.InterruptMaskValue = EEPROM_Blink_TI_STATUS_MASK;
            #if (EEPROM_Blink_TI_UsingHWCaptureCounter)
                EEPROM_Blink_TI_backup.TimerCaptureCounter = EEPROM_Blink_TI_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!EEPROM_Blink_TI_ControlRegRemoved)
            EEPROM_Blink_TI_backup.TimerControlRegister = EEPROM_Blink_TI_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: EEPROM_Blink_TI_RestoreConfig
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
*  EEPROM_Blink_TI_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EEPROM_Blink_TI_RestoreConfig(void) 
{   
    #if (!EEPROM_Blink_TI_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 EEPROM_Blink_TI_interruptState;

            EEPROM_Blink_TI_WriteCounter(EEPROM_Blink_TI_backup.TimerUdb);
            EEPROM_Blink_TI_WritePeriod(EEPROM_Blink_TI_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            EEPROM_Blink_TI_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            EEPROM_Blink_TI_STATUS_AUX_CTRL |= EEPROM_Blink_TI_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(EEPROM_Blink_TI_interruptState);
            EEPROM_Blink_TI_STATUS_MASK =EEPROM_Blink_TI_backup.InterruptMaskValue;
            #if (EEPROM_Blink_TI_UsingHWCaptureCounter)
                EEPROM_Blink_TI_SetCaptureCount(EEPROM_Blink_TI_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            EEPROM_Blink_TI_WriteCounter(EEPROM_Blink_TI_backup.TimerUdb);
            EEPROM_Blink_TI_STATUS_MASK =EEPROM_Blink_TI_backup.InterruptMaskValue;
            #if (EEPROM_Blink_TI_UsingHWCaptureCounter)
                EEPROM_Blink_TI_SetCaptureCount(EEPROM_Blink_TI_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!EEPROM_Blink_TI_ControlRegRemoved)
            EEPROM_Blink_TI_WriteControlRegister(EEPROM_Blink_TI_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: EEPROM_Blink_TI_Sleep
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
*  EEPROM_Blink_TI_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void EEPROM_Blink_TI_Sleep(void) 
{
    #if(!EEPROM_Blink_TI_ControlRegRemoved)
        /* Save Counter's enable state */
        if(EEPROM_Blink_TI_CTRL_ENABLE == (EEPROM_Blink_TI_CONTROL & EEPROM_Blink_TI_CTRL_ENABLE))
        {
            /* Timer is enabled */
            EEPROM_Blink_TI_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            EEPROM_Blink_TI_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    EEPROM_Blink_TI_Stop();
    EEPROM_Blink_TI_SaveConfig();
}


/*******************************************************************************
* Function Name: EEPROM_Blink_TI_Wakeup
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
*  EEPROM_Blink_TI_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EEPROM_Blink_TI_Wakeup(void) 
{
    EEPROM_Blink_TI_RestoreConfig();
    #if(!EEPROM_Blink_TI_ControlRegRemoved)
        if(EEPROM_Blink_TI_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                EEPROM_Blink_TI_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
