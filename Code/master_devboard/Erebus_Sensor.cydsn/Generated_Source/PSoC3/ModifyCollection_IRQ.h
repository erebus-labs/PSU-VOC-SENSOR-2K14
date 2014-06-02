/*******************************************************************************
* File Name: ModifyCollection_IRQ.h
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

#if !defined(CY_ISR_ModifyCollection_IRQ_H)
#define CY_ISR_ModifyCollection_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ModifyCollection_IRQ_Start(void) ;
void ModifyCollection_IRQ_StartEx(cyisraddress address) ;
void ModifyCollection_IRQ_Stop(void) ;

CY_ISR_PROTO(ModifyCollection_IRQ_Interrupt);

void ModifyCollection_IRQ_SetVector(cyisraddress address) ;
cyisraddress ModifyCollection_IRQ_GetVector(void) ;

void ModifyCollection_IRQ_SetPriority(uint8 priority) ;
uint8 ModifyCollection_IRQ_GetPriority(void) ;

void ModifyCollection_IRQ_Enable(void) ;
uint8 ModifyCollection_IRQ_GetState(void) ;
void ModifyCollection_IRQ_Disable(void) ;

void ModifyCollection_IRQ_SetPending(void) ;
void ModifyCollection_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ModifyCollection_IRQ ISR. */
#define ModifyCollection_IRQ_INTC_VECTOR            ((reg16 *) ModifyCollection_IRQ__INTC_VECT)

/* Address of the ModifyCollection_IRQ ISR priority. */
#define ModifyCollection_IRQ_INTC_PRIOR             ((reg8 *) ModifyCollection_IRQ__INTC_PRIOR_REG)

/* Priority of the ModifyCollection_IRQ interrupt. */
#define ModifyCollection_IRQ_INTC_PRIOR_NUMBER      ModifyCollection_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ModifyCollection_IRQ interrupt. */
#define ModifyCollection_IRQ_INTC_SET_EN            ((reg8 *) ModifyCollection_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ModifyCollection_IRQ interrupt. */
#define ModifyCollection_IRQ_INTC_CLR_EN            ((reg8 *) ModifyCollection_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ModifyCollection_IRQ interrupt state to pending. */
#define ModifyCollection_IRQ_INTC_SET_PD            ((reg8 *) ModifyCollection_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ModifyCollection_IRQ interrupt. */
#define ModifyCollection_IRQ_INTC_CLR_PD            ((reg8 *) ModifyCollection_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_ModifyCollection_IRQ_H */


/* [] END OF FILE */
