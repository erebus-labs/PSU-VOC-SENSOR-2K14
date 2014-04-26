/*******************************************************************************
* File Name: StopCollection_IRQ.h
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

#if !defined(CY_ISR_StopCollection_IRQ_H)
#define CY_ISR_StopCollection_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void StopCollection_IRQ_Start(void) ;
void StopCollection_IRQ_StartEx(cyisraddress address) ;
void StopCollection_IRQ_Stop(void) ;

CY_ISR_PROTO(StopCollection_IRQ_Interrupt);

void StopCollection_IRQ_SetVector(cyisraddress address) ;
cyisraddress StopCollection_IRQ_GetVector(void) ;

void StopCollection_IRQ_SetPriority(uint8 priority) ;
uint8 StopCollection_IRQ_GetPriority(void) ;

void StopCollection_IRQ_Enable(void) ;
uint8 StopCollection_IRQ_GetState(void) ;
void StopCollection_IRQ_Disable(void) ;

void StopCollection_IRQ_SetPending(void) ;
void StopCollection_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the StopCollection_IRQ ISR. */
#define StopCollection_IRQ_INTC_VECTOR            ((reg16 *) StopCollection_IRQ__INTC_VECT)

/* Address of the StopCollection_IRQ ISR priority. */
#define StopCollection_IRQ_INTC_PRIOR             ((reg8 *) StopCollection_IRQ__INTC_PRIOR_REG)

/* Priority of the StopCollection_IRQ interrupt. */
#define StopCollection_IRQ_INTC_PRIOR_NUMBER      StopCollection_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable StopCollection_IRQ interrupt. */
#define StopCollection_IRQ_INTC_SET_EN            ((reg8 *) StopCollection_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the StopCollection_IRQ interrupt. */
#define StopCollection_IRQ_INTC_CLR_EN            ((reg8 *) StopCollection_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the StopCollection_IRQ interrupt state to pending. */
#define StopCollection_IRQ_INTC_SET_PD            ((reg8 *) StopCollection_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the StopCollection_IRQ interrupt. */
#define StopCollection_IRQ_INTC_CLR_PD            ((reg8 *) StopCollection_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_StopCollection_IRQ_H */


/* [] END OF FILE */
