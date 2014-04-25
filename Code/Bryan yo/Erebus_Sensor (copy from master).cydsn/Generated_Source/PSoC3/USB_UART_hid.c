/*******************************************************************************
* File Name: USB_UART_hid.c
* Version 2.60
*
* Description:
*  USB HID Class request handler.
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

#if defined(USB_UART_ENABLE_HID_CLASS)

#include "USB_UART_pvt.h"
#include "USB_UART_hid.h"


/***************************************
*    HID Variables
***************************************/

volatile uint8 USB_UART_hidProtocol[USB_UART_MAX_INTERFACES_NUMBER];  /* HID device protocol status */
volatile uint8 USB_UART_hidIdleRate[USB_UART_MAX_INTERFACES_NUMBER];  /* HID device idle reload value */
volatile uint8 USB_UART_hidIdleTimer[USB_UART_MAX_INTERFACES_NUMBER]; /* HID device idle rate value */


/***************************************
* Custom Declarations
***************************************/

/* `#START HID_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB_UART_UpdateHIDTimer
********************************************************************************
*
* Summary:
*  Updates the HID report timer and reloads it if expired
*
* Parameters:
*  interface:  Interface Number.
*
* Return:
*  status.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_UpdateHIDTimer(uint8 interface) 
{
    uint8 stat = USB_UART_IDLE_TIMER_INDEFINITE;

    if(USB_UART_hidIdleRate[interface] != 0u)
    {
        if(USB_UART_hidIdleTimer[interface] > 0u)
        {
            USB_UART_hidIdleTimer[interface]--;
            stat = USB_UART_IDLE_TIMER_RUNNING;
        }
        else
        {
            USB_UART_hidIdleTimer[interface] = USB_UART_hidIdleRate[interface];
            stat = USB_UART_IDLE_TIMER_EXPIRED;
        }
    }

    return(stat);
}


/*******************************************************************************
* Function Name: USB_UART_GetProtocol
********************************************************************************
*
* Summary:
*  Returns the selected protocol value to the application
*
* Parameters:
*  interface:  Interface Number.
*
* Return:
*  Interface protocol.
*
*******************************************************************************/
uint8 USB_UART_GetProtocol(uint8 interface) 
{
    return(USB_UART_hidProtocol[interface]);
}


