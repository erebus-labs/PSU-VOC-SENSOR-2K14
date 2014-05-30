/*******************************************************************************
* File Name: ADC_MUX.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_ADC_MUX_H)
#define CY_AMUX_ADC_MUX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void ADC_MUX_Start(void) ;
#define ADC_MUX_Init() ADC_MUX_Start()
void ADC_MUX_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void ADC_MUX_Stop(void); */
/* void ADC_MUX_Select(uint8 channel); */
/* void ADC_MUX_Connect(uint8 channel); */
/* void ADC_MUX_Disconnect(uint8 channel); */
/* void ADC_MUX_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define ADC_MUX_CHANNELS  2u
#define ADC_MUX_MUXTYPE   1
#define ADC_MUX_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define ADC_MUX_NULL_CHANNEL 0xFFu
#define ADC_MUX_MUX_SINGLE   1
#define ADC_MUX_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if ADC_MUX_MUXTYPE == ADC_MUX_MUX_SINGLE
# if !ADC_MUX_ATMOSTONE
#  define ADC_MUX_Connect(channel) ADC_MUX_Set(channel)
# endif
# define ADC_MUX_Disconnect(channel) ADC_MUX_Unset(channel)
#else
# if !ADC_MUX_ATMOSTONE
void ADC_MUX_Connect(uint8 channel) ;
# endif
void ADC_MUX_Disconnect(uint8 channel) ;
#endif

#if ADC_MUX_ATMOSTONE
# define ADC_MUX_Stop() ADC_MUX_DisconnectAll()
# define ADC_MUX_Select(channel) ADC_MUX_FastSelect(channel)
void ADC_MUX_DisconnectAll(void) ;
#else
# define ADC_MUX_Stop() ADC_MUX_Start()
void ADC_MUX_Select(uint8 channel) ;
# define ADC_MUX_DisconnectAll() ADC_MUX_Start()
#endif

#endif /* CY_AMUX_ADC_MUX_H */


/* [] END OF FILE */
