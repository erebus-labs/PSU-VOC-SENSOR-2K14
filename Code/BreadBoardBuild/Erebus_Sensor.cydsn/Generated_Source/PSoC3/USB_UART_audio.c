/*******************************************************************************
* File Name: USB_UART_audio.c
* Version 2.60
*
* Description:
*  USB AUDIO Class request handler.
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

#if defined(USB_UART_ENABLE_AUDIO_CLASS)

#include "USB_UART_audio.h"
#include "USB_UART_pvt.h"
#if defined(USB_UART_ENABLE_MIDI_STREAMING) 
    #include "USB_UART_midi.h"
#endif /* End USB_UART_ENABLE_MIDI_STREAMING*/


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)


/***************************************
*    AUDIO Variables
***************************************/

#if defined(USB_UART_ENABLE_AUDIO_STREAMING)
    volatile uint8 USB_UART_currentSampleFrequency[USB_UART_MAX_EP][USB_UART_SAMPLE_FREQ_LEN];
    volatile uint8 USB_UART_frequencyChanged;
    volatile uint8 USB_UART_currentMute;
    volatile uint8 USB_UART_currentVolume[USB_UART_VOLUME_LEN];
    volatile uint8 USB_UART_minimumVolume[USB_UART_VOLUME_LEN] = {USB_UART_VOL_MIN_LSB,
                                                                                  USB_UART_VOL_MIN_MSB};
    volatile uint8 USB_UART_maximumVolume[USB_UART_VOLUME_LEN] = {USB_UART_VOL_MAX_LSB,
                                                                                  USB_UART_VOL_MAX_MSB};
    volatile uint8 USB_UART_resolutionVolume[USB_UART_VOLUME_LEN] = {USB_UART_VOL_RES_LSB,
                                                                                     USB_UART_VOL_RES_MSB};
#endif /* End USB_UART_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: USB_UART_DispatchAUDIOClassRqst
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
* Global variables:
*   USB_UART_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   USB_UART_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       if((USB_UART_frequencyChanged != 0) &&
*       (USB_UART_transferState == USB_UART_TRANS_STATE_IDLE))
*       {
*          USB_UART_frequencyChanged = 0;
*       }
*       USB_UART_transferState variable is checked to be sure that
*             transfer completes.
*   USB_UART_currentMute: Contains mute configuration set by Host.
*   USB_UART_currentVolume: Contains volume level set by Host.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_UART_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = USB_UART_FALSE;

    #if defined(USB_UART_ENABLE_AUDIO_STREAMING)
        uint8 epNumber;
        epNumber = CY_GET_REG8(USB_UART_wIndexLo) & USB_UART_DIR_UNUSED;
    #endif /* End USB_UART_ENABLE_AUDIO_STREAMING */

    if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) == USB_UART_RQST_DIR_D2H)
    {
        /* Control Read */
        if((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_RCPT_MASK) == \
                                                                                    USB_UART_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(USB_UART_bRequest))
            {
                case USB_UART_GET_CUR:
                #if defined(USB_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* Endpoint Control Selector is Sampling Frequency */
                        USB_UART_currentTD.wCount = USB_UART_SAMPLE_FREQ_LEN;
                        USB_UART_currentTD.pData  = USB_UART_currentSampleFrequency[epNumber];
                        requestHandled   = USB_UART_InitControlRead();
                    }
                #endif /* End USB_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_RCPT_MASK) == \
                                                                                    USB_UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(USB_UART_bRequest))
            {
                case USB_UART_GET_CUR:
                #if defined(USB_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */
                        
                         /* Entity ID Control Selector is MUTE */
                        USB_UART_currentTD.wCount = 1u;
                        USB_UART_currentTD.pData  = &USB_UART_currentMute;
                        requestHandled   = USB_UART_InitControlRead();
                    }
                    else if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME, */
                        USB_UART_currentTD.wCount = USB_UART_VOLUME_LEN;
                        USB_UART_currentTD.pData  = USB_UART_currentVolume;
                        requestHandled   = USB_UART_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                    break;
                case USB_UART_GET_MIN:    /* GET_MIN */
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB_UART_currentTD.wCount = USB_UART_VOLUME_LEN;
                        USB_UART_currentTD.pData  = &USB_UART_minimumVolume[0];
                        requestHandled   = USB_UART_InitControlRead();
                    }
                    break;
                case USB_UART_GET_MAX:    /* GET_MAX */
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB_UART_currentTD.wCount = USB_UART_VOLUME_LEN;
                        USB_UART_currentTD.pData  = &USB_UART_maximumVolume[0];
                        requestHandled   = USB_UART_InitControlRead();
                    }
                    break;
                case USB_UART_GET_RES:    /* GET_RES */
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        USB_UART_currentTD.wCount = USB_UART_VOLUME_LEN;
                        USB_UART_currentTD.pData  = &USB_UART_resolutionVolume[0];
                        requestHandled   = USB_UART_InitControlRead();
                    }
                    break;
                /* The contents of the status message is reserved for future use.
                *  For the time being, a null packet should be returned in the data stage of the
                *  control transfer, and the received null packet should be ACKed.
                */
                case USB_UART_GET_STAT:
                        USB_UART_currentTD.wCount = 0u;
                        requestHandled   = USB_UART_InitControlWrite();

                #endif /* End USB_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* USB_UART_RQST_RCPT_OTHER */
        }
    }
    else if ((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_DIR_MASK) == \
                                                                                    USB_UART_RQST_DIR_H2D)
    {
        /* Control Write */
        if((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_RCPT_MASK) == \
                                                                                    USB_UART_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(USB_UART_bRequest))
            {
                case USB_UART_SET_CUR:
                #if defined(USB_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* Endpoint Control Selector is Sampling Frequency */
                        USB_UART_currentTD.wCount = USB_UART_SAMPLE_FREQ_LEN;
                        USB_UART_currentTD.pData  = USB_UART_currentSampleFrequency[epNumber];
                        requestHandled   = USB_UART_InitControlWrite();
                        USB_UART_frequencyChanged = epNumber;
                    }
                #endif /* End USB_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((CY_GET_REG8(USB_UART_bmRequestType) & USB_UART_RQST_RCPT_MASK) == \
                                                                                    USB_UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(USB_UART_bRequest))
            {
                case USB_UART_SET_CUR:
                #if defined(USB_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is MUTE */
                        USB_UART_currentTD.wCount = 1u;
                        USB_UART_currentTD.pData  = &USB_UART_currentMute;
                        requestHandled   = USB_UART_InitControlWrite();
                    }
                    else if(CY_GET_REG8(USB_UART_wValueHi) == USB_UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME */
                        USB_UART_currentTD.wCount = USB_UART_VOLUME_LEN;
                        USB_UART_currentTD.pData  = USB_UART_currentVolume;
                        requestHandled   = USB_UART_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                #endif /* End USB_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* USB_UART_RQST_RCPT_OTHER */
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


#endif /* USER_SUPPLIED_AUDIO_HANDLER */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* End USB_UART_ENABLE_AUDIO_CLASS*/


/* [] END OF FILE */
