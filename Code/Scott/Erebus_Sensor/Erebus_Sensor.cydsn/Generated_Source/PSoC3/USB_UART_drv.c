/*******************************************************************************
* File Name: USB_UART_drv.c
* Version 2.60
*
* Description:
*  Endpoint 0 Driver for the USBFS Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB_UART.h"
#include "USB_UART_pvt.h"


/***************************************
* Global data allocation
***************************************/

volatile T_USB_UART_EP_CTL_BLOCK USB_UART_EP[USB_UART_MAX_EP];
volatile uint8 USB_UART_configuration;
volatile uint8 USB_UART_interfaceNumber;
volatile uint8 USB_UART_configurationChanged;
volatile uint8 USB_UART_deviceAddress;
volatile uint8 USB_UART_deviceStatus;
volatile uint8 USB_UART_interfaceSetting[USB_UART_MAX_INTERFACES_NUMBER];
volatile uint8 USB_UART_interfaceSetting_last[USB_UART_MAX_INTERFACES_NUMBER];
volatile uint8 USB_UART_interfaceStatus[USB_UART_MAX_INTERFACES_NUMBER];
volatile uint8 USB_UART_device;
const uint8 CYCODE *USB_UART_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8 USB_UART_ep0Toggle;
volatile uint8 USB_UART_lastPacketSize;
volatile uint8 USB_UART_transferState;
volatile T_USB_UART_TD USB_UART_currentTD;
volatile uint8 USB_UART_ep0Mode;
volatile uint8 USB_UART_ep0Count;
volatile uint16 USB_UART_transferByteCount;


