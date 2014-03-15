/*******************************************************************************
* File Name: Vbus_IRQ.h
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

#if !defined(CY_ISR_Vbus_IRQ_H)
#define CY_ISR_Vbus_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Vbus_IRQ_Start(void) ;
void Vbus_IRQ_StartEx(cyisraddress address) ;
void Vbus_IRQ_Stop(void) ;

CY_ISR_PROTO(Vbus_IRQ_Interrupt);

void Vbus_IRQ_SetVector(cyisraddress address) ;
cyisraddress Vbus_IRQ_GetVector(void) ;

void Vbus_IRQ_SetPriority(uint8 priority) ;
uint8 Vbus_IRQ_GetPriority(void) ;

void Vbus_IRQ_Enable(void) ;
uint8 Vbus_IRQ_GetState(void) ;
void Vbus_IRQ_Disable(void) ;

void Vbus_IRQ_SetPending(void) ;
void Vbus_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Vbus_IRQ ISR. */
#define Vbus_IRQ_INTC_VECTOR            ((reg16 *) Vbus_IRQ__INTC_VECT)

/* Address of the Vbus_IRQ ISR priority. */
#define Vbus_IRQ_INTC_PRIOR             ((reg8 *) Vbus_IRQ__INTC_PRIOR_REG)

/* Priority of the Vbus_IRQ interrupt. */
#define Vbus_IRQ_INTC_PRIOR_NUMBER      Vbus_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Vbus_IRQ interrupt. */
#define Vbus_IRQ_INTC_SET_EN            ((reg8 *) Vbus_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Vbus_IRQ interrupt. */
#define Vbus_IRQ_INTC_CLR_EN            ((reg8 *) Vbus_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Vbus_IRQ interrupt state to pending. */
#define Vbus_IRQ_INTC_SET_PD            ((reg8 *) Vbus_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Vbus_IRQ interrupt. */
#define Vbus_IRQ_INTC_CLR_PD            ((reg8 *) Vbus_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_Vbus_IRQ_H */


/* [] END OF FILE */
