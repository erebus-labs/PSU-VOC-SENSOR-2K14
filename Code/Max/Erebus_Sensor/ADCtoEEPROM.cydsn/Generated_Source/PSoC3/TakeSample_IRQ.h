/*******************************************************************************
* File Name: TakeSample_IRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_TakeSample_IRQ_H)
#define CY_ISR_TakeSample_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TakeSample_IRQ_Start(void) ;
void TakeSample_IRQ_StartEx(cyisraddress address) ;
void TakeSample_IRQ_Stop(void) ;

CY_ISR_PROTO(TakeSample_IRQ_Interrupt);

void TakeSample_IRQ_SetVector(cyisraddress address) ;
cyisraddress TakeSample_IRQ_GetVector(void) ;

void TakeSample_IRQ_SetPriority(uint8 priority) ;
uint8 TakeSample_IRQ_GetPriority(void) ;

void TakeSample_IRQ_Enable(void) ;
uint8 TakeSample_IRQ_GetState(void) ;
void TakeSample_IRQ_Disable(void) ;

void TakeSample_IRQ_SetPending(void) ;
void TakeSample_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TakeSample_IRQ ISR. */
#define TakeSample_IRQ_INTC_VECTOR            ((reg16 *) TakeSample_IRQ__INTC_VECT)

/* Address of the TakeSample_IRQ ISR priority. */
#define TakeSample_IRQ_INTC_PRIOR             ((reg8 *) TakeSample_IRQ__INTC_PRIOR_REG)

/* Priority of the TakeSample_IRQ interrupt. */
#define TakeSample_IRQ_INTC_PRIOR_NUMBER      TakeSample_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TakeSample_IRQ interrupt. */
#define TakeSample_IRQ_INTC_SET_EN            ((reg8 *) TakeSample_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TakeSample_IRQ interrupt. */
#define TakeSample_IRQ_INTC_CLR_EN            ((reg8 *) TakeSample_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TakeSample_IRQ interrupt state to pending. */
#define TakeSample_IRQ_INTC_SET_PD            ((reg8 *) TakeSample_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TakeSample_IRQ interrupt. */
#define TakeSample_IRQ_INTC_CLR_PD            ((reg8 *) TakeSample_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_TakeSample_IRQ_H */


/* [] END OF FILE */