/*******************************************************************************
* Function Name: USB_UART_DispatchHIDClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches class requests
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_DispatchHIDClassRqst(void) 
{
    uint8 requestHandled = USB_UART_FALSE;
    uint8 interfaceNumber;

    interfaceNumber = CY_GET_REG8(USB_UART_wIndexLo);
    if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) == USB_UART_RQST_DIR_D2H)
    {   /* Control Read */
        switch (CY_GET_REG8(USB_UART_bRequest))
        {
            case USB_UART_GET_DESCRIPTOR:
                if (CY_GET_REG8(USB_UART_wValueHi) == USB_UART_DESCR_HID_CLASS)
                {
                    USB_UART_FindHidClassDecriptor();
                    if (USB_UART_currentTD.count != 0u)
                    {
                        requestHandled = USB_UART_InitControlRead();
                    }
                }
                else if (CY_GET_REG8(USB_UART_wValueHi) == USB_UART_DESCR_HID_REPORT)
                {
                    USB_UART_FindReportDescriptor();
                    if (USB_UART_currentTD.count != 0u)
                    {
                        requestHandled = USB_UART_InitControlRead();
                    }
                }
                else
                {   /* requestHandled is initialezed as FALSE by default */
                }
                break;
            case USB_UART_HID_GET_REPORT:
                USB_UART_FindReport();
                if (USB_UART_currentTD.count != 0u)
                {
                    requestHandled = USB_UART_InitControlRead();
                }
                break;

            case USB_UART_HID_GET_IDLE:
                /* This function does not support multiple reports per interface*/
                /* Validate interfaceNumber and Report ID (should be 0) */
                if( (interfaceNumber < USB_UART_MAX_INTERFACES_NUMBER) &&
                    (CY_GET_REG8(USB_UART_wValueLo) == 0u ) ) /* Do not support Idle per Report ID */
                {
                    USB_UART_currentTD.count = 1u;
                    USB_UART_currentTD.pData = &USB_UART_hidIdleRate[interfaceNumber];
                    requestHandled  = USB_UART_InitControlRead();
                }
                break;
            case USB_UART_HID_GET_PROTOCOL:
                /* Validate interfaceNumber */
                if( interfaceNumber < USB_UART_MAX_INTERFACES_NUMBER)
                {
                    USB_UART_currentTD.count = 1u;
                    USB_UART_currentTD.pData = &USB_UART_hidProtocol[interfaceNumber];
                    requestHandled  = USB_UART_InitControlRead();
                }
                break;
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) ==
                                                                            USB_UART_RQST_DIR_H2D)
    {   /* Control Write */
        switch (CY_GET_REG8(USB_UART_bRequest))
        {
            case USB_UART_HID_SET_REPORT:
                USB_UART_FindReport();
                if (USB_UART_currentTD.count != 0u)
                {
                    requestHandled = USB_UART_InitControlWrite();
                }
                break;
            case USB_UART_HID_SET_IDLE:
                /* This function does not support multiple reports per interface */
                /* Validate interfaceNumber and Report ID (should be 0) */
                if( (interfaceNumber < USB_UART_MAX_INTERFACES_NUMBER) &&
                    (CY_GET_REG8(USB_UART_wValueLo) == 0u ) ) /* Do not support Idle per Report ID */
                {
                    USB_UART_hidIdleRate[interfaceNumber] = CY_GET_REG8(USB_UART_wValueHi);
                    /* With regards to HID spec: "7.2.4 Set_Idle Request"
                    *  Latency. If the current period has gone past the
                    *  newly proscribed time duration, then a report
                    *  will be generated immediately.
                    */
                    if(USB_UART_hidIdleRate[interfaceNumber] <
                       USB_UART_hidIdleTimer[interfaceNumber])
                    {
                        /* Set the timer to zero and let the UpdateHIDTimer() API return IDLE_TIMER_EXPIRED status*/
                        USB_UART_hidIdleTimer[interfaceNumber] = 0u;
                    }
                    /* If the new request is received within 4 milliseconds
                    *  (1 count) of the end of the current period, then the
                    *  new request will have no effect until after the report.
                    */
                    else if(USB_UART_hidIdleTimer[interfaceNumber] <= 1u)
                    {
                        /* Do nothing.
                        *  Let the UpdateHIDTimer() API continue to work and
                        *  return IDLE_TIMER_EXPIRED status
                        */
                    }
                    else
                    {   /* Reload the timer*/
                        USB_UART_hidIdleTimer[interfaceNumber] =
                        USB_UART_hidIdleRate[interfaceNumber];
                    }
                    requestHandled = USB_UART_InitNoDataControlTransfer();
                }
                break;

            case USB_UART_HID_SET_PROTOCOL:
                /* Validate interfaceNumber and protocol (must be 0 or 1) */
                if( (interfaceNumber < USB_UART_MAX_INTERFACES_NUMBER) &&
                    (CY_GET_REG8(USB_UART_wValueLo) <= 1u) )
                {
                    USB_UART_hidProtocol[interfaceNumber] = CY_GET_REG8(USB_UART_wValueLo);
                    requestHandled = USB_UART_InitNoDataControlTransfer();
                }
                break;
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: USB_FindHidClassDescriptor
********************************************************************************
*
* Summary:
*  This routine find Hid Class Descriptor pointer based on the Interface number
*  and Alternate setting then loads the currentTD structure with the address of
*  the buffer and the size.
*  The HID Class Descriptor resides inside the config descriptor.
*
* Parameters:
*  None.
*
* Return:
*  currentTD
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_FindHidClassDecriptor(void) 
{
    const T_USB_UART_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = USB_UART_GetConfigTablePtr(USB_UART_configuration - 1u);
    interfaceN = CY_GET_REG8(USB_UART_wIndexLo);
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number*/
    pTmp = &pTmp[interfaceN + 2u];
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USB_UART_LUT CYCODE *) pTmp->p_list;
    /* Now use Alternate setting number */
    pTmp = &pTmp[USB_UART_interfaceSetting[interfaceN]];
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_USB_UART_LUT CYCODE *) pTmp->p_list;
    /* Fifth entry in the LUT points to Hid Class Descriptor in Configuration Descriptor */
    pTmp = &pTmp[4u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    /* The first byte contains the descriptor length */
    USB_UART_currentTD.count = *pDescr;
    USB_UART_currentTD.pData = pDescr;
}


/*******************************************************************************
* Function Name: USB_FindReportDescriptor
********************************************************************************
*
* Summary:
*  This routine find Hid Report Descriptor pointer based on the Interface
*  number, then loads the currentTD structure with the address of the buffer
*  and the size.
*  Hid Report Descriptor is located after IN/OUT/FEATURE reports.
*
* Parameters:
*   void
*
* Return:
*  currentTD
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_FindReportDescriptor(void) 
{
    const T_USB_UART_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = USB_UART_GetConfigTablePtr(USB_UART_configuration - 1u);
    interfaceN = CY_GET_REG8(USB_UART_wIndexLo);
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USB_UART_LUT CYCODE *) pTmp->p_list;
    /* Now use Alternate setting number */
    pTmp = &pTmp[USB_UART_interfaceSetting[interfaceN]];
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_USB_UART_LUT CYCODE *) pTmp->p_list;
    /* Fourth entry in the LUT starts the Hid Report Descriptor */
    pTmp = &pTmp[3u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    /* The 1st and 2nd bytes of descriptor contain its length. LSB is 1st. */
    USB_UART_currentTD.count =  (((uint16)pDescr[1u] << 8u) | pDescr[0u]);
    USB_UART_currentTD.pData = &pDescr[2u];
}


