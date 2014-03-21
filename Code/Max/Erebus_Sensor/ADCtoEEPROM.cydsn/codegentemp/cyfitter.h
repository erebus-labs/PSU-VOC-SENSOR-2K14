#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* ADC_Ext_CP_Clk */
#define ADC_Ext_CP_Clk__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define ADC_Ext_CP_Clk__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define ADC_Ext_CP_Clk__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define ADC_Ext_CP_Clk__CFG2_SRC_SEL_MASK 0x07u
#define ADC_Ext_CP_Clk__INDEX 0x00u
#define ADC_Ext_CP_Clk__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define ADC_Ext_CP_Clk__PM_ACT_MSK 0x01u
#define ADC_Ext_CP_Clk__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define ADC_Ext_CP_Clk__PM_STBY_MSK 0x01u

/* TakeSample_IRQ */
#define TakeSample_IRQ__ES2_PATCH 0u
#define TakeSample_IRQ__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define TakeSample_IRQ__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define TakeSample_IRQ__INTC_MASK 0x01u
#define TakeSample_IRQ__INTC_NUMBER 0u
#define TakeSample_IRQ__INTC_PRIOR_NUM 7u
#define TakeSample_IRQ__INTC_PRIOR_REG CYREG_INTC_PRIOR0
#define TakeSample_IRQ__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define TakeSample_IRQ__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define TakeSample_IRQ__INTC_VECT (CYREG_INTC_VECT_MBASE+0x00u)

/* Potentiometer */
#define Potentiometer__0__MASK 0x20u
#define Potentiometer__0__PC CYREG_PRT6_PC5
#define Potentiometer__0__PORT 6u
#define Potentiometer__0__SHIFT 5
#define Potentiometer__AG CYREG_PRT6_AG
#define Potentiometer__AMUX CYREG_PRT6_AMUX
#define Potentiometer__BIE CYREG_PRT6_BIE
#define Potentiometer__BIT_MASK CYREG_PRT6_BIT_MASK
#define Potentiometer__BYP CYREG_PRT6_BYP
#define Potentiometer__CTL CYREG_PRT6_CTL
#define Potentiometer__DM0 CYREG_PRT6_DM0
#define Potentiometer__DM1 CYREG_PRT6_DM1
#define Potentiometer__DM2 CYREG_PRT6_DM2
#define Potentiometer__DR CYREG_PRT6_DR
#define Potentiometer__INP_DIS CYREG_PRT6_INP_DIS
#define Potentiometer__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define Potentiometer__LCD_EN CYREG_PRT6_LCD_EN
#define Potentiometer__MASK 0x20u
#define Potentiometer__PORT 6u
#define Potentiometer__PRT CYREG_PRT6_PRT
#define Potentiometer__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define Potentiometer__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define Potentiometer__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define Potentiometer__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define Potentiometer__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define Potentiometer__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define Potentiometer__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define Potentiometer__PS CYREG_PRT6_PS
#define Potentiometer__SHIFT 5
#define Potentiometer__SLW CYREG_PRT6_SLW

/* ADC_theACLK */
#define ADC_theACLK__CFG0 CYREG_CLKDIST_ACFG0_CFG0
#define ADC_theACLK__CFG1 CYREG_CLKDIST_ACFG0_CFG1
#define ADC_theACLK__CFG2 CYREG_CLKDIST_ACFG0_CFG2
#define ADC_theACLK__CFG2_SRC_SEL_MASK 0x07u
#define ADC_theACLK__CFG3 CYREG_CLKDIST_ACFG0_CFG3
#define ADC_theACLK__CFG3_PHASE_DLY_MASK 0x0Fu
#define ADC_theACLK__INDEX 0x00u
#define ADC_theACLK__PM_ACT_CFG CYREG_PM_ACT_CFG1
#define ADC_theACLK__PM_ACT_MSK 0x01u
#define ADC_theACLK__PM_STBY_CFG CYREG_PM_STBY_CFG1
#define ADC_theACLK__PM_STBY_MSK 0x01u

