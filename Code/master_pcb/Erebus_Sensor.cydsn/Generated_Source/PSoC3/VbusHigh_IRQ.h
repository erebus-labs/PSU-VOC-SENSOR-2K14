/*******************************************************************************
* File Name: VbusHigh_IRQ.h
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

#if !defined(CY_ISR_VbusHigh_IRQ_H)
#define CY_ISR_VbusHigh_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void VbusHigh_IRQ_Start(void) ;
void VbusHigh_IRQ_StartEx(cyisraddress address) ;
void VbusHigh_IRQ_Stop(void) ;

CY_ISR_PROTO(VbusHigh_IRQ_Interrupt);

void VbusHigh_IRQ_SetVector(cyisraddress address) ;
cyisraddress VbusHigh_IRQ_GetVector(void) ;

void VbusHigh_IRQ_SetPriority(uint8 priority) ;
uint8 VbusHigh_IRQ_GetPriority(void) ;

void VbusHigh_IRQ_Enable(void) ;
uint8 VbusHigh_IRQ_GetState(void) ;
void VbusHigh_IRQ_Disable(void) ;

void VbusHigh_IRQ_SetPending(void) ;
void VbusHigh_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the VbusHigh_IRQ ISR. */
#define VbusHigh_IRQ_INTC_VECTOR            ((reg16 *) VbusHigh_IRQ__INTC_VECT)

/* Address of the VbusHigh_IRQ ISR priority. */
#define VbusHigh_IRQ_INTC_PRIOR             ((reg8 *) VbusHigh_IRQ__INTC_PRIOR_REG)

/* Priority of the VbusHigh_IRQ interrupt. */
#define VbusHigh_IRQ_INTC_PRIOR_NUMBER      VbusHigh_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable VbusHigh_IRQ interrupt. */
#define VbusHigh_IRQ_INTC_SET_EN            ((reg8 *) VbusHigh_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the VbusHigh_IRQ interrupt. */
#define VbusHigh_IRQ_INTC_CLR_EN            ((reg8 *) VbusHigh_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the VbusHigh_IRQ interrupt state to pending. */
#define VbusHigh_IRQ_INTC_SET_PD            ((reg8 *) VbusHigh_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the VbusHigh_IRQ interrupt. */
#define VbusHigh_IRQ_INTC_CLR_PD            ((reg8 *) VbusHigh_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_VbusHigh_IRQ_H */


/* [] END OF FILE */