/*******************************************************************************
* Function Name: USB_UART_FindReport
********************************************************************************
*
* Summary:
*  This routine sets up a transfer based on the Interface number, Report Type
*  and Report ID, then loads the currentTD structure with the address of the
*  buffer and the size.  The caller has to decide if it is a control read or
*  control write.
*
* Parameters:
*  None.
*
* Return:
*  currentTD
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UART_FindReport(void) 
{
    const T_USB_UART_LUT CYCODE *pTmp;
    T_USB_UART_TD *pTD;
    uint8 interfaceN;
    uint8 reportType;

    /* `#START HID_FINDREPORT` Place custom handling here */

    /* `#END` */
    USB_UART_currentTD.count = 0u;   /* Init not supported condition */
    pTmp = USB_UART_GetConfigTablePtr(USB_UART_configuration - 1u);
    reportType = CY_GET_REG8(USB_UART_wValueHi);
    interfaceN = CY_GET_REG8(USB_UART_wIndexLo);
    /* Third entry in the LUT COnfiguration Table starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE*/
    pTmp = (const T_USB_UART_LUT CYCODE *) pTmp->p_list;
    if(interfaceN < USB_UART_MAX_INTERFACES_NUMBER)
    {
        /* Now use Alternate setting number */
        pTmp = &pTmp[USB_UART_interfaceSetting[interfaceN]];
        /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
        pTmp = (const T_USB_UART_LUT CYCODE *) pTmp->p_list;
        /* Validate reportType to comply with "7.2.1 Get_Report Request" */
        if((reportType >= USB_UART_HID_GET_REPORT_INPUT) &&
           (reportType <= USB_UART_HID_GET_REPORT_FEATURE))
        {
            /* Get the entry proper TD (IN, OUT or Feature Report Table)*/
            pTmp = &pTmp[reportType - 1u];
            reportType = CY_GET_REG8(USB_UART_wValueLo);    /* Get reportID */
            /* Validate table support by the HID descriptor, compare table count with reportID */
            if(pTmp->c >= reportType)
            {
                pTD = (T_USB_UART_TD *) pTmp->p_list;
                pTD = &pTD[reportType];                          /* select entry depend on report ID*/
                USB_UART_currentTD.pData = pTD->pData;   /* Buffer pointer */
                USB_UART_currentTD.count = pTD->count;   /* Buffer Size */
                USB_UART_currentTD.pStatusBlock = pTD->pStatusBlock;
            }
        }
    }
}


/*******************************************************************************
* Additional user functions supporting HID Requests
********************************************************************************/

/* `#START HID_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* End USB_UART_ENABLE_HID_CLASS */


/* [] END OF FILE */
