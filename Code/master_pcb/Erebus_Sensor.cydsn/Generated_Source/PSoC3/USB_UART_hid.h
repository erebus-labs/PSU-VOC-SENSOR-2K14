/*******************************************************************************
* File Name: USB_UART_hid.h
* Version 2.60
*
* Description:
*  Header File for the USFS component. Contains prototypes and constant values.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USB_UART_hid_H)
#define CY_USBFS_USB_UART_hid_H

#include "cytypes.h"


/***************************************
* Prototypes of the USB_UART_hid API.
***************************************/

uint8 USB_UART_UpdateHIDTimer(uint8 interface) ;
uint8 USB_UART_GetProtocol(uint8 interface) ;


/***************************************
*Renamed Functions for backward compatible
***************************************/

#define USB_UART_bGetProtocol               USB_UART_GetProtocol


/***************************************
*  Constants for USB_UART_hid API.
***************************************/

#define USB_UART_PROTOCOL_BOOT              (0x00u)
#define USB_UART_PROTOCOL_REPORT            (0x01u)

/* Request Types (HID Chapter 7.2) */
#define USB_UART_HID_GET_REPORT             (0x01u)
#define USB_UART_HID_GET_IDLE               (0x02u)
#define USB_UART_HID_GET_PROTOCOL           (0x03u)
#define USB_UART_HID_SET_REPORT             (0x09u)
#define USB_UART_HID_SET_IDLE               (0x0Au)
#define USB_UART_HID_SET_PROTOCOL           (0x0Bu)

/* Descriptor Types (HID Chapter 7.1) */
#define USB_UART_DESCR_HID_CLASS            (0x21u)
#define USB_UART_DESCR_HID_REPORT           (0x22u)
#define USB_UART_DESCR_HID_PHYSICAL         (0x23u)

/* Report Request Types (HID Chapter 7.2.1) */
#define USB_UART_HID_GET_REPORT_INPUT       (0x01u)
#define USB_UART_HID_GET_REPORT_OUTPUT      (0x02u)
#define USB_UART_HID_GET_REPORT_FEATURE     (0x03u)

#endif /* End CY_USBFS_USB_UART_hid_H */


/* [] END OF FILE */
