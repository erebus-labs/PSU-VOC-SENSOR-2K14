/*******************************************************************************
* FILENAME: cyfitter_cfg.c
* PSoC Creator 3.0 Component Pack 7
*
* Description:
* This file is automatically generated by PSoC Creator with device 
* initialization code.  Except for the user defined sections in
* CyClockStartupError(), this file should not be modified.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
#include <cyfitter_cfg.h>


#if defined(__C51__) || defined(__CX51__)
	#define CYPACKED
	#define CYPACKED_ATTR
	#define CYALIGNED
	
    #define CY_CFG_UNUSED
	#define CY_CFG_MEMORY_BARRIER() do { } while (0)



	#define CYMEMZERO(a,c) cymemzero((a),(c))
	#define CYCONFIGCPY(d,s,c) cyconfigcpy((c),(s),(d))
	#define CYCONFIGCPYCODE(d,s,c) cyconfigcpycode((c),(s),(d))
#else
	#error Unsupported toolchain
#endif



/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u

#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* `#START CyClockStartupError` */

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

    /* `#END` */

    /* If nothing else, stop here since the clocks have not started         */
    /* correctly.                                                           */
    while(1) {}
}
#endif

#define cfg_byte_table ((const void CYFAR *)0x080000u)
/* IOPINS0_0 Address: CYREG_PRT0_DM0 Size (bytes): 8 */
#define BS_IOPINS0_0_VAL ((const uint8 CYFAR *)0x00080214u)

/* IOPINS0_7 Address: CYREG_PRT12_DR Size (bytes): 10 */
#define BS_IOPINS0_7_VAL ((const uint8 CYFAR *)0x0008021Cu)

/* IOPINS0_8 Address: CYREG_PRT15_DR Size (bytes): 10 */
#define BS_IOPINS0_8_VAL ((const uint8 CYFAR *)0x00080228u)

/* IOPINS0_3 Address: CYREG_PRT3_DR Size (bytes): 10 */
#define BS_IOPINS0_3_VAL ((const uint8 CYFAR *)0x00080234u)

/* IOPINS0_6 Address: CYREG_PRT6_DM0 Size (bytes): 8 */
#define BS_IOPINS0_6_VAL ((const uint8 CYFAR *)0x00080240u)

/* CYDEV_CLKDIST_ACFG0_CFG0 Address: CYREG_CLKDIST_ACFG0_CFG0 Size (bytes): 4 */
#define BS_CYDEV_CLKDIST_ACFG0_CFG0_VAL ((const uint8 CYFAR *)0x00080248u)