/* LCD_LCDPort */
#define LCD_LCDPort__0__MASK 0x01u
#define LCD_LCDPort__0__PC CYREG_PRT0_PC0
#define LCD_LCDPort__0__PORT 0u
#define LCD_LCDPort__0__SHIFT 0
#define LCD_LCDPort__1__MASK 0x02u
#define LCD_LCDPort__1__PC CYREG_PRT0_PC1
#define LCD_LCDPort__1__PORT 0u
#define LCD_LCDPort__1__SHIFT 1
#define LCD_LCDPort__2__MASK 0x04u
#define LCD_LCDPort__2__PC CYREG_PRT0_PC2
#define LCD_LCDPort__2__PORT 0u
#define LCD_LCDPort__2__SHIFT 2
#define LCD_LCDPort__3__MASK 0x08u
#define LCD_LCDPort__3__PC CYREG_PRT0_PC3
#define LCD_LCDPort__3__PORT 0u
#define LCD_LCDPort__3__SHIFT 3
#define LCD_LCDPort__4__MASK 0x10u
#define LCD_LCDPort__4__PC CYREG_PRT0_PC4
#define LCD_LCDPort__4__PORT 0u
#define LCD_LCDPort__4__SHIFT 4
#define LCD_LCDPort__5__MASK 0x20u
#define LCD_LCDPort__5__PC CYREG_PRT0_PC5
#define LCD_LCDPort__5__PORT 0u
#define LCD_LCDPort__5__SHIFT 5
#define LCD_LCDPort__6__MASK 0x40u
#define LCD_LCDPort__6__PC CYREG_PRT0_PC6
#define LCD_LCDPort__6__PORT 0u
#define LCD_LCDPort__6__SHIFT 6
#define LCD_LCDPort__AG CYREG_PRT0_AG
#define LCD_LCDPort__AMUX CYREG_PRT0_AMUX
#define LCD_LCDPort__BIE CYREG_PRT0_BIE
#define LCD_LCDPort__BIT_MASK CYREG_PRT0_BIT_MASK
#define LCD_LCDPort__BYP CYREG_PRT0_BYP
#define LCD_LCDPort__CTL CYREG_PRT0_CTL
#define LCD_LCDPort__DM0 CYREG_PRT0_DM0
#define LCD_LCDPort__DM1 CYREG_PRT0_DM1
#define LCD_LCDPort__DM2 CYREG_PRT0_DM2
#define LCD_LCDPort__DR CYREG_PRT0_DR
#define LCD_LCDPort__INP_DIS CYREG_PRT0_INP_DIS
#define LCD_LCDPort__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define LCD_LCDPort__LCD_EN CYREG_PRT0_LCD_EN
#define LCD_LCDPort__MASK 0x7Fu
#define LCD_LCDPort__PORT 0u
#define LCD_LCDPort__PRT CYREG_PRT0_PRT
#define LCD_LCDPort__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define LCD_LCDPort__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define LCD_LCDPort__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define LCD_LCDPort__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define LCD_LCDPort__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define LCD_LCDPort__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define LCD_LCDPort__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define LCD_LCDPort__PS CYREG_PRT0_PS
#define LCD_LCDPort__SHIFT 0
#define LCD_LCDPort__SLW CYREG_PRT0_SLW

/* ADC_DEC */
#define ADC_DEC__COHER CYREG_DEC_COHER
#define ADC_DEC__CR CYREG_DEC_CR
#define ADC_DEC__DR1 CYREG_DEC_DR1
#define ADC_DEC__DR2 CYREG_DEC_DR2
#define ADC_DEC__DR2H CYREG_DEC_DR2H
#define ADC_DEC__GCOR CYREG_DEC_GCOR
#define ADC_DEC__GCORH CYREG_DEC_GCORH
#define ADC_DEC__GVAL CYREG_DEC_GVAL
#define ADC_DEC__OCOR CYREG_DEC_OCOR
#define ADC_DEC__OCORH CYREG_DEC_OCORH
#define ADC_DEC__OCORM CYREG_DEC_OCORM
#define ADC_DEC__OUTSAMP CYREG_DEC_OUTSAMP
#define ADC_DEC__OUTSAMPH CYREG_DEC_OUTSAMPH
#define ADC_DEC__OUTSAMPM CYREG_DEC_OUTSAMPM
#define ADC_DEC__OUTSAMPS CYREG_DEC_OUTSAMPS
#define ADC_DEC__PM_ACT_CFG CYREG_PM_ACT_CFG10
#define ADC_DEC__PM_ACT_MSK 0x01u
#define ADC_DEC__PM_STBY_CFG CYREG_PM_STBY_CFG10
#define ADC_DEC__PM_STBY_MSK 0x01u
#define ADC_DEC__SHIFT1 CYREG_DEC_SHIFT1
#define ADC_DEC__SHIFT2 CYREG_DEC_SHIFT2
#define ADC_DEC__SR CYREG_DEC_SR
#define ADC_DEC__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DEC_M1
#define ADC_DEC__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DEC_M2
#define ADC_DEC__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DEC_M3
#define ADC_DEC__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DEC_M4
#define ADC_DEC__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DEC_M5
#define ADC_DEC__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DEC_M6
#define ADC_DEC__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DEC_M7
#define ADC_DEC__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DEC_M8

