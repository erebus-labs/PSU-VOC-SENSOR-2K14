/*******************************************************************************
* File Name: USB_UART_pm.c
* Version 2.60
*
* Description:
*  This file provides Suspend/Resume APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "project.h"
#include "USB_UART.h"
#include "USB_UART_pvt.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static USB_UART_BACKUP_STRUCT  USB_UART_backup;


#if(USB_UART_DP_ISR_REMOVE == 0u)


    /*******************************************************************************
    * Function Name: USB_UART_DP_Interrupt
    ********************************************************************************
    *
    * Summary:
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_UART_DP_ISR)
    {
        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        /* Clears active interrupt */
        CY_GET_REG8(USB_UART_DP_INTSTAT_PTR);
    }

#endif /* (USB_UART_DP_ISR_REMOVE == 0u) */


/*******************************************************************************
* Function Name: USB_UART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: USB_UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_RestoreConfig(void) 
{
    if(USB_UART_configuration != 0u)
    {
        USB_UART_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: USB_UART_Suspend
********************************************************************************
*
* Summary:
*  This function disables the USBFS block and prepares for power donwn mode.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*  USB_UART_backup.enable:  modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_Suspend(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if((CY_GET_REG8(USB_UART_CR0_PTR) & USB_UART_CR0_ENABLE) != 0u)
    {   /* USB block is enabled */
        USB_UART_backup.enableState = 1u;

        #if(USB_UART_EP_MM != USB_UART__EP_MANUAL)
            USB_UART_Stop_DMA(USB_UART_MAX_EP);     /* Stop all DMAs */
        #endif   /* End USB_UART_EP_MM != USB_UART__EP_MANUAL */

        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        USB_UART_USBIO_CR0_REG &= (uint8)~USB_UART_USBIO_CR0_TEN;
        CyDelayUs(0u);  /*~50ns delay */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        USB_UART_PM_USB_CR0_REG &=
                                (uint8)~(USB_UART_PM_USB_CR0_PD_N | USB_UART_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE */
        USB_UART_CR0_REG &= (uint8)~USB_UART_CR0_ENABLE;

        CyDelayUs(0u);  /*~50ns delay */
        /* Store mode and Disable VRegulator*/
        USB_UART_backup.mode = USB_UART_CR1_REG & USB_UART_CR1_REG_ENABLE;
        USB_UART_CR1_REG &= (uint8)~USB_UART_CR1_REG_ENABLE;

        CyDelayUs(1u);  /* 0.5 us min delay */
        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        USB_UART_PM_USB_CR0_REG &= (uint8)~USB_UART_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pullup*/
        USB_UART_USBIO_CR1_REG |= USB_UART_USBIO_CR1_IOMODE;

        /* Disable USB in ACT PM */
        USB_UART_PM_ACT_CFG_REG &= (uint8)~USB_UART_PM_ACT_EN_FSUSB;
        /* Disable USB block for Standby Power Mode */
        USB_UART_PM_STBY_CFG_REG &= (uint8)~USB_UART_PM_STBY_EN_FSUSB;
        CyDelayUs(1u); /* min  0.5us delay required */

    }
    else
    {
        USB_UART_backup.enableState = 0u;
    }
    CyExitCriticalSection(enableInterrupts);

    /* Set the DP Interrupt for wake-up from sleep mode. */
    #if(USB_UART_DP_ISR_REMOVE == 0u)
        (void) CyIntSetVector(USB_UART_DP_INTC_VECT_NUM,   &USB_UART_DP_ISR);
        CyIntSetPriority(USB_UART_DP_INTC_VECT_NUM, USB_UART_DP_INTC_PRIOR);
        CyIntClearPending(USB_UART_DP_INTC_VECT_NUM);
        CyIntEnable(USB_UART_DP_INTC_VECT_NUM);
    #endif /* (USB_UART_DP_ISR_REMOVE == 0u) */

}


/*******************************************************************************
* Function Name: USB_UART_Resume
********************************************************************************
*
* Summary:
*  This function enables the USBFS block after power down mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_backup - checked.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_Resume(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if(USB_UART_backup.enableState != 0u)
    {
        #if(USB_UART_DP_ISR_REMOVE == 0u)
            CyIntDisable(USB_UART_DP_INTC_VECT_NUM);
        #endif /* End USB_UART_DP_ISR_REMOVE */

        /* Enable USB block */
        USB_UART_PM_ACT_CFG_REG |= USB_UART_PM_ACT_EN_FSUSB;
        /* Enable USB block for Standby Power Mode */
        USB_UART_PM_STBY_CFG_REG |= USB_UART_PM_STBY_EN_FSUSB;
        /* Enable core clock */
        USB_UART_USB_CLK_EN_REG |= USB_UART_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        USB_UART_PM_USB_CR0_REG |= USB_UART_PM_USB_CR0_REF_EN;
        /* The reference will be available ~40us after power restored */
        CyDelayUs(40u);
        /* Return VRegulator*/
        USB_UART_CR1_REG |= USB_UART_backup.mode;
        CyDelayUs(0u);  /*~50ns delay */
        /* Enable USBIO */
        USB_UART_PM_USB_CR0_REG |= USB_UART_PM_USB_CR0_PD_N;
        CyDelayUs(2u);
        /* Set the USBIO pull-up enable */
        USB_UART_PM_USB_CR0_REG |= USB_UART_PM_USB_CR0_PD_PULLUP_N;

        /* Reinit Arbiter configuration for DMA transfers */
        #if(USB_UART_EP_MM != USB_UART__EP_MANUAL)
            /* usb arb interrupt enable */
            USB_UART_ARB_INT_EN_REG = USB_UART_ARB_INT_MASK;
            #if(USB_UART_EP_MM == USB_UART__EP_DMAMANUAL)
                USB_UART_ARB_CFG_REG = USB_UART_ARB_CFG_MANUAL_DMA;
            #endif   /* End USB_UART_EP_MM == USB_UART__EP_DMAMANUAL */
            #if(USB_UART_EP_MM == USB_UART__EP_DMAAUTO)
                /*Set cfg cmplt this rises DMA request when the full configuration is done */
                USB_UART_ARB_CFG_REG = USB_UART_ARB_CFG_AUTO_DMA | USB_UART_ARB_CFG_AUTO_MEM;
            #endif   /* End USB_UART_EP_MM == USB_UART__EP_DMAAUTO */
        #endif   /* End USB_UART_EP_MM != USB_UART__EP_MANUAL */

        /* STALL_IN_OUT */
        CY_SET_REG8(USB_UART_EP0_CR_PTR, USB_UART_MODE_STALL_IN_OUT);
        /* Enable the SIE with a last address */
        USB_UART_CR0_REG |= USB_UART_CR0_ENABLE;
        CyDelayCycles(1u);
        /* Finally, Enable d+ pullup and select iomode to USB mode*/
        CY_SET_REG8(USB_UART_USBIO_CR1_PTR, USB_UART_USBIO_CR1_USBPUEN);

        /* Restore USB register settings */
        USB_UART_RestoreConfig();

    }
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
