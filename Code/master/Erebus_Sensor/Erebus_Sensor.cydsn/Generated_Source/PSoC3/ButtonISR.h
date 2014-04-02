/*******************************************************************************
* File Name: ButtonISR.h
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

#if !defined(CY_ISR_ButtonISR_H)
#define CY_ISR_ButtonISR_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ButtonISR_Start(void) ;
void ButtonISR_StartEx(cyisraddress address) ;
void ButtonISR_Stop(void) ;

CY_ISR_PROTO(ButtonISR_Interrupt);

void ButtonISR_SetVector(cyisraddress address) ;
cyisraddress ButtonISR_GetVector(void) ;

void ButtonISR_SetPriority(uint8 priority) ;
uint8 ButtonISR_GetPriority(void) ;

void ButtonISR_Enable(void) ;
uint8 ButtonISR_GetState(void) ;
void ButtonISR_Disable(void) ;

void ButtonISR_SetPending(void) ;
void ButtonISR_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ButtonISR ISR. */
#define ButtonISR_INTC_VECTOR            ((reg16 *) ButtonISR__INTC_VECT)

/* Address of the ButtonISR ISR priority. */
#define ButtonISR_INTC_PRIOR             ((reg8 *) ButtonISR__INTC_PRIOR_REG)

/* Priority of the ButtonISR interrupt. */
#define ButtonISR_INTC_PRIOR_NUMBER      ButtonISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ButtonISR interrupt. */
#define ButtonISR_INTC_SET_EN            ((reg8 *) ButtonISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ButtonISR interrupt. */
#define ButtonISR_INTC_CLR_EN            ((reg8 *) ButtonISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ButtonISR interrupt state to pending. */
#define ButtonISR_INTC_SET_PD            ((reg8 *) ButtonISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ButtonISR interrupt. */
#define ButtonISR_INTC_CLR_PD            ((reg8 *) ButtonISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_ButtonISR_H */


/* [] END OF FILE */
