/*******************************************************************************
* File Name: USB_UART_cdc.c
* Version 2.60
*
* Description:
*  USB HID Class request handler.
*
* Note:
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB_UART.h"

#if defined(USB_UART_ENABLE_CDC_CLASS)

#include "USB_UART_cdc.h"
#include "USB_UART_pvt.h"


/***************************************
*    CDC Variables
***************************************/

volatile uint8 USB_UART_lineCoding[USB_UART_LINE_CODING_SIZE];
volatile uint8 USB_UART_lineChanged;
volatile uint16 USB_UART_lineControlBitmap;
volatile uint8 USB_UART_cdc_data_in_ep;
volatile uint8 USB_UART_cdc_data_out_ep;


/***************************************
*     Static Function Prototypes
***************************************/
static uint16 USB_UART_StrLen(const char8 string[]) ;


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB_UART_DispatchCDCClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches CDC class requests.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   USB_UART_lineCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   USB_UART_lineControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   USB_UART_lineChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_DispatchCDCClassRqst(void) 
{
    uint8 requestHandled = USB_UART_FALSE;

    if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) == USB_UART_RQST_DIR_D2H)
    {   /* Control Read */
        switch (CY_GET_REG8(USB_UART_bRequest))
        {
            case USB_UART_CDC_GET_LINE_CODING:
                USB_UART_currentTD.count = USB_UART_LINE_CODING_SIZE;
                USB_UART_currentTD.pData = USB_UART_lineCoding;
                requestHandled  = USB_UART_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) == \
                                                                            USB_UART_RQST_DIR_H2D)
    {   /* Control Write */
        switch (CY_GET_REG8(USB_UART_bRequest))
        {
            case USB_UART_CDC_SET_LINE_CODING:
                USB_UART_currentTD.count = USB_UART_LINE_CODING_SIZE;
                USB_UART_currentTD.pData = USB_UART_lineCoding;
                USB_UART_lineChanged |= USB_UART_LINE_CODING_CHANGED;
                requestHandled = USB_UART_InitControlWrite();
                break;

            case USB_UART_CDC_SET_CONTROL_LINE_STATE:
                USB_UART_lineControlBitmap = CY_GET_REG8(USB_UART_wValueLo);
                USB_UART_lineChanged |= USB_UART_LINE_CONTROL_CHANGED;
                requestHandled = USB_UART_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (USB_UART_ENABLE_CDC_CLASS_API != 0u)


    /*******************************************************************************
    * Function Name: USB_UART_CDC_Init
    ********************************************************************************
    *
    * Summary:
    *  This function initialize the CDC interface to be ready for the receive data
    *  from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_UART_lineChanged: Initialized to zero.
    *   USB_UART_cdc_data_out_ep: Used as an OUT endpoint number.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_UART_CDC_Init(void) 
    {
        USB_UART_lineChanged = 0u;
        USB_UART_EnableOutEP(USB_UART_cdc_data_out_ep);
    }


    /*******************************************************************************
    * Function Name: USB_UART_PutData
    ********************************************************************************
    *
    * Summary:
    *  Sends a specified number of bytes from the location specified by a
    *  pointer to the PC.
    *
    * Parameters:
    *  pData: pointer to the buffer containing data to be sent.
    *  length: Specifies the number of bytes to send from the pData
    *  buffer. Maximum length will be limited by the maximum packet
    *  size for the endpoint.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_UART_PutData(const uint8* pData, uint16 length) 
    {
        /* Limits length to maximum packet size for the EP */
        if(length > USB_UART_EP[USB_UART_cdc_data_in_ep].bufferSize)
        {
            /* Caution: Data will be lost if length is greater than Max Packet Length */
            length = USB_UART_EP[USB_UART_cdc_data_in_ep].bufferSize;
             /* Halt CPU in debug mode */
            CYASSERT(0u != 0u);
        }
        USB_UART_LoadInEP(USB_UART_cdc_data_in_ep, pData, length);
    }


    /*******************************************************************************
    * Function Name: USB_UART_StrLen
    ********************************************************************************
    *
    * Summary:
    *  Calculates length of a null terminated string.
    *
    * Parameters:
    *  string: pointer to the string.
    *
    * Return:
    *  Length of the string
    *
    *******************************************************************************/
    static uint16 USB_UART_StrLen(const char8 string[]) 
    {
        uint16 len = 0u;

        while (string[len] != (char8)0)
        {
            len++;
        }

        return (len);
    }


    /*******************************************************************************
    * Function Name: USB_UART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a null terminated string to the PC.
    *
    * Parameters:
    *  string: pointer to the string to be sent to the PC
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole
    *  string, it will block until the entire string has been written to the
    *  transmit buffer.
    *
    *******************************************************************************/
    void USB_UART_PutString(const char8 string[]) 
    {
        uint16 str_length;
        uint16 send_length;
        uint16 buf_index = 0u;

        /* Get length of the null terminated string */
        str_length = USB_UART_StrLen(string);
        do
        {
            /* Limits length to maximum packet size for the EP */
            send_length = (str_length > USB_UART_EP[USB_UART_cdc_data_in_ep].bufferSize) ?
                          USB_UART_EP[USB_UART_cdc_data_in_ep].bufferSize : str_length;
             /* Enable IN transfer */
            USB_UART_LoadInEP(USB_UART_cdc_data_in_ep, (const uint8 *)&string[buf_index], send_length);
            str_length -= send_length;

            /* If more data are present to send */
            if(str_length > 0u)
            {
                buf_index += send_length;
                /* Wait for the Host to read it. */
                while(USB_UART_EP[USB_UART_cdc_data_in_ep].apiEpState ==
                                          USB_UART_IN_BUFFER_FULL)
                {
                    ;
                }
            }
        }while(str_length > 0u);
    }


    /*******************************************************************************
    * Function Name: USB_UART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Writes a single character to the PC.
    *
    * Parameters:
    *  txDataByte: Character to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_UART_PutChar(char8 txDataByte) 
    {
        uint8 dataByte;
        dataByte = (uint8)txDataByte;

        USB_UART_LoadInEP(USB_UART_cdc_data_in_ep, &dataByte, 1u);
    }


    /*******************************************************************************
    * Function Name: USB_UART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Sends a carriage return (0x0D) and line feed (0x0A) to the PC
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_UART_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_UART_PutCRLF(void) 
    {
        const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

        USB_UART_LoadInEP(USB_UART_cdc_data_in_ep, (const uint8 *)txData, 2u);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetCount
    ********************************************************************************
    *
    * Summary:
    *  This function returns the number of bytes that were received from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of received bytes.
    *
    * Global variables:
    *   USB_UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint16 USB_UART_GetCount(void) 
    {
        uint16 bytesCount = 0u;

        if (USB_UART_EP[USB_UART_cdc_data_out_ep].apiEpState == USB_UART_OUT_BUFFER_FULL)
        {
            bytesCount = USB_UART_GetEPCount(USB_UART_cdc_data_out_ep);
        }

        return(bytesCount);
    }


    /*******************************************************************************
    * Function Name: USB_UART_DataIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component received data or received
    *  zero-length packet. The GetAll() or GetData() API should be called to read
    *  data from the buffer and re-init OUT endpoint even when zero-length packet
    *  received.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the OUT packet received this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   USB_UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint8 USB_UART_DataIsReady(void) 
    {
        return(USB_UART_EP[USB_UART_cdc_data_out_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: USB_UART_CDCIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component is ready to send more data to the
    *  PC. Otherwise returns zero. Should be called before sending new data to
    *  ensure the previous data has finished sending.This function returns the
    *  number of bytes that were received from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the buffer can accept new data then this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   USB_UART_cdc_data_in_ep: CDC IN endpoint number used.
    *
    *******************************************************************************/
    uint8 USB_UART_CDCIsReady(void) 
    {
        return(USB_UART_EP[USB_UART_cdc_data_in_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetData
    ********************************************************************************
    *
    * Summary:
    *  Gets a specified number of bytes from the input buffer and places it in a
    *  data array specified by the passed pointer.
    *  USB_UART_DataIsReady() API should be called before, to be sure
    *  that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *  Length: Number of bytes to read into the data array from the RX buffer.
    *          Maximum length is limited by the the number of received bytes.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   USB_UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 USB_UART_GetData(uint8* pData, uint16 length) 
    {
        return(USB_UART_ReadOutEP(USB_UART_cdc_data_out_ep, pData, length));
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetAll
    ********************************************************************************
    *
    * Summary:
    *  Gets all bytes of received data from the input buffer and places it into a
    *  specified data array. USB_UART_DataIsReady() API should be called
    *  before, to be sure that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   USB_UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *   USB_UART_EP[].bufferSize: EP max packet size is used as a length
    *     to read all data from the EP buffer.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 USB_UART_GetAll(uint8* pData) 
    {
        return (USB_UART_ReadOutEP(USB_UART_cdc_data_out_ep, pData,
                                           USB_UART_EP[USB_UART_cdc_data_out_ep].bufferSize));
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads one byte of received data from the buffer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received one character.
    *
    * Global variables:
    *   USB_UART_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 USB_UART_GetChar(void) 
    {
         uint8 rxData;

        (void) USB_UART_ReadOutEP(USB_UART_cdc_data_out_ep, &rxData, 1u);

        return(rxData);
    }

    /*******************************************************************************
    * Function Name: USB_UART_IsLineChanged
    ********************************************************************************
    *
    * Summary:
    *  This function returns clear on read status of the line.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE request received then not
    *  zero value returned. Otherwise zero is returned.
    *
    * Global variables:
    *  USB_UART_transferState - it is checked to be sure then OUT data
    *    phase has been complete, and data written to the lineCoding or Control
    *    Bitmap buffer.
    *  USB_UART_lineChanged: used as a flag to be aware that Host has been
    *    sent request for changing Line Coding or Control Bitmap.
    *
    *******************************************************************************/
    uint8 USB_UART_IsLineChanged(void) 
    {
        uint8 state = 0u;

        /* transferState is checked to be sure then OUT data phase has been complete */
        if(USB_UART_transferState == USB_UART_TRANS_STATE_IDLE)
        {
            if(USB_UART_lineChanged != 0u)
            {
                state = USB_UART_lineChanged;
                USB_UART_lineChanged = 0u;
            }
        }

        return(state);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetDTERate
    ********************************************************************************
    *
    * Summary:
    *  Returns the data terminal rate set for this port in bits per second.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns a uint32 value of the data rate in bits per second.
    *
    * Global variables:
    *  USB_UART_lineCoding: First four bytes converted to uint32
    *    depend on compiler, and returned as a data rate.
    *
    *******************************************************************************/
    uint32 USB_UART_GetDTERate(void) 
    {
        uint32 rate;

        rate = USB_UART_lineCoding[USB_UART_LINE_CODING_RATE + 3u];
        rate = (rate << 8u) | USB_UART_lineCoding[USB_UART_LINE_CODING_RATE + 2u];
        rate = (rate << 8u) | USB_UART_lineCoding[USB_UART_LINE_CODING_RATE + 1u];
        rate = (rate << 8u) | USB_UART_lineCoding[USB_UART_LINE_CODING_RATE];

        return(rate);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetCharFormat
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of stop bits.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of stop bits.
    *
    * Global variables:
    *  USB_UART_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 USB_UART_GetCharFormat(void) 
    {
        return(USB_UART_lineCoding[USB_UART_LINE_CODING_STOP_BITS]);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetParityType
    ********************************************************************************
    *
    * Summary:
    *  Returns the parity type for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the parity type.
    *
    * Global variables:
    *  USB_UART_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 USB_UART_GetParityType(void) 
    {
        return(USB_UART_lineCoding[USB_UART_LINE_CODING_PARITY]);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetDataBits
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of data bits for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of data bits.
    *  The number of data bits can be 5, 6, 7, 8 or 16.
    *
    * Global variables:
    *  USB_UART_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 USB_UART_GetDataBits(void) 
    {
        return(USB_UART_lineCoding[USB_UART_LINE_CODING_DATA_BITS]);
    }


    /*******************************************************************************
    * Function Name: USB_UART_GetLineControl
    ********************************************************************************
    *
    * Summary:
    *  Returns Line control bitmap.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns Line control bitmap.
    *
    * Global variables:
    *  USB_UART_lineControlBitmap: used to get a parameter.
    *
    *******************************************************************************/
    uint16 USB_UART_GetLineControl(void) 
    {
        return(USB_UART_lineControlBitmap);
    }

#endif  /* End USB_UART_ENABLE_CDC_CLASS_API*/


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* End USB_UART_ENABLE_CDC_CLASS*/


/* [] END OF FILE */
