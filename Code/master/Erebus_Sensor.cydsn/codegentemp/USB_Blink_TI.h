/*******************************************************************************
* File Name: USB_Blink_TI.h
* Version 2.50
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_30_USB_Blink_TI_H)
#define CY_Timer_v2_30_USB_Blink_TI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 USB_Blink_TI_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define USB_Blink_TI_Resolution                 16u
#define USB_Blink_TI_UsingFixedFunction         0u
#define USB_Blink_TI_UsingHWCaptureCounter      0u
#define USB_Blink_TI_SoftwareCaptureMode        0u
#define USB_Blink_TI_SoftwareTriggerMode        0u
#define USB_Blink_TI_UsingHWEnable              0u
#define USB_Blink_TI_EnableTriggerMode          0u
#define USB_Blink_TI_InterruptOnCaptureCount    0u
#define USB_Blink_TI_RunModeUsed                0u
#define USB_Blink_TI_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!USB_Blink_TI_UsingFixedFunction)
        #if (CY_UDB_V0)
            uint16 TimerUdb;                 /* Timer internal counter value */
            uint16 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (USB_Blink_TI_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in CY_UDB_V0 */

        #if (CY_UDB_V1)
            uint16 TimerUdb;
            uint8 InterruptMaskValue;
            #if (USB_Blink_TI_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */
        #endif /* (CY_UDB_V1) */

        #if (!USB_Blink_TI_ControlRegRemoved)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}USB_Blink_TI_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    USB_Blink_TI_Start(void) ;
void    USB_Blink_TI_Stop(void) ;

void    USB_Blink_TI_SetInterruptMode(uint8 interruptMode) ;
uint8   USB_Blink_TI_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define USB_Blink_TI_GetInterruptSource() USB_Blink_TI_ReadStatusRegister()

#if(!USB_Blink_TI_ControlRegRemoved)
    uint8   USB_Blink_TI_ReadControlRegister(void) ;
    void    USB_Blink_TI_WriteControlRegister(uint8 control) \
        ;
#endif /* (!USB_Blink_TI_ControlRegRemoved) */

uint16  USB_Blink_TI_ReadPeriod(void) ;
void    USB_Blink_TI_WritePeriod(uint16 period) \
    ;
uint16  USB_Blink_TI_ReadCounter(void) ;
void    USB_Blink_TI_WriteCounter(uint16 counter) \
    ;
uint16  USB_Blink_TI_ReadCapture(void) ;
void    USB_Blink_TI_SoftwareCapture(void) ;


#if(!USB_Blink_TI_UsingFixedFunction) /* UDB Prototypes */
    #if (USB_Blink_TI_SoftwareCaptureMode)
        void    USB_Blink_TI_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!USB_Blink_TI_UsingFixedFunction) */

    #if (USB_Blink_TI_SoftwareTriggerMode)
        void    USB_Blink_TI_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (USB_Blink_TI_SoftwareTriggerMode) */
    #if (USB_Blink_TI_EnableTriggerMode)
        void    USB_Blink_TI_EnableTrigger(void) ;
        void    USB_Blink_TI_DisableTrigger(void) ;
    #endif /* (USB_Blink_TI_EnableTriggerMode) */

    #if(USB_Blink_TI_InterruptOnCaptureCount)
        #if(!USB_Blink_TI_ControlRegRemoved)
            void    USB_Blink_TI_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!USB_Blink_TI_ControlRegRemoved) */
    #endif /* (USB_Blink_TI_InterruptOnCaptureCount) */

    #if (USB_Blink_TI_UsingHWCaptureCounter)
        void    USB_Blink_TI_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   USB_Blink_TI_ReadCaptureCount(void) ;
    #endif /* (USB_Blink_TI_UsingHWCaptureCounter) */

    void USB_Blink_TI_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void USB_Blink_TI_Init(void)          ;
void USB_Blink_TI_Enable(void)        ;
void USB_Blink_TI_SaveConfig(void)    ;
void USB_Blink_TI_RestoreConfig(void) ;
void USB_Blink_TI_Sleep(void)         ;
void USB_Blink_TI_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define USB_Blink_TI__B_TIMER__CM_NONE 0
#define USB_Blink_TI__B_TIMER__CM_RISINGEDGE 1
#define USB_Blink_TI__B_TIMER__CM_FALLINGEDGE 2
#define USB_Blink_TI__B_TIMER__CM_EITHEREDGE 3
#define USB_Blink_TI__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define USB_Blink_TI__B_TIMER__TM_NONE 0x00u
#define USB_Blink_TI__B_TIMER__TM_RISINGEDGE 0x04u
#define USB_Blink_TI__B_TIMER__TM_FALLINGEDGE 0x08u
#define USB_Blink_TI__B_TIMER__TM_EITHEREDGE 0x0Cu
#define USB_Blink_TI__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define USB_Blink_TI_INIT_PERIOD             499u
#define USB_Blink_TI_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << USB_Blink_TI_CTRL_CAP_MODE_SHIFT))
#define USB_Blink_TI_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << USB_Blink_TI_CTRL_TRIG_MODE_SHIFT))
#if (USB_Blink_TI_UsingFixedFunction)
    #define USB_Blink_TI_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << USB_Blink_TI_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << USB_Blink_TI_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define USB_Blink_TI_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << USB_Blink_TI_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << USB_Blink_TI_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << USB_Blink_TI_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (USB_Blink_TI_UsingFixedFunction) */
