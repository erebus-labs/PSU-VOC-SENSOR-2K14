/*******************************************************************************
* File Name: USB_EN_ISR.h
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

#if !defined(CY_ISR_USB_EN_ISR_H)
#define CY_ISR_USB_EN_ISR_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void USB_EN_ISR_Start(void) ;
void USB_EN_ISR_StartEx(cyisraddress address) ;
void USB_EN_ISR_Stop(void) ;

CY_ISR_PROTO(USB_EN_ISR_Interrupt);

void USB_EN_ISR_SetVector(cyisraddress address) ;
cyisraddress USB_EN_ISR_GetVector(void) ;

void USB_EN_ISR_SetPriority(uint8 priority) ;
uint8 USB_EN_ISR_GetPriority(void) ;

void USB_EN_ISR_Enable(void) ;
uint8 USB_EN_ISR_GetState(void) ;
void USB_EN_ISR_Disable(void) ;

void USB_EN_ISR_SetPending(void) ;
void USB_EN_ISR_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the USB_EN_ISR ISR. */
#define USB_EN_ISR_INTC_VECTOR            ((reg16 *) USB_EN_ISR__INTC_VECT)

/* Address of the USB_EN_ISR ISR priority. */
#define USB_EN_ISR_INTC_PRIOR             ((reg8 *) USB_EN_ISR__INTC_PRIOR_REG)

/* Priority of the USB_EN_ISR interrupt. */
#define USB_EN_ISR_INTC_PRIOR_NUMBER      USB_EN_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable USB_EN_ISR interrupt. */
#define USB_EN_ISR_INTC_SET_EN            ((reg8 *) USB_EN_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the USB_EN_ISR interrupt. */
#define USB_EN_ISR_INTC_CLR_EN            ((reg8 *) USB_EN_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the USB_EN_ISR interrupt state to pending. */
#define USB_EN_ISR_INTC_SET_PD            ((reg8 *) USB_EN_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the USB_EN_ISR interrupt. */
#define USB_EN_ISR_INTC_CLR_PD            ((reg8 *) USB_EN_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_USB_EN_ISR_H */


/* [] END OF FILE */
