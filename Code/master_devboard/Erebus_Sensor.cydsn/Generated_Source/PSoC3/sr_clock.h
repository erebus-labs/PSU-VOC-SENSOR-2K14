/*******************************************************************************
* File Name: sr_clock.h
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

#if !defined(CY_CLOCK_sr_clock_H)
#define CY_CLOCK_sr_clock_H

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

void sr_clock_Start(void) ;
void sr_clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void sr_clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void sr_clock_StandbyPower(uint8 state) ;
void sr_clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 sr_clock_GetDividerRegister(void) ;
void sr_clock_SetModeRegister(uint8 modeBitMask) ;
void sr_clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 sr_clock_GetModeRegister(void) ;
void sr_clock_SetSourceRegister(uint8 clkSource) ;
uint8 sr_clock_GetSourceRegister(void) ;
#if defined(sr_clock__CFG3)
void sr_clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 sr_clock_GetPhaseRegister(void) ;
#endif /* defined(sr_clock__CFG3) */

#define sr_clock_Enable()                       sr_clock_Start()
#define sr_clock_Disable()                      sr_clock_Stop()
#define sr_clock_SetDivider(clkDivider)         sr_clock_SetDividerRegister(clkDivider, 1u)
#define sr_clock_SetDividerValue(clkDivider)    sr_clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define sr_clock_SetMode(clkMode)               sr_clock_SetModeRegister(clkMode)
#define sr_clock_SetSource(clkSource)           sr_clock_SetSourceRegister(clkSource)
#if defined(sr_clock__CFG3)
#define sr_clock_SetPhase(clkPhase)             sr_clock_SetPhaseRegister(clkPhase)
#define sr_clock_SetPhaseValue(clkPhase)        sr_clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(sr_clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define sr_clock_CLKEN              (* (reg8 *) sr_clock__PM_ACT_CFG)
#define sr_clock_CLKEN_PTR          ((reg8 *) sr_clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define sr_clock_CLKSTBY            (* (reg8 *) sr_clock__PM_STBY_CFG)
#define sr_clock_CLKSTBY_PTR        ((reg8 *) sr_clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define sr_clock_DIV_LSB            (* (reg8 *) sr_clock__CFG0)
#define sr_clock_DIV_LSB_PTR        ((reg8 *) sr_clock__CFG0)
#define sr_clock_DIV_PTR            ((reg16 *) sr_clock__CFG0)

/* Clock MSB divider configuration register. */
#define sr_clock_DIV_MSB            (* (reg8 *) sr_clock__CFG1)
#define sr_clock_DIV_MSB_PTR        ((reg8 *) sr_clock__CFG1)

/* Mode and source configuration register */
#define sr_clock_MOD_SRC            (* (reg8 *) sr_clock__CFG2)
#define sr_clock_MOD_SRC_PTR        ((reg8 *) sr_clock__CFG2)

#if defined(sr_clock__CFG3)
/* Analog clock phase configuration register */
#define sr_clock_PHASE              (* (reg8 *) sr_clock__CFG3)
#define sr_clock_PHASE_PTR          ((reg8 *) sr_clock__CFG3)
#endif /* defined(sr_clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define sr_clock_CLKEN_MASK         sr_clock__PM_ACT_MSK
#define sr_clock_CLKSTBY_MASK       sr_clock__PM_STBY_MSK

/* CFG2 field masks */
#define sr_clock_SRC_SEL_MSK        sr_clock__CFG2_SRC_SEL_MASK
#define sr_clock_MODE_MASK          (~(sr_clock_SRC_SEL_MSK))

#if defined(sr_clock__CFG3)
/* CFG3 phase mask */
#define sr_clock_PHASE_MASK         sr_clock__CFG3_PHASE_DLY_MASK
#endif /* defined(sr_clock__CFG3) */

#endif /* CY_CLOCK_sr_clock_H */


/* [] END OF FILE */
