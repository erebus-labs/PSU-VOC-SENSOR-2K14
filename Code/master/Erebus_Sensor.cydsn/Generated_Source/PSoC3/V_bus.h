/*******************************************************************************
* File Name: V_bus.h  
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

#if !defined(CY_PINS_V_bus_H) /* Pins V_bus_H */
#define CY_PINS_V_bus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_bus_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    V_bus_Write(uint8 value) ;
void    V_bus_SetDriveMode(uint8 mode) ;
uint8   V_bus_ReadDataReg(void) ;
uint8   V_bus_Read(void) ;
uint8   V_bus_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V_bus_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define V_bus_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define V_bus_DM_RES_UP          PIN_DM_RES_UP
#define V_bus_DM_RES_DWN         PIN_DM_RES_DWN
#define V_bus_DM_OD_LO           PIN_DM_OD_LO
#define V_bus_DM_OD_HI           PIN_DM_OD_HI
#define V_bus_DM_STRONG          PIN_DM_STRONG
#define V_bus_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define V_bus_MASK               V_bus__MASK
#define V_bus_SHIFT              V_bus__SHIFT
#define V_bus_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_bus_PS                     (* (reg8 *) V_bus__PS)
/* Data Register */
#define V_bus_DR                     (* (reg8 *) V_bus__DR)
/* Port Number */
#define V_bus_PRT_NUM                (* (reg8 *) V_bus__PRT) 
/* Connect to Analog Globals */                                                  
#define V_bus_AG                     (* (reg8 *) V_bus__AG)                       
/* Analog MUX bux enable */
#define V_bus_AMUX                   (* (reg8 *) V_bus__AMUX) 
/* Bidirectional Enable */                                                        
#define V_bus_BIE                    (* (reg8 *) V_bus__BIE)
/* Bit-mask for Aliased Register Access */
#define V_bus_BIT_MASK               (* (reg8 *) V_bus__BIT_MASK)
/* Bypass Enable */
#define V_bus_BYP                    (* (reg8 *) V_bus__BYP)
/* Port wide control signals */                                                   
#define V_bus_CTL                    (* (reg8 *) V_bus__CTL)
/* Drive Modes */
#define V_bus_DM0                    (* (reg8 *) V_bus__DM0) 
#define V_bus_DM1                    (* (reg8 *) V_bus__DM1)
#define V_bus_DM2                    (* (reg8 *) V_bus__DM2) 
/* Input Buffer Disable Override */
#define V_bus_INP_DIS                (* (reg8 *) V_bus__INP_DIS)
/* LCD Common or Segment Drive */
#define V_bus_LCD_COM_SEG            (* (reg8 *) V_bus__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_bus_LCD_EN                 (* (reg8 *) V_bus__LCD_EN)
/* Slew Rate Control */
#define V_bus_SLW                    (* (reg8 *) V_bus__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_bus_PRTDSI__CAPS_SEL       (* (reg8 *) V_bus__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_bus_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_bus__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_bus_PRTDSI__OE_SEL0        (* (reg8 *) V_bus__PRTDSI__OE_SEL0) 
#define V_bus_PRTDSI__OE_SEL1        (* (reg8 *) V_bus__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_bus_PRTDSI__OUT_SEL0       (* (reg8 *) V_bus__PRTDSI__OUT_SEL0) 
#define V_bus_PRTDSI__OUT_SEL1       (* (reg8 *) V_bus__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_bus_PRTDSI__SYNC_OUT       (* (reg8 *) V_bus__PRTDSI__SYNC_OUT) 


#if defined(V_bus__INTSTAT)  /* Interrupt Registers */

    #define V_bus_INTSTAT                (* (reg8 *) V_bus__INTSTAT)
    #define V_bus_SNAP                   (* (reg8 *) V_bus__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins V_bus_H */


/* [] END OF FILE */
