/*******************************************************************************
* File Name: VbusLow_IRQ.h
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

#if !defined(CY_ISR_VbusLow_IRQ_H)
#define CY_ISR_VbusLow_IRQ_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void VbusLow_IRQ_Start(void) ;
void VbusLow_IRQ_StartEx(cyisraddress address) ;
void VbusLow_IRQ_Stop(void) ;

CY_ISR_PROTO(VbusLow_IRQ_Interrupt);

void VbusLow_IRQ_SetVector(cyisraddress address) ;
cyisraddress VbusLow_IRQ_GetVector(void) ;

void VbusLow_IRQ_SetPriority(uint8 priority) ;
uint8 VbusLow_IRQ_GetPriority(void) ;

void VbusLow_IRQ_Enable(void) ;
uint8 VbusLow_IRQ_GetState(void) ;
void VbusLow_IRQ_Disable(void) ;

void VbusLow_IRQ_SetPending(void) ;
void VbusLow_IRQ_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the VbusLow_IRQ ISR. */
#define VbusLow_IRQ_INTC_VECTOR            ((reg16 *) VbusLow_IRQ__INTC_VECT)

/* Address of the VbusLow_IRQ ISR priority. */
#define VbusLow_IRQ_INTC_PRIOR             ((reg8 *) VbusLow_IRQ__INTC_PRIOR_REG)

/* Priority of the VbusLow_IRQ interrupt. */
#define VbusLow_IRQ_INTC_PRIOR_NUMBER      VbusLow_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable VbusLow_IRQ interrupt. */
#define VbusLow_IRQ_INTC_SET_EN            ((reg8 *) VbusLow_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the VbusLow_IRQ interrupt. */
#define VbusLow_IRQ_INTC_CLR_EN            ((reg8 *) VbusLow_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the VbusLow_IRQ interrupt state to pending. */
#define VbusLow_IRQ_INTC_SET_PD            ((reg8 *) VbusLow_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the VbusLow_IRQ interrupt. */
#define VbusLow_IRQ_INTC_CLR_PD            ((reg8 *) VbusLow_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_VbusLow_IRQ_H */


/* [] END OF FILE */
