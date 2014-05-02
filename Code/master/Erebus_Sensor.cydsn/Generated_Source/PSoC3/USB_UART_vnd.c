/*******************************************************************************
* File Name: USB_UART_vnd.c
* Version 2.60
*
* Description:
*  USB vendor request handler.
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

#if(USB_UART_EXTERN_VND == USB_UART_FALSE)


/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB_UART_HandleVendorRqst
********************************************************************************
*
* Summary:
*  This routine provide users with a method to implement vendor specifc
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_HandleVendorRqst(void) 
{
    uint8 requestHandled = USB_UART_FALSE;

    if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) == USB_UART_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(USB_UART_bRequest))
        {
            case USB_UART_GET_EXTENDED_CONFIG_DESCRIPTOR:
                #if defined(USB_UART_ENABLE_MSOS_STRING)
                    USB_UART_currentTD.pData = (volatile uint8 *)&USB_UART_MSOS_CONFIGURATION_DESCR[0u];
                    USB_UART_currentTD.count = USB_UART_MSOS_CONFIGURATION_DESCR[0u];
                    requestHandled  = USB_UART_InitControlRead();
                #endif /* End USB_UART_ENABLE_MSOS_STRING */
                break;
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* USB_UART_EXTERN_VND */


/* [] END OF FILE */
