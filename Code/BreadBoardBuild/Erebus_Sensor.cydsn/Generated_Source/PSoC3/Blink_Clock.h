/*******************************************************************************
* File Name: Blink_Clock.h
* Version 2.10
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Blink_Clock_H)
#define CY_CLOCK_Blink_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Blink_Clock_Start(void) ;
void Blink_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Blink_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Blink_Clock_StandbyPower(uint8 state) ;
void Blink_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Blink_Clock_GetDividerRegister(void) ;
void Blink_Clock_SetModeRegister(uint8 modeBitMask) ;
void Blink_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 Blink_Clock_GetModeRegister(void) ;
void Blink_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 Blink_Clock_GetSourceRegister(void) ;
#if defined(Blink_Clock__CFG3)
void Blink_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 Blink_Clock_GetPhaseRegister(void) ;
#endif /* defined(Blink_Clock__CFG3) */

#define Blink_Clock_Enable()                       Blink_Clock_Start()
#define Blink_Clock_Disable()                      Blink_Clock_Stop()
#define Blink_Clock_SetDivider(clkDivider)         Blink_Clock_SetDividerRegister(clkDivider, 1u)
#define Blink_Clock_SetDividerValue(clkDivider)    Blink_Clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define Blink_Clock_SetMode(clkMode)               Blink_Clock_SetModeRegister(clkMode)
#define Blink_Clock_SetSource(clkSource)           Blink_Clock_SetSourceRegister(clkSource)
#if defined(Blink_Clock__CFG3)
#define Blink_Clock_SetPhase(clkPhase)             Blink_Clock_SetPhaseRegister(clkPhase)
#define Blink_Clock_SetPhaseValue(clkPhase)        Blink_Clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Blink_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Blink_Clock_CLKEN              (* (reg8 *) Blink_Clock__PM_ACT_CFG)
#define Blink_Clock_CLKEN_PTR          ((reg8 *) Blink_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Blink_Clock_CLKSTBY            (* (reg8 *) Blink_Clock__PM_STBY_CFG)
#define Blink_Clock_CLKSTBY_PTR        ((reg8 *) Blink_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Blink_Clock_DIV_LSB            (* (reg8 *) Blink_Clock__CFG0)
#define Blink_Clock_DIV_LSB_PTR        ((reg8 *) Blink_Clock__CFG0)
#define Blink_Clock_DIV_PTR            ((reg16 *) Blink_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define Blink_Clock_DIV_MSB            (* (reg8 *) Blink_Clock__CFG1)
#define Blink_Clock_DIV_MSB_PTR        ((reg8 *) Blink_Clock__CFG1)

/* Mode and source configuration register */
#define Blink_Clock_MOD_SRC            (* (reg8 *) Blink_Clock__CFG2)
#define Blink_Clock_MOD_SRC_PTR        ((reg8 *) Blink_Clock__CFG2)

#if defined(Blink_Clock__CFG3)
/* Analog clock phase configuration register */
#define Blink_Clock_PHASE              (* (reg8 *) Blink_Clock__CFG3)
#define Blink_Clock_PHASE_PTR          ((reg8 *) Blink_Clock__CFG3)
#endif /* defined(Blink_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Blink_Clock_CLKEN_MASK         Blink_Clock__PM_ACT_MSK
#define Blink_Clock_CLKSTBY_MASK       Blink_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define Blink_Clock_SRC_SEL_MSK        Blink_Clock__CFG2_SRC_SEL_MASK
#define Blink_Clock_MODE_MASK          (~(Blink_Clock_SRC_SEL_MSK))

#if defined(Blink_Clock__CFG3)
/* CFG3 phase mask */
#define Blink_Clock_PHASE_MASK         Blink_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(Blink_Clock__CFG3) */

#endif /* CY_CLOCK_Blink_Clock_H */


/* [] END OF FILE */