/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*  Performs the initialization of all of the clocks in the device based on the
*  settings in the Clock tab of the DWR.  This includes enabling the requested
*  clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void ClockSetup(void);
static void ClockSetup(void)
{
	uint8 x32TrHold;
	uint32 timeout;

	x32TrHold = CY_GET_REG8((void CYXDATA *)CYREG_X32_TR);

	/* Configure Digital Clocks based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG0_CFG0), 0x0000u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DCFG0_CFG0 + 0x2u), 0x50u);

	/* Configure Analog Clocks based on settings from Clock DWR */
	CYCONFIGCPY((void CYFAR *)(CYREG_CLKDIST_ACFG0_CFG0), (const void CYFAR *)(BS_CYDEV_CLKDIST_ACFG0_CFG0_VAL), 4u);

	/* Configure ILO based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_SLOWCLK_ILO_CR0), 0x06u);

	/* Configure XTAL 32kHz based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_SLOWCLK_X32_TST), 0xF3u);
	CY_SET_REG8((void CYXDATA *)(CYREG_X32_TR), 0x03u);
	CY_SET_REG8((void CYXDATA *)(CYREG_SLOWCLK_X32_CFG), 0x84u);
	CY_SET_REG8((void CYXDATA *)(CYREG_SLOWCLK_X32_CR), 0x05u);
	/* Wait up to 1000000us for the XTAL 32kHz to lock */
	for (timeout = 1000000u / 10u; (timeout > 0u) && ((CY_GET_REG8((void CYXDATA *)CYREG_SLOWCLK_X32_CR) & 0x20u) == 0u); timeout--)
	{ 
		
		CyDelayCycles(10u * 48u); /* Delay 10us based on 48MHz clock */
	}
	CY_SET_REG8((void CYXDATA *)(CYREG_X32_TR), (x32TrHold));

	/* Configure IMO based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_FASTCLK_IMO_CR), 0x52u);
	CY_SET_REG8((void CYXDATA *)(CYREG_IMO_TR1), (CY_GET_XTND_REG8((void CYFAR *)CYREG_FLSHID_CUST_TABLES_IMO_USB)));

	/* Configure Bus/Master Clock based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_MSTR0), 0x0000u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_MSTR0), 0x07u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_BCFG0), 0x00u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_BCFG2), 0x48u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_MSTR0), 0x00u);

	/* Configure USB Clock based on settings from Clock DWR */
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_UCFG), 0x00u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_LD), 0x02u);
	CY_SET_REG8((void CYXDATA *)(CYREG_CLKDIST_DLY1), 0x04u);

	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG2), ((CY_GET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG2) | 0x01u)));
	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG1), ((CY_GET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG1) | 0x01u)));
	CY_SET_REG8((void CYXDATA *)(CYREG_PM_ACT_CFG0), ((CY_GET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG0) | 0x80u)));
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	uint8 bg_xover_inl_trim = CY_GET_XTND_REG8((void CYFAR *)(CYREG_FLSHID_MFG_CFG_BG_XOVER_INL_TRIM + 1u));
	CY_SET_REG8((void CYXDATA *)(CYREG_BG_DFT0), (bg_xover_inl_trim & 0x07u));
	CY_SET_REG8((void CYXDATA *)(CYREG_BG_DFT1), ((bg_xover_inl_trim >> 4) & 0x0Fu));
	CY_SET_REG8((void CYXDATA *)CYREG_PRT0_AG, 0x80u);
	CY_SET_REG8((void CYXDATA *)CYREG_DSM0_SW0, 0x80u);
	CY_SET_REG8((void CYXDATA *)CYREG_PUMP_CR0, 0x44u);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage
* crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint8 regValue = CY_GET_REG8((void CYXDATA *)CYREG_PUMP_CR0);
	if (enabled != 0u)
	{
		regValue |= 0x22u;
	}
	else
	{
		regValue &= (uint8)~0x22u;
	}
	CY_SET_REG8((void CYXDATA *)CYREG_PUMP_CR0, regValue);
}

#define CY_AMUX_UNUSED CYREG_BOOST_SR
/* This is an implementation detail of the AMux. Code that depends on it may be
   incompatible with other versions of PSoC Creator. */
uint8 CYXDATA * const CYCODE ADC_AMux__addrTable[2] = {
	(uint8 CYXDATA *)CYREG_DSM0_SW3, 
	(uint8 CYXDATA *)CY_AMUX_UNUSED, 
};

/* This is an implementation detail of the AMux. Code that depends on it may be
   incompatible with other versions of PSoC Creator. */
const uint8 CYCODE ADC_AMux__maskTable[2] = {
	0x40u, 
	0x00u, 
};

/*******************************************************************************
* Function Name: ADC_AMux_Set
********************************************************************************
* Summary:
*  This function is used to set a particular channel as active on the AMux.
*
* Parameters:  
*   channel - The mux channel input to set as active
*
* Return:
*   void
*
*******************************************************************************/
void ADC_AMux_Set(uint8 channel)
{
	if (channel < 2)
	{
		*ADC_AMux__addrTable[channel] |= ADC_AMux__maskTable[channel];
	}
}

/*******************************************************************************
* Function Name: ADC_AMux_Unset
********************************************************************************
* Summary:
*  This function is used to clear a particular channel from being active on the
*  AMux.
*
* Parameters:  
*   channel - The mux channel input to mark inactive
*
* Return:
*   void
*
*******************************************************************************/
void ADC_AMux_Unset(uint8 channel)
{
	if (channel < 2)
	{
		*ADC_AMux__addrTable[channel] &= (uint8)~ADC_AMux__maskTable[channel];
	}
}



/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/

