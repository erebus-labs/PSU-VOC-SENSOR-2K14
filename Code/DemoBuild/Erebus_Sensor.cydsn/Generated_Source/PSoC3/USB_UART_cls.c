/*******************************************************************************
* File Name: USB_UART_cls.c
* Version 2.60
*
* Description:
*  USB Class request handler.
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

#if(USB_UART_EXTERN_CLS == USB_UART_FALSE)

#include "USB_UART_pvt.h"


/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB_UART_DispatchClassRqst
********************************************************************************
* Summary:
*  This routine dispatches class specific requests depend on interface class.
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
uint8 USB_UART_DispatchClassRqst(void) 
{
    uint8 requestHandled = USB_UART_FALSE;
    uint8 interfaceNumber = 0u;

    switch(CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_RCPT_MASK)
    {
        case USB_UART_RQST_RCPT_IFC:        /* Class-specific request directed to an interface */
            interfaceNumber = CY_GET_REG8(USB_UART_wIndexLo); /* wIndexLo contain Interface number */
            break;
        case USB_UART_RQST_RCPT_EP:         /* Class-specific request directed to the endpoint */
            /* Find related interface to the endpoint, wIndexLo contain EP number */
            interfaceNumber =
                USB_UART_EP[CY_GET_REG8(USB_UART_wIndexLo) & USB_UART_DIR_UNUSED].interface;
            break;
        default:    /* RequestHandled is initialized as FALSE by default */
            break;
    }
    /* Handle Class request depend on interface type */
    switch(USB_UART_interfaceClass[interfaceNumber])
    {
        case USB_UART_CLASS_HID:
            #if defined(USB_UART_ENABLE_HID_CLASS)
                requestHandled = USB_UART_DispatchHIDClassRqst();
            #endif /* USB_UART_ENABLE_HID_CLASS */
            break;
        case USB_UART_CLASS_AUDIO:
            #if defined(USB_UART_ENABLE_AUDIO_CLASS)
                requestHandled = USB_UART_DispatchAUDIOClassRqst();
            #endif /* USB_UART_ENABLE_HID_CLASS */
            break;
        case USB_UART_CLASS_CDC:
            #if defined(USB_UART_ENABLE_CDC_CLASS)
                requestHandled = USB_UART_DispatchCDCClassRqst();
            #endif /* USB_UART_ENABLE_CDC_CLASS */
            break;
        default:    /* requestHandled is initialized as FALSE by default */
            break;
    }

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* USB_UART_EXTERN_CLS */


/* [] END OF FILE */
