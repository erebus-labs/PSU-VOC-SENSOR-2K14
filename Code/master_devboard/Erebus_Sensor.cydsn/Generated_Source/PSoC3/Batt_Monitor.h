/*******************************************************************************
* File Name: Batt_Monitor.h  
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

#if !defined(CY_PINS_Batt_Monitor_H) /* Pins Batt_Monitor_H */
#define CY_PINS_Batt_Monitor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Batt_Monitor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Batt_Monitor_Write(uint8 value) ;
void    Batt_Monitor_SetDriveMode(uint8 mode) ;
uint8   Batt_Monitor_ReadDataReg(void) ;
uint8   Batt_Monitor_Read(void) ;
uint8   Batt_Monitor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Batt_Monitor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Batt_Monitor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Batt_Monitor_DM_RES_UP          PIN_DM_RES_UP
#define Batt_Monitor_DM_RES_DWN         PIN_DM_RES_DWN
#define Batt_Monitor_DM_OD_LO           PIN_DM_OD_LO
#define Batt_Monitor_DM_OD_HI           PIN_DM_OD_HI
#define Batt_Monitor_DM_STRONG          PIN_DM_STRONG
#define Batt_Monitor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Batt_Monitor_MASK               Batt_Monitor__MASK
#define Batt_Monitor_SHIFT              Batt_Monitor__SHIFT
#define Batt_Monitor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Batt_Monitor_PS                     (* (reg8 *) Batt_Monitor__PS)
/* Data Register */
#define Batt_Monitor_DR                     (* (reg8 *) Batt_Monitor__DR)
/* Port Number */
#define Batt_Monitor_PRT_NUM                (* (reg8 *) Batt_Monitor__PRT) 
/* Connect to Analog Globals */                                                  
#define Batt_Monitor_AG                     (* (reg8 *) Batt_Monitor__AG)                       
/* Analog MUX bux enable */
#define Batt_Monitor_AMUX                   (* (reg8 *) Batt_Monitor__AMUX) 
/* Bidirectional Enable */                                                        
#define Batt_Monitor_BIE                    (* (reg8 *) Batt_Monitor__BIE)
/* Bit-mask for Aliased Register Access */
#define Batt_Monitor_BIT_MASK               (* (reg8 *) Batt_Monitor__BIT_MASK)
/* Bypass Enable */
#define Batt_Monitor_BYP                    (* (reg8 *) Batt_Monitor__BYP)
/* Port wide control signals */                                                   
#define Batt_Monitor_CTL                    (* (reg8 *) Batt_Monitor__CTL)
/* Drive Modes */
#define Batt_Monitor_DM0                    (* (reg8 *) Batt_Monitor__DM0) 
#define Batt_Monitor_DM1                    (* (reg8 *) Batt_Monitor__DM1)
#define Batt_Monitor_DM2                    (* (reg8 *) Batt_Monitor__DM2) 
/* Input Buffer Disable Override */
#define Batt_Monitor_INP_DIS                (* (reg8 *) Batt_Monitor__INP_DIS)
/* LCD Common or Segment Drive */
#define Batt_Monitor_LCD_COM_SEG            (* (reg8 *) Batt_Monitor__LCD_COM_SEG)
/* Enable Segment LCD */
#define Batt_Monitor_LCD_EN                 (* (reg8 *) Batt_Monitor__LCD_EN)
/* Slew Rate Control */
#define Batt_Monitor_SLW                    (* (reg8 *) Batt_Monitor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Batt_Monitor_PRTDSI__CAPS_SEL       (* (reg8 *) Batt_Monitor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Batt_Monitor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Batt_Monitor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Batt_Monitor_PRTDSI__OE_SEL0        (* (reg8 *) Batt_Monitor__PRTDSI__OE_SEL0) 
#define Batt_Monitor_PRTDSI__OE_SEL1        (* (reg8 *) Batt_Monitor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Batt_Monitor_PRTDSI__OUT_SEL0       (* (reg8 *) Batt_Monitor__PRTDSI__OUT_SEL0) 
#define Batt_Monitor_PRTDSI__OUT_SEL1       (* (reg8 *) Batt_Monitor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Batt_Monitor_PRTDSI__SYNC_OUT       (* (reg8 *) Batt_Monitor__PRTDSI__SYNC_OUT) 


#if defined(Batt_Monitor__INTSTAT)  /* Interrupt Registers */

    #define Batt_Monitor_INTSTAT                (* (reg8 *) Batt_Monitor__INTSTAT)
    #define Batt_Monitor_SNAP                   (* (reg8 *) Batt_Monitor__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Batt_Monitor_H */


/* [] END OF FILE */
