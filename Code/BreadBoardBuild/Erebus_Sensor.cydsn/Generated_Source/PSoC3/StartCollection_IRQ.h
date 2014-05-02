/*******************************************************************************
* File Name: StartCollection_IRQ.h
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

#if !defined(CY_ISR_StartCollection_IRQ_H)
#define CY_ISR_StartCollection_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void StartCollection_IRQ_Start(void) ;
void StartCollection_IRQ_StartEx(cyisraddress address) ;
void StartCollection_IRQ_Stop(void) ;

CY_ISR_PROTO(StartCollection_IRQ_Interrupt);

void StartCollection_IRQ_SetVector(cyisraddress address) ;
cyisraddress StartCollection_IRQ_GetVector(void) ;

void StartCollection_IRQ_SetPriority(uint8 priority) ;
uint8 StartCollection_IRQ_GetPriority(void) ;

void StartCollection_IRQ_Enable(void) ;
uint8 StartCollection_IRQ_GetState(void) ;
void StartCollection_IRQ_Disable(void) ;

void StartCollection_IRQ_SetPending(void) ;
void StartCollection_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the StartCollection_IRQ ISR. */
#define StartCollection_IRQ_INTC_VECTOR            ((reg16 *) StartCollection_IRQ__INTC_VECT)

/* Address of the StartCollection_IRQ ISR priority. */
#define StartCollection_IRQ_INTC_PRIOR             ((reg8 *) StartCollection_IRQ__INTC_PRIOR_REG)

/* Priority of the StartCollection_IRQ interrupt. */
#define StartCollection_IRQ_INTC_PRIOR_NUMBER      StartCollection_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable StartCollection_IRQ interrupt. */
#define StartCollection_IRQ_INTC_SET_EN            ((reg8 *) StartCollection_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the StartCollection_IRQ interrupt. */
#define StartCollection_IRQ_INTC_CLR_EN            ((reg8 *) StartCollection_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the StartCollection_IRQ interrupt state to pending. */
#define StartCollection_IRQ_INTC_SET_PD            ((reg8 *) StartCollection_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the StartCollection_IRQ interrupt. */
#define StartCollection_IRQ_INTC_CLR_PD            ((reg8 *) StartCollection_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_StartCollection_IRQ_H */


/* [] END OF FILE */
