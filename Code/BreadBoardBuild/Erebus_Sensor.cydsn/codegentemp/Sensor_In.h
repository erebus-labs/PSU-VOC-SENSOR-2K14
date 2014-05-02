/*******************************************************************************
* File Name: Sensor_In.h  
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

#if !defined(CY_PINS_Sensor_In_H) /* Pins Sensor_In_H */
#define CY_PINS_Sensor_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sensor_In_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Sensor_In_Write(uint8 value) ;
void    Sensor_In_SetDriveMode(uint8 mode) ;
uint8   Sensor_In_ReadDataReg(void) ;
uint8   Sensor_In_Read(void) ;
uint8   Sensor_In_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Sensor_In_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Sensor_In_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Sensor_In_DM_RES_UP          PIN_DM_RES_UP
#define Sensor_In_DM_RES_DWN         PIN_DM_RES_DWN
#define Sensor_In_DM_OD_LO           PIN_DM_OD_LO
#define Sensor_In_DM_OD_HI           PIN_DM_OD_HI
#define Sensor_In_DM_STRONG          PIN_DM_STRONG
#define Sensor_In_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Sensor_In_MASK               Sensor_In__MASK
#define Sensor_In_SHIFT              Sensor_In__SHIFT
#define Sensor_In_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sensor_In_PS                     (* (reg8 *) Sensor_In__PS)
/* Data Register */
#define Sensor_In_DR                     (* (reg8 *) Sensor_In__DR)
/* Port Number */
#define Sensor_In_PRT_NUM                (* (reg8 *) Sensor_In__PRT) 
/* Connect to Analog Globals */                                                  
#define Sensor_In_AG                     (* (reg8 *) Sensor_In__AG)                       
/* Analog MUX bux enable */
#define Sensor_In_AMUX                   (* (reg8 *) Sensor_In__AMUX) 
/* Bidirectional Enable */                                                        
#define Sensor_In_BIE                    (* (reg8 *) Sensor_In__BIE)
/* Bit-mask for Aliased Register Access */
#define Sensor_In_BIT_MASK               (* (reg8 *) Sensor_In__BIT_MASK)
/* Bypass Enable */
#define Sensor_In_BYP                    (* (reg8 *) Sensor_In__BYP)
/* Port wide control signals */                                                   
#define Sensor_In_CTL                    (* (reg8 *) Sensor_In__CTL)
/* Drive Modes */
#define Sensor_In_DM0                    (* (reg8 *) Sensor_In__DM0) 
#define Sensor_In_DM1                    (* (reg8 *) Sensor_In__DM1)
#define Sensor_In_DM2                    (* (reg8 *) Sensor_In__DM2) 
/* Input Buffer Disable Override */
#define Sensor_In_INP_DIS                (* (reg8 *) Sensor_In__INP_DIS)
/* LCD Common or Segment Drive */
#define Sensor_In_LCD_COM_SEG            (* (reg8 *) Sensor_In__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sensor_In_LCD_EN                 (* (reg8 *) Sensor_In__LCD_EN)
/* Slew Rate Control */
#define Sensor_In_SLW                    (* (reg8 *) Sensor_In__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sensor_In_PRTDSI__CAPS_SEL       (* (reg8 *) Sensor_In__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sensor_In_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sensor_In__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sensor_In_PRTDSI__OE_SEL0        (* (reg8 *) Sensor_In__PRTDSI__OE_SEL0) 
#define Sensor_In_PRTDSI__OE_SEL1        (* (reg8 *) Sensor_In__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sensor_In_PRTDSI__OUT_SEL0       (* (reg8 *) Sensor_In__PRTDSI__OUT_SEL0) 
#define Sensor_In_PRTDSI__OUT_SEL1       (* (reg8 *) Sensor_In__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sensor_In_PRTDSI__SYNC_OUT       (* (reg8 *) Sensor_In__PRTDSI__SYNC_OUT) 


#if defined(Sensor_In__INTSTAT)  /* Interrupt Registers */

    #define Sensor_In_INTSTAT                (* (reg8 *) Sensor_In__INTSTAT)
    #define Sensor_In_SNAP                   (* (reg8 *) Sensor_In__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Sensor_In_H */


/* [] END OF FILE */