/* ADC_DSM */
#define ADC_DSM__BUF0 CYREG_DSM0_BUF0
#define ADC_DSM__BUF1 CYREG_DSM0_BUF1
#define ADC_DSM__BUF2 CYREG_DSM0_BUF2
#define ADC_DSM__BUF3 CYREG_DSM0_BUF3
#define ADC_DSM__CLK CYREG_DSM0_CLK
#define ADC_DSM__CR0 CYREG_DSM0_CR0
#define ADC_DSM__CR1 CYREG_DSM0_CR1
#define ADC_DSM__CR10 CYREG_DSM0_CR10
#define ADC_DSM__CR11 CYREG_DSM0_CR11
#define ADC_DSM__CR12 CYREG_DSM0_CR12
#define ADC_DSM__CR13 CYREG_DSM0_CR13
#define ADC_DSM__CR14 CYREG_DSM0_CR14
#define ADC_DSM__CR15 CYREG_DSM0_CR15
#define ADC_DSM__CR16 CYREG_DSM0_CR16
#define ADC_DSM__CR17 CYREG_DSM0_CR17
#define ADC_DSM__CR2 CYREG_DSM0_CR2
#define ADC_DSM__CR3 CYREG_DSM0_CR3
#define ADC_DSM__CR4 CYREG_DSM0_CR4
#define ADC_DSM__CR5 CYREG_DSM0_CR5
#define ADC_DSM__CR6 CYREG_DSM0_CR6
#define ADC_DSM__CR7 CYREG_DSM0_CR7
#define ADC_DSM__CR8 CYREG_DSM0_CR8
#define ADC_DSM__CR9 CYREG_DSM0_CR9
#define ADC_DSM__DEM0 CYREG_DSM0_DEM0
#define ADC_DSM__DEM1 CYREG_DSM0_DEM1
#define ADC_DSM__MISC CYREG_DSM0_MISC
#define ADC_DSM__OUT0 CYREG_DSM0_OUT0
#define ADC_DSM__OUT1 CYREG_DSM0_OUT1
#define ADC_DSM__REF0 CYREG_DSM0_REF0
#define ADC_DSM__REF1 CYREG_DSM0_REF1
#define ADC_DSM__REF2 CYREG_DSM0_REF2
#define ADC_DSM__REF3 CYREG_DSM0_REF3
#define ADC_DSM__RSVD1 CYREG_DSM0_RSVD1
#define ADC_DSM__SW0 CYREG_DSM0_SW0
#define ADC_DSM__SW2 CYREG_DSM0_SW2
#define ADC_DSM__SW3 CYREG_DSM0_SW3
#define ADC_DSM__SW4 CYREG_DSM0_SW4
#define ADC_DSM__SW6 CYREG_DSM0_SW6
#define ADC_DSM__TR0 CYREG_NPUMP_DSM_TR0
#define ADC_DSM__TST0 CYREG_DSM0_TST0
#define ADC_DSM__TST1 CYREG_DSM0_TST1

/* ADC_IRQ */
#define ADC_IRQ__ES2_PATCH 0u
#define ADC_IRQ__INTC_CLR_EN_REG CYREG_INTC_CLR_EN3
#define ADC_IRQ__INTC_CLR_PD_REG CYREG_INTC_CLR_PD3
#define ADC_IRQ__INTC_MASK 0x20u
#define ADC_IRQ__INTC_NUMBER 29u
#define ADC_IRQ__INTC_PRIOR_NUM 7u
#define ADC_IRQ__INTC_PRIOR_REG CYREG_INTC_PRIOR29
#define ADC_IRQ__INTC_SET_EN_REG CYREG_INTC_SET_EN3
#define ADC_IRQ__INTC_SET_PD_REG CYREG_INTC_SET_PD3
#define ADC_IRQ__INTC_VECT (CYREG_INTC_VECT_MBASE+0x3Au)

/* SW_3 */
#define SW_3__0__MASK 0x20u
#define SW_3__0__PC CYREG_IO_PC_PRT15_PC5
#define SW_3__0__PORT 15u
#define SW_3__0__SHIFT 5
#define SW_3__AG CYREG_PRT15_AG
#define SW_3__AMUX CYREG_PRT15_AMUX
#define SW_3__BIE CYREG_PRT15_BIE
#define SW_3__BIT_MASK CYREG_PRT15_BIT_MASK
#define SW_3__BYP CYREG_PRT15_BYP
#define SW_3__CTL CYREG_PRT15_CTL
#define SW_3__DM0 CYREG_PRT15_DM0
#define SW_3__DM1 CYREG_PRT15_DM1
#define SW_3__DM2 CYREG_PRT15_DM2
#define SW_3__DR CYREG_PRT15_DR
#define SW_3__INP_DIS CYREG_PRT15_INP_DIS
#define SW_3__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define SW_3__LCD_EN CYREG_PRT15_LCD_EN
#define SW_3__MASK 0x20u
#define SW_3__PORT 15u
#define SW_3__PRT CYREG_PRT15_PRT
#define SW_3__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define SW_3__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define SW_3__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define SW_3__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define SW_3__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define SW_3__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define SW_3__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define SW_3__PS CYREG_PRT15_PS
#define SW_3__SHIFT 5
#define SW_3__SLW CYREG_PRT15_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_LEOPARD
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_PANTHER 3u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_PSOC5LP 4u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC3
#define CYDEV_CHIP_JTAG_ID 0x1E028069u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_MEMBER_5B 4u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_3A
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_3A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_LEOPARD_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CONFIGURATION_CLEAR_SRAM 1
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x01u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000001u
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