void cyfitter_cfg(void)
{
	/* Enable/Disable Debug functionality based on settings from System DWR */
	CY_SET_XTND_REG8((void CYFAR *)CYREG_MLOGIC_DEBUG, (CY_GET_XTND_REG8((void CYFAR *)CYREG_MLOGIC_DEBUG) | 0x05u));

	{

		CYPACKED typedef struct {
			void CYFAR *address;
			uint16 size;
		} CYPACKED_ATTR cfg_memset_t;

		static const cfg_memset_t CYCODE cfg_memset_list [] = {
			/* address, size */
			{(void CYFAR *)(CYREG_PRT1_DR), 32u},
			{(void CYFAR *)(CYREG_PRT4_DR), 32u},
			{(void CYFAR *)(CYDEV_UCFG_B0_P0_U0_BASE), 4096u},
			{(void CYFAR *)(CYDEV_UCFG_B1_P2_U0_BASE), 2048u},
			{(void CYFAR *)(CYDEV_UCFG_DSI0_BASE), 2560u},
			{(void CYFAR *)(CYDEV_UCFG_DSI12_BASE), 512u},
			{(void CYFAR *)(CYREG_BCTL0_MDCLK_EN), 32u},
		};

		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0u; i < (sizeof(cfg_memset_list)/sizeof(cfg_memset_list[0])); i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, ms->size);
		}

		cfg_write_bytes(cfg_byte_table);

		/* Perform normal device configuration. Order is not critical for these items. */
		CY_SET_REG8((void CYXDATA *)(CYREG_DSM0_CR3), 0x0Au);

		/* Enable digital routing */
		CY_SET_XTND_REG8((void CYFAR *)CYREG_BCTL0_BANK_CTL, CY_GET_XTND_REG8((void CYFAR *)CYREG_BCTL0_BANK_CTL) | 0x02u);
		CY_SET_XTND_REG8((void CYFAR *)CYREG_BCTL1_BANK_CTL, CY_GET_XTND_REG8((void CYFAR *)CYREG_BCTL1_BANK_CTL) | 0x02u);

		/* Enable UDB array */
		CY_SET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG0, CY_GET_REG8((void CYXDATA *)CYREG_PM_ACT_CFG0) | 0x40u);
		CY_SET_REG8((void CYXDATA *)CYREG_PM_AVAIL_CR2, CY_GET_REG8((void CYXDATA *)CYREG_PM_AVAIL_CR2) | 0x10u);
	}

	/* Perform second pass device configuration. These items must be configured in specific order after the regular configuration is done. */
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT0_DM0), (const void CYFAR *)(BS_IOPINS0_0_VAL), 8u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT12_DR), (const void CYFAR *)(BS_IOPINS0_7_VAL), 10u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT15_DR), (const void CYFAR *)(BS_IOPINS0_8_VAL), 10u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT3_DR), (const void CYFAR *)(BS_IOPINS0_3_VAL), 10u);
	CYCONFIGCPY((void CYFAR *)(CYREG_PRT6_DM0), (const void CYFAR *)(BS_IOPINS0_6_VAL), 8u);
	CY_SET_REG8((void CYXDATA *)(CYREG_INTC_CSR_EN), 0x01u);

	/* Switch Boost to the precision bandgap reference from its internal reference */
	CY_SET_REG8((void CYXDATA *)CYREG_BOOST_CR2, (CY_GET_REG8((void CYXDATA *)CYREG_BOOST_CR2) | 0x08u));
	if (CYDEV_CHIP_REV_ACTUAL < 5u)
	{
		CY_SET_REG8((void CYXDATA *)CYREG_PWRSYS_WAKE_TR2, 0x3Au);
	}


	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG8((void CYXDATA *)(CYREG_CACHE_CR), (((CYDEV_INSTRUCT_CACHE_ENABLED) != 0) ? 0xF1u : 0xC0u));
	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();
	/* Set Flash Cycles based on newly configured 24.00MHz Bus Clock. */
	CY_SET_REG8((void CYXDATA *)(CYREG_CACHE_CR), (((CYDEV_INSTRUCT_CACHE_ENABLED) != 0) ? 0xB1u : 0x80u));

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

	/* Configure alternate active mode */
	CYCONFIGCPY((void CYFAR *)CYDEV_PM_STBY_BASE, (const void CYFAR *)CYDEV_PM_ACT_BASE, 14u);
	CY_SET_REG8((void CYXDATA *)CYREG_PM_STBY_CFG0, CY_GET_REG8((void CYXDATA *)CYREG_PM_STBY_CFG0) & (uint8)~0x02u);	/* Disable CPU */
}
