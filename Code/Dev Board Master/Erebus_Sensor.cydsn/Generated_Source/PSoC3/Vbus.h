/*******************************************************************************
* File Name: Vbus.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Vbus_H) /* Pins Vbus_H */
#define CY_PINS_Vbus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vbus_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Vbus_Write(uint8 value) ;
void    Vbus_SetDriveMode(uint8 mode) ;
uint8   Vbus_ReadDataReg(void) ;
uint8   Vbus_Read(void) ;
uint8   Vbus_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vbus_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Vbus_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Vbus_DM_RES_UP          PIN_DM_RES_UP
#define Vbus_DM_RES_DWN         PIN_DM_RES_DWN
#define Vbus_DM_OD_LO           PIN_DM_OD_LO
#define Vbus_DM_OD_HI           PIN_DM_OD_HI
#define Vbus_DM_STRONG          PIN_DM_STRONG
#define Vbus_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Vbus_MASK               Vbus__MASK
#define Vbus_SHIFT              Vbus__SHIFT
#define Vbus_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vbus_PS                     (* (reg8 *) Vbus__PS)
/* Data Register */
#define Vbus_DR                     (* (reg8 *) Vbus__DR)
/* Port Number */
#define Vbus_PRT_NUM                (* (reg8 *) Vbus__PRT) 
/* Connect to Analog Globals */                                                  
#define Vbus_AG                     (* (reg8 *) Vbus__AG)                       
/* Analog MUX bux enable */
#define Vbus_AMUX                   (* (reg8 *) Vbus__AMUX) 
/* Bidirectional Enable */                                                        
#define Vbus_BIE                    (* (reg8 *) Vbus__BIE)
/* Bit-mask for Aliased Register Access */
#define Vbus_BIT_MASK               (* (reg8 *) Vbus__BIT_MASK)
/* Bypass Enable */
#define Vbus_BYP                    (* (reg8 *) Vbus__BYP)
/* Port wide control signals */                                                   
#define Vbus_CTL                    (* (reg8 *) Vbus__CTL)
/* Drive Modes */
#define Vbus_DM0                    (* (reg8 *) Vbus__DM0) 
#define Vbus_DM1                    (* (reg8 *) Vbus__DM1)
#define Vbus_DM2                    (* (reg8 *) Vbus__DM2) 
/* Input Buffer Disable Override */
#define Vbus_INP_DIS                (* (reg8 *) Vbus__INP_DIS)
/* LCD Common or Segment Drive */
#define Vbus_LCD_COM_SEG            (* (reg8 *) Vbus__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vbus_LCD_EN                 (* (reg8 *) Vbus__LCD_EN)
/* Slew Rate Control */
#define Vbus_SLW                    (* (reg8 *) Vbus__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vbus_PRTDSI__CAPS_SEL       (* (reg8 *) Vbus__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vbus_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vbus__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vbus_PRTDSI__OE_SEL0        (* (reg8 *) Vbus__PRTDSI__OE_SEL0) 
#define Vbus_PRTDSI__OE_SEL1        (* (reg8 *) Vbus__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vbus_PRTDSI__OUT_SEL0       (* (reg8 *) Vbus__PRTDSI__OUT_SEL0) 
#define Vbus_PRTDSI__OUT_SEL1       (* (reg8 *) Vbus__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vbus_PRTDSI__SYNC_OUT       (* (reg8 *) Vbus__PRTDSI__SYNC_OUT) 


#if defined(Vbus__INTSTAT)  /* Interrupt Registers */

    #define Vbus_INTSTAT                (* (reg8 *) Vbus__INTSTAT)
    #define Vbus_SNAP                   (* (reg8 *) Vbus__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Vbus_H */


/* [] END OF FILE */