#define USB_Blink_TI_INIT_CAPTURE_COUNT      (2u)
#define USB_Blink_TI_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << USB_Blink_TI_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (USB_Blink_TI_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define USB_Blink_TI_STATUS         (*(reg8 *) USB_Blink_TI_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define USB_Blink_TI_STATUS_MASK    (*(reg8 *) USB_Blink_TI_TimerHW__SR0 )
    #define USB_Blink_TI_CONTROL        (*(reg8 *) USB_Blink_TI_TimerHW__CFG0)
    #define USB_Blink_TI_CONTROL2       (*(reg8 *) USB_Blink_TI_TimerHW__CFG1)
    #define USB_Blink_TI_CONTROL2_PTR   ( (reg8 *) USB_Blink_TI_TimerHW__CFG1)
    #define USB_Blink_TI_RT1            (*(reg8 *) USB_Blink_TI_TimerHW__RT1)
    #define USB_Blink_TI_RT1_PTR        ( (reg8 *) USB_Blink_TI_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define USB_Blink_TI_CONTROL3       (*(reg8 *) USB_Blink_TI_TimerHW__CFG2)
        #define USB_Blink_TI_CONTROL3_PTR   ( (reg8 *) USB_Blink_TI_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define USB_Blink_TI_GLOBAL_ENABLE  (*(reg8 *) USB_Blink_TI_TimerHW__PM_ACT_CFG)
    #define USB_Blink_TI_GLOBAL_STBY_ENABLE  (*(reg8 *) USB_Blink_TI_TimerHW__PM_STBY_CFG)

    #define USB_Blink_TI_CAPTURE_LSB         (* (reg16 *) USB_Blink_TI_TimerHW__CAP0 )
    #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg16 *) USB_Blink_TI_TimerHW__CAP0 )
    #define USB_Blink_TI_PERIOD_LSB          (* (reg16 *) USB_Blink_TI_TimerHW__PER0 )
    #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg16 *) USB_Blink_TI_TimerHW__PER0 )
    #define USB_Blink_TI_COUNTER_LSB         (* (reg16 *) USB_Blink_TI_TimerHW__CNT_CMP0 )
    #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg16 *) USB_Blink_TI_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define USB_Blink_TI_BLOCK_EN_MASK                     USB_Blink_TI_TimerHW__PM_ACT_MSK
    #define USB_Blink_TI_BLOCK_STBY_EN_MASK                USB_Blink_TI_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define USB_Blink_TI_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define USB_Blink_TI_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define USB_Blink_TI_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define USB_Blink_TI_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define USB_Blink_TI_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define USB_Blink_TI_CTRL_ENABLE                        ((uint8)((uint8)0x01u << USB_Blink_TI_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define USB_Blink_TI_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define USB_Blink_TI_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << USB_Blink_TI_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define USB_Blink_TI_CTRL_MODE_SHIFT                     0x01u
        #define USB_Blink_TI_CTRL_MODE_MASK                     ((uint8)((uint8)0x07u << USB_Blink_TI_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define USB_Blink_TI_CTRL_RCOD_SHIFT        0x02u
        #define USB_Blink_TI_CTRL_ENBL_SHIFT        0x00u
        #define USB_Blink_TI_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define USB_Blink_TI_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << USB_Blink_TI_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define USB_Blink_TI_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << USB_Blink_TI_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define USB_Blink_TI_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << USB_Blink_TI_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define USB_Blink_TI_CTRL_RCOD       ((uint8)((uint8)0x03u << USB_Blink_TI_CTRL_RCOD_SHIFT))
        #define USB_Blink_TI_CTRL_ENBL       ((uint8)((uint8)0x80u << USB_Blink_TI_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define USB_Blink_TI_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define USB_Blink_TI_RT1_MASK                        ((uint8)((uint8)0x03u << USB_Blink_TI_RT1_SHIFT))
    #define USB_Blink_TI_SYNC                            ((uint8)((uint8)0x03u << USB_Blink_TI_RT1_SHIFT))
    #define USB_Blink_TI_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define USB_Blink_TI_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << USB_Blink_TI_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define USB_Blink_TI_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << USB_Blink_TI_SYNCDSI_SHIFT))

    #define USB_Blink_TI_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << USB_Blink_TI_CTRL_MODE_SHIFT))
    #define USB_Blink_TI_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << USB_Blink_TI_CTRL_MODE_SHIFT))
    #define USB_Blink_TI_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << USB_Blink_TI_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define USB_Blink_TI_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define USB_Blink_TI_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define USB_Blink_TI_STATUS_TC_INT_MASK_SHIFT        (USB_Blink_TI_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define USB_Blink_TI_STATUS_CAPTURE_INT_MASK_SHIFT   (USB_Blink_TI_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define USB_Blink_TI_STATUS_TC                       ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_TC_SHIFT))
    #define USB_Blink_TI_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define USB_Blink_TI_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define USB_Blink_TI_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define USB_Blink_TI_STATUS              (* (reg8 *) USB_Blink_TI_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define USB_Blink_TI_STATUS_MASK         (* (reg8 *) USB_Blink_TI_TimerUDB_rstSts_stsreg__MASK_REG)
    #define USB_Blink_TI_STATUS_AUX_CTRL     (* (reg8 *) USB_Blink_TI_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define USB_Blink_TI_CONTROL             (* (reg8 *) USB_Blink_TI_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(USB_Blink_TI_Resolution <= 8u) /* 8-bit Timer */
        #define USB_Blink_TI_CAPTURE_LSB         (* (reg8 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg8 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define USB_Blink_TI_PERIOD_LSB          (* (reg8 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg8 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define USB_Blink_TI_COUNTER_LSB         (* (reg8 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg8 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(USB_Blink_TI_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define USB_Blink_TI_CAPTURE_LSB         (* (reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define USB_Blink_TI_PERIOD_LSB          (* (reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define USB_Blink_TI_COUNTER_LSB         (* (reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define USB_Blink_TI_CAPTURE_LSB         (* (reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define USB_Blink_TI_PERIOD_LSB          (* (reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define USB_Blink_TI_COUNTER_LSB         (* (reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg16 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(USB_Blink_TI_Resolution <= 24u)/* 24-bit Timer */
        #define USB_Blink_TI_CAPTURE_LSB         (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define USB_Blink_TI_PERIOD_LSB          (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define USB_Blink_TI_COUNTER_LSB         (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define USB_Blink_TI_CAPTURE_LSB         (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define USB_Blink_TI_PERIOD_LSB          (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define USB_Blink_TI_COUNTER_LSB         (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define USB_Blink_TI_CAPTURE_LSB         (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define USB_Blink_TI_CAPTURE_LSB_PTR       ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define USB_Blink_TI_PERIOD_LSB          (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define USB_Blink_TI_PERIOD_LSB_PTR        ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define USB_Blink_TI_COUNTER_LSB         (* (reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define USB_Blink_TI_COUNTER_LSB_PTR       ((reg32 *) USB_Blink_TI_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #if (USB_Blink_TI_UsingHWCaptureCounter)
        #define USB_Blink_TI_CAP_COUNT              (*(reg8 *) USB_Blink_TI_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define USB_Blink_TI_CAP_COUNT_PTR          ( (reg8 *) USB_Blink_TI_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define USB_Blink_TI_CAPTURE_COUNT_CTRL     (*(reg8 *) USB_Blink_TI_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define USB_Blink_TI_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) USB_Blink_TI_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (USB_Blink_TI_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define USB_Blink_TI_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define USB_Blink_TI_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define USB_Blink_TI_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define USB_Blink_TI_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define USB_Blink_TI_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define USB_Blink_TI_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << USB_Blink_TI_CTRL_INTCNT_SHIFT))
    #define USB_Blink_TI_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << USB_Blink_TI_CTRL_TRIG_MODE_SHIFT))
    #define USB_Blink_TI_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << USB_Blink_TI_CTRL_TRIG_EN_SHIFT))
    #define USB_Blink_TI_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << USB_Blink_TI_CTRL_CAP_MODE_SHIFT))
    #define USB_Blink_TI_CTRL_ENABLE                    ((uint8)((uint8)0x01u << USB_Blink_TI_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define USB_Blink_TI_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define USB_Blink_TI_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define USB_Blink_TI_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define USB_Blink_TI_STATUS_TC_INT_MASK_SHIFT       USB_Blink_TI_STATUS_TC_SHIFT
    #define USB_Blink_TI_STATUS_CAPTURE_INT_MASK_SHIFT  USB_Blink_TI_STATUS_CAPTURE_SHIFT
    #define USB_Blink_TI_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define USB_Blink_TI_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define USB_Blink_TI_STATUS_FIFOFULL_INT_MASK_SHIFT USB_Blink_TI_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define USB_Blink_TI_STATUS_TC                      ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define USB_Blink_TI_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define USB_Blink_TI_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define USB_Blink_TI_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define USB_Blink_TI_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define USB_Blink_TI_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define USB_Blink_TI_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << USB_Blink_TI_STATUS_FIFOFULL_SHIFT))

    #define USB_Blink_TI_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define USB_Blink_TI_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define USB_Blink_TI_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define USB_Blink_TI_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define USB_Blink_TI_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define USB_Blink_TI_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_USB_Blink_TI_H */


/* [] END OF FILE */
