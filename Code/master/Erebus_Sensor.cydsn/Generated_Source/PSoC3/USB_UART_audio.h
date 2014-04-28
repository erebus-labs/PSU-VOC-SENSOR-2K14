/*******************************************************************************
* File Name: USB_UART_audio.h
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

#if !defined(CY_USBFS_USB_UART_audio_H)
#define CY_USBFS_USB_UART_audio_H

#include "cytypes.h"


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_CONSTANTS` Place your declaration here */

/* `#END` */


/***************************************
*  Constants for USB_UART_audio API.
***************************************/

/* Audio Class-Specific Request Codes (AUDIO Table A-9) */
#define USB_UART_REQUEST_CODE_UNDEFINED     (0x00u)
#define USB_UART_SET_CUR                    (0x01u)
#define USB_UART_GET_CUR                    (0x81u)
#define USB_UART_SET_MIN                    (0x02u)
#define USB_UART_GET_MIN                    (0x82u)
#define USB_UART_SET_MAX                    (0x03u)
#define USB_UART_GET_MAX                    (0x83u)
#define USB_UART_SET_RES                    (0x04u)
#define USB_UART_GET_RES                    (0x84u)
#define USB_UART_SET_MEM                    (0x05u)
#define USB_UART_GET_MEM                    (0x85u)
#define USB_UART_GET_STAT                   (0xFFu)

/* Endpoint Control Selectors (AUDIO Table A-19) */
#define USB_UART_EP_CONTROL_UNDEFINED       (0x00u)
#define USB_UART_SAMPLING_FREQ_CONTROL      (0x01u)
#define USB_UART_PITCH_CONTROL              (0x02u)

/* Feature Unit Control Selectors (AUDIO Table A-11) */
#define USB_UART_FU_CONTROL_UNDEFINED       (0x00u)
#define USB_UART_MUTE_CONTROL               (0x01u)
#define USB_UART_VOLUME_CONTROL             (0x02u)
#define USB_UART_BASS_CONTROL               (0x03u)
#define USB_UART_MID_CONTROL                (0x04u)
#define USB_UART_TREBLE_CONTROL             (0x05u)
#define USB_UART_GRAPHIC_EQUALIZER_CONTROL  (0x06u)
#define USB_UART_AUTOMATIC_GAIN_CONTROL     (0x07u)
#define USB_UART_DELAY_CONTROL              (0x08u)
#define USB_UART_BASS_BOOST_CONTROL         (0x09u)
#define USB_UART_LOUDNESS_CONTROL           (0x0Au)

#define USB_UART_SAMPLE_FREQ_LEN            (3u)
#define USB_UART_VOLUME_LEN                 (2u)

#if !defined(USER_SUPPLIED_DEFAULT_VOLUME_VALUE)
    #define USB_UART_VOL_MIN_MSB            (0x80u)
    #define USB_UART_VOL_MIN_LSB            (0x01u)
    #define USB_UART_VOL_MAX_MSB            (0x7Fu)
    #define USB_UART_VOL_MAX_LSB            (0xFFu)
    #define USB_UART_VOL_RES_MSB            (0x00u)
    #define USB_UART_VOL_RES_LSB            (0x01u)
#endif /* USER_SUPPLIED_DEFAULT_VOLUME_VALUE */


/***************************************
* External data references
***************************************/

extern volatile uint8 USB_UART_currentSampleFrequency[USB_UART_MAX_EP]
                                                             [USB_UART_SAMPLE_FREQ_LEN];
extern volatile uint8 USB_UART_frequencyChanged;
extern volatile uint8 USB_UART_currentMute;
extern volatile uint8 USB_UART_currentVolume[USB_UART_VOLUME_LEN];
extern volatile uint8 USB_UART_minimumVolume[USB_UART_VOLUME_LEN];
extern volatile uint8 USB_UART_maximumVolume[USB_UART_VOLUME_LEN];
extern volatile uint8 USB_UART_resolutionVolume[USB_UART_VOLUME_LEN];

#endif /* End CY_USBFS_USB_UART_audio_H */


/* [] END OF FILE */