/*******************************************************************************
* Function Name: USB_UART_ep_0_Interrupt
********************************************************************************
*
* Summary:
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(USB_UART_EP_0_ISR)
{
    uint8 bRegTemp;
    uint8 modifyReg;


    bRegTemp = CY_GET_REG8(USB_UART_EP0_CR_PTR);
    if ((bRegTemp & USB_UART_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((bRegTemp & USB_UART_MODE_SETUP_RCVD) != 0u)
        {
            if((bRegTemp & USB_UART_MODE_MASK) != USB_UART_MODE_NAK_IN_OUT)
            {
                modifyReg = 0u;                                     /* When mode not NAK_IN_OUT => invalid setup */
            }
            else
            {
                USB_UART_HandleSetup();
                if((USB_UART_ep0Mode & USB_UART_MODE_SETUP_RCVD) != 0u)
                {
                    modifyReg = 0u;                         /* if SETUP bit set -> exit without modifying the mode */
                }

            }
        }
        else if ((bRegTemp & USB_UART_MODE_IN_RCVD) != 0u)
        {
            USB_UART_HandleIN();
        }
        else if ((bRegTemp & USB_UART_MODE_OUT_RCVD) != 0u)
        {
            USB_UART_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        if(modifyReg != 0u)
        {
            bRegTemp = CY_GET_REG8(USB_UART_EP0_CR_PTR);    /* unlock registers */
            if((bRegTemp & USB_UART_MODE_SETUP_RCVD) == 0u)  /* Check if SETUP bit is not set, otherwise exit */
            {
                /* Update the count register */
                bRegTemp = USB_UART_ep0Toggle | USB_UART_ep0Count;
                CY_SET_REG8(USB_UART_EP0_CNT_PTR, bRegTemp);
                if(bRegTemp == CY_GET_REG8(USB_UART_EP0_CNT_PTR))   /* continue if writing was successful */
                {
                    do
                    {
                        modifyReg = USB_UART_ep0Mode;       /* Init temporary variable */
                        /* Unlock registers */
                        bRegTemp = CY_GET_REG8(USB_UART_EP0_CR_PTR) & USB_UART_MODE_SETUP_RCVD;
                        if(bRegTemp == 0u)                          /* Check if SETUP bit is not set */
                        {
                            /* Set the Mode Register  */
                            CY_SET_REG8(USB_UART_EP0_CR_PTR, USB_UART_ep0Mode);
                            /* Writing check */
                            modifyReg = CY_GET_REG8(USB_UART_EP0_CR_PTR) & USB_UART_MODE_MASK;
                        }
                    }while(modifyReg != USB_UART_ep0Mode);  /* Repeat if writing was not successful */
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: USB_UART_HandleSetup
********************************************************************************
*
* Summary:
*  This Routine dispatches requests for the four USB request types
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
void USB_UART_HandleSetup(void) 
{
    uint8 requestHandled;

    requestHandled = CY_GET_REG8(USB_UART_EP0_CR_PTR);      /* unlock registers */
    CY_SET_REG8(USB_UART_EP0_CR_PTR, requestHandled);       /* clear setup bit */
    requestHandled = CY_GET_REG8(USB_UART_EP0_CR_PTR);      /* reread register */
    if((requestHandled & USB_UART_MODE_SETUP_RCVD) != 0u)
    {
        USB_UART_ep0Mode = requestHandled;        /* if SETUP bit set -> exit without modifying the mode */
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        USB_UART_UpdateStatusBlock(USB_UART_XFER_PREMATURE);

        switch (CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_TYPE_MASK)
        {
            case USB_UART_RQST_TYPE_STD:
                requestHandled = USB_UART_HandleStandardRqst();
                break;
            case USB_UART_RQST_TYPE_CLS:
                requestHandled = USB_UART_DispatchClassRqst();
                break;
            case USB_UART_RQST_TYPE_VND:
                requestHandled = USB_UART_HandleVendorRqst();
                break;
            default:
                requestHandled = USB_UART_FALSE;
                break;
        }
        if (requestHandled == USB_UART_FALSE)
        {
            USB_UART_ep0Mode = USB_UART_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: USB_UART_HandleIN
********************************************************************************
*
* Summary:
*  This routine handles EP0 IN transfers.
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
void USB_UART_HandleIN(void) 
{
    switch (USB_UART_transferState)
    {
        case USB_UART_TRANS_STATE_IDLE:
            break;
        case USB_UART_TRANS_STATE_CONTROL_READ:
            USB_UART_ControlReadDataStage();
            break;
        case USB_UART_TRANS_STATE_CONTROL_WRITE:
            USB_UART_ControlWriteStatusStage();
            break;
        case USB_UART_TRANS_STATE_NO_DATA_CONTROL:
            USB_UART_NoDataControlStatusStage();
            break;
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USB_UART_HandleOUT
********************************************************************************
*
* Summary:
*  This routine handles EP0 OUT transfers.
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
void USB_UART_HandleOUT(void) 
{
    switch (USB_UART_transferState)
    {
        case USB_UART_TRANS_STATE_IDLE:
            break;
        case USB_UART_TRANS_STATE_CONTROL_READ:
            USB_UART_ControlReadStatusStage();
            break;
        case USB_UART_TRANS_STATE_CONTROL_WRITE:
            USB_UART_ControlWriteDataStage();
            break;
        case USB_UART_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            USB_UART_UpdateStatusBlock(USB_UART_XFER_ERROR);
            /* We expect no more data, so stall INs and OUTs */
            USB_UART_ep0Mode = USB_UART_MODE_STALL_IN_OUT;
            break;
        default:    /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USB_UART_LoadEP0
********************************************************************************
*
* Summary:
*  This routine loads the EP0 data registers for OUT transfers.  It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  USB_UART_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  USB_UART_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  USB_UART_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  USB_UART_ep0Toggle - inverted
*  USB_UART_ep0Mode  - prepare for mode register content.
*  USB_UART_transferState - set to TRANS_STATE_CONTROL_READ
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    USB_UART_transferByteCount += USB_UART_lastPacketSize;
    /* Now load the next transaction */
    while ((USB_UART_currentTD.count > 0u) && (ep0Count < 8u))
    {
        CY_SET_REG8((reg8 *)(USB_UART_EP0_DR0_IND + ep0Count), *USB_UART_currentTD.pData);
        USB_UART_currentTD.pData = &USB_UART_currentTD.pData[1u];
        ep0Count++;
        USB_UART_currentTD.count--;
    }
    /* Support zero-length packet*/
    if( (USB_UART_lastPacketSize == 8u) || (ep0Count > 0u) )
    {
        /* Update the data toggle */
        USB_UART_ep0Toggle ^= USB_UART_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        USB_UART_ep0Mode = USB_UART_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        USB_UART_transferState = USB_UART_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        USB_UART_ep0Mode = USB_UART_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        USB_UART_transferState = USB_UART_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    USB_UART_lastPacketSize = ep0Count;
    USB_UART_ep0Count = ep0Count;
}


/*******************************************************************************
* Function Name: USB_UART_InitControlRead
********************************************************************************
*
* Summary:
*  Initialize a control read transaction, usable to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB_UART_currentTD.count - counts of data to be sent.
*  USB_UART_currentTD.pData - data pointer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_InitControlRead(void) 
{
    uint16 xferCount;
    if(USB_UART_currentTD.count == 0u)
    {
        (void) USB_UART_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        USB_UART_transferState = USB_UART_TRANS_STATE_CONTROL_READ;
        /* Set the toggle, it gets updated in LoadEP */
        USB_UART_ep0Toggle = 0u;
        /* Initialize the Status Block */
        USB_UART_InitializeStatusBlock();
        xferCount = (((uint16)CY_GET_REG8(USB_UART_lengthHi) << 8u) | (CY_GET_REG8(USB_UART_lengthLo)));

        if (USB_UART_currentTD.count > xferCount)
        {
            USB_UART_currentTD.count = xferCount;
        }
        USB_UART_LoadEP0();
    }

    return(USB_UART_TRUE);
}


/*******************************************************************************
* Function Name: USB_UART_InitZeroLengthControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a zero length data IN transfer.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB_UART_ep0Mode  - prepare for mode register content.
*  USB_UART_transferState - set to TRANS_STATE_CONTROL_READ
*  USB_UART_ep0Count - cleared, means the zero-length packet.
*  USB_UART_lastPacketSize - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    USB_UART_transferState = USB_UART_TRANS_STATE_CONTROL_READ;
    /* Set the data toggle */
    USB_UART_ep0Toggle = USB_UART_EP0_CNT_DATA_TOGGLE;
    /* Set the Mode Register  */
    USB_UART_ep0Mode = USB_UART_MODE_ACK_IN_STATUS_OUT;
    /* Save the packet size for next time */
    USB_UART_lastPacketSize = 0u;
    USB_UART_ep0Count = 0u;

    return(USB_UART_TRUE);
}


/*******************************************************************************
* Function Name: USB_UART_ControlReadDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control read transfer.
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
void USB_UART_ControlReadDataStage(void) 

{
    USB_UART_LoadEP0();
}


/*******************************************************************************
* Function Name: USB_UART_ControlReadStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control read transfer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_USBFS_transferByteCount - updated with last packet size.
*  USB_UART_transferState - set to TRANS_STATE_IDLE.
*  USB_UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    USB_UART_transferByteCount += USB_UART_lastPacketSize;
    /* Go Idle */
    USB_UART_transferState = USB_UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB_UART_UpdateStatusBlock(USB_UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    USB_UART_ep0Mode =  USB_UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB_UART_InitControlWrite
********************************************************************************
*
* Summary:
*  Initialize a control write transaction
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB_UART_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  USB_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB_UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    USB_UART_transferState = USB_UART_TRANS_STATE_CONTROL_WRITE;
    /* This might not be necessary */
    USB_UART_ep0Toggle = USB_UART_EP0_CNT_DATA_TOGGLE;
    /* Initialize the Status Block */
    USB_UART_InitializeStatusBlock();

    xferCount = (((uint16)CY_GET_REG8(USB_UART_lengthHi) << 8u) | (CY_GET_REG8(USB_UART_lengthLo)));

    if (USB_UART_currentTD.count > xferCount)
    {
        USB_UART_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    USB_UART_ep0Mode = USB_UART_MODE_ACK_OUT_STATUS_IN;

    return(USB_UART_TRUE);
}


/*******************************************************************************
* Function Name: USB_UART_ControlWriteDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  USB_UART_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  USB_UART_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  USB_UART_ep0Toggle - inverted
*  USB_UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (CY_GET_REG8(USB_UART_EP0_CNT_PTR) & USB_UART_EPX_CNT0_MASK) -
               USB_UART_EPX_CNTX_CRC_COUNT;

    USB_UART_transferByteCount += ep0Count;

    while ((USB_UART_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *USB_UART_currentTD.pData = CY_GET_REG8((reg8 *)(USB_UART_EP0_DR0_IND + regIndex));
        USB_UART_currentTD.pData = &USB_UART_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        USB_UART_currentTD.count--;
    }
    USB_UART_ep0Count = ep0Count;
    /* Update the data toggle */
    USB_UART_ep0Toggle ^= USB_UART_EP0_CNT_DATA_TOGGLE;
    /* Expect Data or Status Stage */
    USB_UART_ep0Mode = USB_UART_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: USB_UART_ControlWriteStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control write transfer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_transferState - set to TRANS_STATE_IDLE.
*  USB_UART_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    USB_UART_transferState = USB_UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB_UART_UpdateStatusBlock(USB_UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    USB_UART_ep0Mode = USB_UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB_UART_InitNoDataControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a no data control transfer
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB_UART_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  USB_UART_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  USB_UART_ep0Count - cleared.
*  USB_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_InitNoDataControlTransfer(void) 
{
    USB_UART_transferState = USB_UART_TRANS_STATE_NO_DATA_CONTROL;
    USB_UART_ep0Mode = USB_UART_MODE_STATUS_IN_ONLY;
    USB_UART_ep0Toggle = USB_UART_EP0_CNT_DATA_TOGGLE;
    USB_UART_ep0Count = 0u;

    return(USB_UART_TRUE);
}


/*******************************************************************************
* Function Name: USB_UART_NoDataControlStatusStage
********************************************************************************
* Summary:
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_transferState - set to TRANS_STATE_IDLE.
*  USB_UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*  USB_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB_UART_deviceAddress - used to set new address and cleared
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_NoDataControlStatusStage(void) 
{
    /* Change the USB address register if we got a SET_ADDRESS. */
    if (USB_UART_deviceAddress != 0u)
    {
        CY_SET_REG8(USB_UART_CR0_PTR, USB_UART_deviceAddress | USB_UART_CR0_ENABLE);
        USB_UART_deviceAddress = 0u;
    }
    /* Go Idle */
    USB_UART_transferState = USB_UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB_UART_UpdateStatusBlock(USB_UART_XFER_STATUS_ACK);
     /* We expect no more data, so stall INs and OUTs */
    USB_UART_ep0Mode = USB_UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB_UART_UpdateStatusBlock
********************************************************************************
*
* Summary:
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the USB_UART_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
* Parameters:
*  completionCode - status.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  USB_UART_currentTD.pStatusBlock->length - updated.
*  USB_UART_currentTD.pStatusBlock - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_UpdateStatusBlock(uint8 completionCode) 
{
    if (USB_UART_currentTD.pStatusBlock != NULL)
    {
        USB_UART_currentTD.pStatusBlock->status = completionCode;
        USB_UART_currentTD.pStatusBlock->length = USB_UART_transferByteCount;
        USB_UART_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: USB_UART_InitializeStatusBlock
********************************************************************************
*
* Summary:
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes USB_UART_transferByteCount.  Save some space,
*  this is the only consumer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_UART_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  USB_UART_currentTD.pStatusBlock->length - cleared.
*  USB_UART_transferByteCount - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_InitializeStatusBlock(void) 
{
    USB_UART_transferByteCount = 0u;
    if(USB_UART_currentTD.pStatusBlock != NULL)
    {
        USB_UART_currentTD.pStatusBlock->status = USB_UART_XFER_IDLE;
        USB_UART_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
