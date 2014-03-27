/*******************************************************************************
* File Name: .h
* Version 2.60
*
* Description:
*  This private file provides constants and parameter values for the
*  USBFS Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USB_UART_pvt_H)
#define CY_USBFS_USB_UART_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
extern const uint8 CYCODE USB_UART_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USB_UART_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_USB_UART_EP_SETTINGS_BLOCK CYCODE USB_UART_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE USB_UART_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_USB_UART_LUT CYCODE USB_UART_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_USB_UART_LUT CYCODE USB_UART_DEVICE0_TABLE[2u];
extern const T_USB_UART_LUT CYCODE USB_UART_TABLE[1u];
extern const uint8 CYCODE USB_UART_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USB_UART_STRING_DESCRIPTORS[69u];


extern const uint8 CYCODE USB_UART_MSOS_DESCRIPTOR[USB_UART_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USB_UART_MSOS_CONFIGURATION_DESCR[USB_UART_MSOS_CONF_DESCR_LENGTH];
#if defined(USB_UART_ENABLE_IDSN_STRING)
    extern uint8 USB_UART_idSerialNumberStringDescriptor[USB_UART_IDSN_DESCR_LENGTH];
#endif /* USB_UART_ENABLE_IDSN_STRING */

extern volatile uint8 USB_UART_interfaceNumber;
extern volatile uint8 USB_UART_interfaceSetting[USB_UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB_UART_interfaceSetting_last[USB_UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB_UART_deviceAddress;
extern volatile uint8 USB_UART_interfaceStatus[USB_UART_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USB_UART_interfaceClass;

extern volatile T_USB_UART_EP_CTL_BLOCK USB_UART_EP[USB_UART_MAX_EP];
extern volatile T_USB_UART_TD USB_UART_currentTD;

#if(USB_UART_EP_MM != USB_UART__EP_MANUAL)
    extern uint8 USB_UART_DmaChan[USB_UART_MAX_EP];
    extern uint8 USB_UART_DmaTd[USB_UART_MAX_EP];
#endif /* End USB_UART_EP_MM */

extern volatile uint8 USB_UART_ep0Toggle;
extern volatile uint8 USB_UART_lastPacketSize;
extern volatile uint8 USB_UART_ep0Mode;
extern volatile uint8 USB_UART_ep0Count;
extern volatile uint16 USB_UART_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USB_UART_ReInitComponent(void) ;
void  USB_UART_HandleSetup(void) ;
void  USB_UART_HandleIN(void) ;
void  USB_UART_HandleOUT(void) ;
void  USB_UART_LoadEP0(void) ;
uint8 USB_UART_InitControlRead(void) ;
uint8 USB_UART_InitControlWrite(void) ;
void  USB_UART_ControlReadDataStage(void) ;
void  USB_UART_ControlReadStatusStage(void) ;
void  USB_UART_ControlReadPrematureStatus(void)
                                                ;
uint8 USB_UART_InitControlWrite(void) ;
uint8 USB_UART_InitZeroLengthControlTransfer(void)
                                                ;
void  USB_UART_ControlWriteDataStage(void) ;
void  USB_UART_ControlWriteStatusStage(void) ;
void  USB_UART_ControlWritePrematureStatus(void)
                                                ;
uint8 USB_UART_InitNoDataControlTransfer(void) ;
void  USB_UART_NoDataControlStatusStage(void) ;
void  USB_UART_InitializeStatusBlock(void) ;
void  USB_UART_UpdateStatusBlock(uint8 completionCode) ;
uint8 USB_UART_DispatchClassRqst(void) ;

void USB_UART_Config(uint8 clearAltSetting) ;
void USB_UART_ConfigAltChanged(void) ;
void USB_UART_ConfigReg(void) ;

const T_USB_UART_LUT CYCODE *USB_UART_GetConfigTablePtr(uint8 c)
                                                            ;
const T_USB_UART_LUT CYCODE *USB_UART_GetDeviceTablePtr(void)
                                                            ;
const uint8 CYCODE *USB_UART_GetInterfaceClassTablePtr(void)
                                                    ;
uint8 USB_UART_ClearEndpointHalt(void) ;
uint8 USB_UART_SetEndpointHalt(void) ;
uint8 USB_UART_ValidateAlternateSetting(void) ;

void USB_UART_SaveConfig(void) ;
void USB_UART_RestoreConfig(void) ;

#if defined(USB_UART_ENABLE_IDSN_STRING)
    void USB_UART_ReadDieID(uint8 descr[]) ;
#endif /* USB_UART_ENABLE_IDSN_STRING */

#if defined(USB_UART_ENABLE_HID_CLASS)
    uint8 USB_UART_DispatchHIDClassRqst(void);
#endif /* End USB_UART_ENABLE_HID_CLASS */
#if defined(USB_UART_ENABLE_AUDIO_CLASS)
    uint8 USB_UART_DispatchAUDIOClassRqst(void);
#endif /* End USB_UART_ENABLE_HID_CLASS */
#if defined(USB_UART_ENABLE_CDC_CLASS)
    uint8 USB_UART_DispatchCDCClassRqst(void);
#endif /* End USB_UART_ENABLE_CDC_CLASS */

CY_ISR_PROTO(USB_UART_EP_0_ISR);
#if(USB_UART_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_1_ISR);
#endif /* End USB_UART_EP1_ISR_REMOVE */
#if(USB_UART_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_2_ISR);
#endif /* End USB_UART_EP2_ISR_REMOVE */
#if(USB_UART_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_3_ISR);
#endif /* End USB_UART_EP3_ISR_REMOVE */
#if(USB_UART_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_4_ISR);
#endif /* End USB_UART_EP4_ISR_REMOVE */
#if(USB_UART_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_5_ISR);
#endif /* End USB_UART_EP5_ISR_REMOVE */
#if(USB_UART_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_6_ISR);
#endif /* End USB_UART_EP6_ISR_REMOVE */
#if(USB_UART_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_7_ISR);
#endif /* End USB_UART_EP7_ISR_REMOVE */
#if(USB_UART_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_EP_8_ISR);
#endif /* End USB_UART_EP8_ISR_REMOVE */
CY_ISR_PROTO(USB_UART_BUS_RESET_ISR);
#if(USB_UART_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_SOF_ISR);
#endif /* End USB_UART_SOF_ISR_REMOVE */
#if(USB_UART_EP_MM != USB_UART__EP_MANUAL)
    CY_ISR_PROTO(USB_UART_ARB_ISR);
#endif /* End USB_UART_EP_MM */
#if(USB_UART_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_UART_DP_ISR);
#endif /* End USB_UART_DP_ISR_REMOVE */


/***************************************
* Request Handlers
***************************************/

uint8 USB_UART_HandleStandardRqst(void) ;
uint8 USB_UART_DispatchClassRqst(void) ;
uint8 USB_UART_HandleVendorRqst(void) ;


/***************************************
*    HID Internal references
***************************************/
#if defined(USB_UART_ENABLE_HID_CLASS)
    void USB_UART_FindReport(void) ;
    void USB_UART_FindReportDescriptor(void) ;
    void USB_UART_FindHidClassDecriptor(void) ;
#endif /* USB_UART_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/
#if defined(USB_UART_ENABLE_MIDI_STREAMING)
    void USB_UART_MIDI_IN_EP_Service(void) ;
#endif /* USB_UART_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_USB_UART_pvt_H */


/* [] END OF FILE */
