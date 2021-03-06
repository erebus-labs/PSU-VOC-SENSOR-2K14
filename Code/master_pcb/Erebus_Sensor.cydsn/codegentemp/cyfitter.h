#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* ModifyCollection_IRQ */
#define ModifyCollection_IRQ__ES2_PATCH 0u
#define ModifyCollection_IRQ__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define ModifyCollection_IRQ__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define ModifyCollection_IRQ__INTC_MASK 0x40u
#define ModifyCollection_IRQ__INTC_NUMBER 6u
#define ModifyCollection_IRQ__INTC_PRIOR_NUM 7u
#define ModifyCollection_IRQ__INTC_PRIOR_REG CYREG_INTC_PRIOR6
#define ModifyCollection_IRQ__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define ModifyCollection_IRQ__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define ModifyCollection_IRQ__INTC_VECT (CYREG_INTC_VECT_MBASE+0x0Cu)

/* ModifyCollection_B */
#define ModifyCollection_B__0__MASK 0x08u
#define ModifyCollection_B__0__PC CYREG_PRT2_PC3
#define ModifyCollection_B__0__PORT 2u
#define ModifyCollection_B__0__SHIFT 3
#define ModifyCollection_B__1__MASK 0x10u
#define ModifyCollection_B__1__PC CYREG_PRT2_PC4
#define ModifyCollection_B__1__PORT 2u
#define ModifyCollection_B__1__SHIFT 4
#define ModifyCollection_B__AG CYREG_PRT2_AG
#define ModifyCollection_B__AMUX CYREG_PRT2_AMUX
#define ModifyCollection_B__BIE CYREG_PRT2_BIE
#define ModifyCollection_B__BIT_MASK CYREG_PRT2_BIT_MASK
#define ModifyCollection_B__BYP CYREG_PRT2_BYP
#define ModifyCollection_B__CTL CYREG_PRT2_CTL
#define ModifyCollection_B__DM0 CYREG_PRT2_DM0
#define ModifyCollection_B__DM1 CYREG_PRT2_DM1
#define ModifyCollection_B__DM2 CYREG_PRT2_DM2
#define ModifyCollection_B__DR CYREG_PRT2_DR
#define ModifyCollection_B__INP_DIS CYREG_PRT2_INP_DIS
#define ModifyCollection_B__INTSTAT CYREG_PICU2_INTSTAT
#define ModifyCollection_B__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define ModifyCollection_B__LCD_EN CYREG_PRT2_LCD_EN
#define ModifyCollection_B__MASK 0x18u
#define ModifyCollection_B__PORT 2u
#define ModifyCollection_B__PRT CYREG_PRT2_PRT
#define ModifyCollection_B__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define ModifyCollection_B__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define ModifyCollection_B__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define ModifyCollection_B__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define ModifyCollection_B__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define ModifyCollection_B__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define ModifyCollection_B__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define ModifyCollection_B__PS CYREG_PRT2_PS
#define ModifyCollection_B__SHIFT 3
#define ModifyCollection_B__SLW CYREG_PRT2_SLW
#define ModifyCollection_B__SNAP CYREG_PICU2_SNAP

/* USBUART_bus_reset */
#define USBUART_bus_reset__ES2_PATCH 0u
#define USBUART_bus_reset__INTC_CLR_EN_REG CYREG_INTC_CLR_EN2
#define USBUART_bus_reset__INTC_CLR_PD_REG CYREG_INTC_CLR_PD2
#define USBUART_bus_reset__INTC_MASK 0x80u
#define USBUART_bus_reset__INTC_NUMBER 23u
#define USBUART_bus_reset__INTC_PRIOR_NUM 6u
#define USBUART_bus_reset__INTC_PRIOR_REG CYREG_INTC_PRIOR23
#define USBUART_bus_reset__INTC_SET_EN_REG CYREG_INTC_SET_EN2
#define USBUART_bus_reset__INTC_SET_PD_REG CYREG_INTC_SET_PD2
#define USBUART_bus_reset__INTC_VECT (CYREG_INTC_VECT_MBASE+0x2Eu)

/* USBUART_arb_int */
#define USBUART_arb_int__ES2_PATCH 0u
#define USBUART_arb_int__INTC_CLR_EN_REG CYREG_INTC_CLR_EN2
#define USBUART_arb_int__INTC_CLR_PD_REG CYREG_INTC_CLR_PD2
#define USBUART_arb_int__INTC_MASK 0x40u
#define USBUART_arb_int__INTC_NUMBER 22u
#define USBUART_arb_int__INTC_PRIOR_NUM 6u
#define USBUART_arb_int__INTC_PRIOR_REG CYREG_INTC_PRIOR22
#define USBUART_arb_int__INTC_SET_EN_REG CYREG_INTC_SET_EN2
#define USBUART_arb_int__INTC_SET_PD_REG CYREG_INTC_SET_PD2
#define USBUART_arb_int__INTC_VECT (CYREG_INTC_VECT_MBASE+0x2Cu)

/* USBUART_sof_int */
#define USBUART_sof_int__ES2_PATCH 0u
#define USBUART_sof_int__INTC_CLR_EN_REG CYREG_INTC_CLR_EN2
#define USBUART_sof_int__INTC_CLR_PD_REG CYREG_INTC_CLR_PD2
#define USBUART_sof_int__INTC_MASK 0x20u
#define USBUART_sof_int__INTC_NUMBER 21u
#define USBUART_sof_int__INTC_PRIOR_NUM 6u
#define USBUART_sof_int__INTC_PRIOR_REG CYREG_INTC_PRIOR21
#define USBUART_sof_int__INTC_SET_EN_REG CYREG_INTC_SET_EN2
#define USBUART_sof_int__INTC_SET_PD_REG CYREG_INTC_SET_PD2
#define USBUART_sof_int__INTC_VECT (CYREG_INTC_VECT_MBASE+0x2Au)

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

/* LED_PWM_PWMUDB */
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB14_15_ACTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB14_15_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB14_15_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB14_15_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG CYREG_B0_UDB14_15_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG CYREG_B0_UDB14_15_MSK
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG CYREG_B0_UDB14_15_MSK
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG CYREG_B0_UDB14_15_MSK
#define LED_PWM_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB14_15_MSK
#define LED_PWM_PWMUDB_genblk1_ctrlreg__7__MASK 0x80u
#define LED_PWM_PWMUDB_genblk1_ctrlreg__7__POS 7
#define LED_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG CYREG_B0_UDB14_ACTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG CYREG_B0_UDB14_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG CYREG_B0_UDB14_ST_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__COUNT_REG CYREG_B0_UDB14_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG CYREG_B0_UDB14_ST_CTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__MASK 0x80u
#define LED_PWM_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define LED_PWM_PWMUDB_genblk1_ctrlreg__PERIOD_REG CYREG_B0_UDB14_MSK
#define LED_PWM_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__A0_A1_REG CYREG_B0_UDB15_A0_A1
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG CYREG_B0_UDB15_A0
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG CYREG_B0_UDB15_A1
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__D0_D1_REG CYREG_B0_UDB15_D0_D1
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG CYREG_B0_UDB15_D0
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG CYREG_B0_UDB15_D1
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG CYREG_B0_UDB15_ACTL
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__F0_F1_REG CYREG_B0_UDB15_F0_F1
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG CYREG_B0_UDB15_F0
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG CYREG_B0_UDB15_F1
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG CYREG_B0_UDB15_MSK_ACTL
#define LED_PWM_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG CYREG_B0_UDB15_MSK_ACTL

/* SOLID_LED_CTRL */
#define SOLID_LED_CTRL_Sync_ctrl_reg__0__MASK 0x01u
#define SOLID_LED_CTRL_Sync_ctrl_reg__0__POS 0
#define SOLID_LED_CTRL_Sync_ctrl_reg__1__MASK 0x02u
#define SOLID_LED_CTRL_Sync_ctrl_reg__1__POS 1
#define SOLID_LED_CTRL_Sync_ctrl_reg__2__MASK 0x04u
#define SOLID_LED_CTRL_Sync_ctrl_reg__2__POS 2
#define SOLID_LED_CTRL_Sync_ctrl_reg__CONTROL_AUX_CTL_REG CYREG_B0_UDB15_ACTL
#define SOLID_LED_CTRL_Sync_ctrl_reg__CONTROL_REG CYREG_B0_UDB15_CTL
#define SOLID_LED_CTRL_Sync_ctrl_reg__CONTROL_ST_REG CYREG_B0_UDB15_ST_CTL
#define SOLID_LED_CTRL_Sync_ctrl_reg__COUNT_REG CYREG_B0_UDB15_CTL
#define SOLID_LED_CTRL_Sync_ctrl_reg__COUNT_ST_REG CYREG_B0_UDB15_ST_CTL
#define SOLID_LED_CTRL_Sync_ctrl_reg__MASK 0x07u
#define SOLID_LED_CTRL_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB15_MSK_ACTL
#define SOLID_LED_CTRL_Sync_ctrl_reg__PERIOD_REG CYREG_B0_UDB15_MSK
#define SOLID_LED_CTRL_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB15_MSK_ACTL

/* USBUART_dp_int */
#define USBUART_dp_int__ES2_PATCH 0u
#define USBUART_dp_int__INTC_CLR_EN_REG CYREG_INTC_CLR_EN1
#define USBUART_dp_int__INTC_CLR_PD_REG CYREG_INTC_CLR_PD1
#define USBUART_dp_int__INTC_MASK 0x10u
#define USBUART_dp_int__INTC_NUMBER 12u
#define USBUART_dp_int__INTC_PRIOR_NUM 6u
#define USBUART_dp_int__INTC_PRIOR_REG CYREG_INTC_PRIOR12
#define USBUART_dp_int__INTC_SET_EN_REG CYREG_INTC_SET_EN1
#define USBUART_dp_int__INTC_SET_PD_REG CYREG_INTC_SET_PD1
#define USBUART_dp_int__INTC_VECT (CYREG_INTC_VECT_MBASE+0x18u)

/* Batt_Monitor */
#define Batt_Monitor__0__MASK 0x04u
#define Batt_Monitor__0__PC CYREG_PRT0_PC2
#define Batt_Monitor__0__PORT 0u
#define Batt_Monitor__0__SHIFT 2
#define Batt_Monitor__AG CYREG_PRT0_AG
#define Batt_Monitor__AMUX CYREG_PRT0_AMUX
#define Batt_Monitor__BIE CYREG_PRT0_BIE
#define Batt_Monitor__BIT_MASK CYREG_PRT0_BIT_MASK
#define Batt_Monitor__BYP CYREG_PRT0_BYP
#define Batt_Monitor__CTL CYREG_PRT0_CTL
#define Batt_Monitor__DM0 CYREG_PRT0_DM0
#define Batt_Monitor__DM1 CYREG_PRT0_DM1
#define Batt_Monitor__DM2 CYREG_PRT0_DM2
#define Batt_Monitor__DR CYREG_PRT0_DR
#define Batt_Monitor__INP_DIS CYREG_PRT0_INP_DIS
#define Batt_Monitor__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Batt_Monitor__LCD_EN CYREG_PRT0_LCD_EN
#define Batt_Monitor__MASK 0x04u
#define Batt_Monitor__PORT 0u
#define Batt_Monitor__PRT CYREG_PRT0_PRT
#define Batt_Monitor__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Batt_Monitor__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Batt_Monitor__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Batt_Monitor__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Batt_Monitor__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Batt_Monitor__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Batt_Monitor__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Batt_Monitor__PS CYREG_PRT0_PS
#define Batt_Monitor__SHIFT 2
#define Batt_Monitor__SLW CYREG_PRT0_SLW

/* USBUART_ep_0 */
#define USBUART_ep_0__ES2_PATCH 0u
#define USBUART_ep_0__INTC_CLR_EN_REG CYREG_INTC_CLR_EN3
#define USBUART_ep_0__INTC_CLR_PD_REG CYREG_INTC_CLR_PD3
#define USBUART_ep_0__INTC_MASK 0x01u
#define USBUART_ep_0__INTC_NUMBER 24u
#define USBUART_ep_0__INTC_PRIOR_NUM 6u
#define USBUART_ep_0__INTC_PRIOR_REG CYREG_INTC_PRIOR24
#define USBUART_ep_0__INTC_SET_EN_REG CYREG_INTC_SET_EN3
#define USBUART_ep_0__INTC_SET_PD_REG CYREG_INTC_SET_PD3
#define USBUART_ep_0__INTC_VECT (CYREG_INTC_VECT_MBASE+0x30u)

/* USBUART_ep_1 */
#define USBUART_ep_1__ES2_PATCH 0u
#define USBUART_ep_1__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define USBUART_ep_1__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define USBUART_ep_1__INTC_MASK 0x02u
#define USBUART_ep_1__INTC_NUMBER 1u
#define USBUART_ep_1__INTC_PRIOR_NUM 6u
#define USBUART_ep_1__INTC_PRIOR_REG CYREG_INTC_PRIOR1
#define USBUART_ep_1__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define USBUART_ep_1__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define USBUART_ep_1__INTC_VECT (CYREG_INTC_VECT_MBASE+0x02u)

/* USBUART_ep_2 */
#define USBUART_ep_2__ES2_PATCH 0u
#define USBUART_ep_2__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define USBUART_ep_2__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define USBUART_ep_2__INTC_MASK 0x04u
#define USBUART_ep_2__INTC_NUMBER 2u
#define USBUART_ep_2__INTC_PRIOR_NUM 6u
#define USBUART_ep_2__INTC_PRIOR_REG CYREG_INTC_PRIOR2
#define USBUART_ep_2__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define USBUART_ep_2__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define USBUART_ep_2__INTC_VECT (CYREG_INTC_VECT_MBASE+0x04u)

/* USBUART_ep_3 */
#define USBUART_ep_3__ES2_PATCH 0u
#define USBUART_ep_3__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define USBUART_ep_3__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define USBUART_ep_3__INTC_MASK 0x08u
#define USBUART_ep_3__INTC_NUMBER 3u
#define USBUART_ep_3__INTC_PRIOR_NUM 6u
#define USBUART_ep_3__INTC_PRIOR_REG CYREG_INTC_PRIOR3
#define USBUART_ep_3__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define USBUART_ep_3__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define USBUART_ep_3__INTC_VECT (CYREG_INTC_VECT_MBASE+0x06u)

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

/* USBUART_USB */
#define USBUART_USB__ARB_CFG CYREG_USB_ARB_CFG
#define USBUART_USB__ARB_EP1_CFG CYREG_USB_ARB_EP1_CFG
#define USBUART_USB__ARB_EP1_INT_EN CYREG_USB_ARB_EP1_INT_EN
#define USBUART_USB__ARB_EP1_SR CYREG_USB_ARB_EP1_SR
#define USBUART_USB__ARB_EP2_CFG CYREG_USB_ARB_EP2_CFG
#define USBUART_USB__ARB_EP2_INT_EN CYREG_USB_ARB_EP2_INT_EN
#define USBUART_USB__ARB_EP2_SR CYREG_USB_ARB_EP2_SR
#define USBUART_USB__ARB_EP3_CFG CYREG_USB_ARB_EP3_CFG
#define USBUART_USB__ARB_EP3_INT_EN CYREG_USB_ARB_EP3_INT_EN
#define USBUART_USB__ARB_EP3_SR CYREG_USB_ARB_EP3_SR
#define USBUART_USB__ARB_EP4_CFG CYREG_USB_ARB_EP4_CFG
#define USBUART_USB__ARB_EP4_INT_EN CYREG_USB_ARB_EP4_INT_EN
#define USBUART_USB__ARB_EP4_SR CYREG_USB_ARB_EP4_SR
#define USBUART_USB__ARB_EP5_CFG CYREG_USB_ARB_EP5_CFG
#define USBUART_USB__ARB_EP5_INT_EN CYREG_USB_ARB_EP5_INT_EN
#define USBUART_USB__ARB_EP5_SR CYREG_USB_ARB_EP5_SR
#define USBUART_USB__ARB_EP6_CFG CYREG_USB_ARB_EP6_CFG
#define USBUART_USB__ARB_EP6_INT_EN CYREG_USB_ARB_EP6_INT_EN
#define USBUART_USB__ARB_EP6_SR CYREG_USB_ARB_EP6_SR
#define USBUART_USB__ARB_EP7_CFG CYREG_USB_ARB_EP7_CFG
#define USBUART_USB__ARB_EP7_INT_EN CYREG_USB_ARB_EP7_INT_EN
#define USBUART_USB__ARB_EP7_SR CYREG_USB_ARB_EP7_SR
#define USBUART_USB__ARB_EP8_CFG CYREG_USB_ARB_EP8_CFG
#define USBUART_USB__ARB_EP8_INT_EN CYREG_USB_ARB_EP8_INT_EN
#define USBUART_USB__ARB_EP8_SR CYREG_USB_ARB_EP8_SR
#define USBUART_USB__ARB_INT_EN CYREG_USB_ARB_INT_EN
#define USBUART_USB__ARB_INT_SR CYREG_USB_ARB_INT_SR
#define USBUART_USB__ARB_RW1_DR CYREG_USB_ARB_RW1_DR
#define USBUART_USB__ARB_RW1_RA CYREG_USB_ARB_RW1_RA
#define USBUART_USB__ARB_RW1_RA_MSB CYREG_USB_ARB_RW1_RA_MSB
#define USBUART_USB__ARB_RW1_WA CYREG_USB_ARB_RW1_WA
#define USBUART_USB__ARB_RW1_WA_MSB CYREG_USB_ARB_RW1_WA_MSB
#define USBUART_USB__ARB_RW2_DR CYREG_USB_ARB_RW2_DR
#define USBUART_USB__ARB_RW2_RA CYREG_USB_ARB_RW2_RA
#define USBUART_USB__ARB_RW2_RA_MSB CYREG_USB_ARB_RW2_RA_MSB
#define USBUART_USB__ARB_RW2_WA CYREG_USB_ARB_RW2_WA
#define USBUART_USB__ARB_RW2_WA_MSB CYREG_USB_ARB_RW2_WA_MSB
#define USBUART_USB__ARB_RW3_DR CYREG_USB_ARB_RW3_DR
#define USBUART_USB__ARB_RW3_RA CYREG_USB_ARB_RW3_RA
#define USBUART_USB__ARB_RW3_RA_MSB CYREG_USB_ARB_RW3_RA_MSB
#define USBUART_USB__ARB_RW3_WA CYREG_USB_ARB_RW3_WA
#define USBUART_USB__ARB_RW3_WA_MSB CYREG_USB_ARB_RW3_WA_MSB
#define USBUART_USB__ARB_RW4_DR CYREG_USB_ARB_RW4_DR
#define USBUART_USB__ARB_RW4_RA CYREG_USB_ARB_RW4_RA
#define USBUART_USB__ARB_RW4_RA_MSB CYREG_USB_ARB_RW4_RA_MSB
#define USBUART_USB__ARB_RW4_WA CYREG_USB_ARB_RW4_WA
#define USBUART_USB__ARB_RW4_WA_MSB CYREG_USB_ARB_RW4_WA_MSB
#define USBUART_USB__ARB_RW5_DR CYREG_USB_ARB_RW5_DR
#define USBUART_USB__ARB_RW5_RA CYREG_USB_ARB_RW5_RA
#define USBUART_USB__ARB_RW5_RA_MSB CYREG_USB_ARB_RW5_RA_MSB
#define USBUART_USB__ARB_RW5_WA CYREG_USB_ARB_RW5_WA
#define USBUART_USB__ARB_RW5_WA_MSB CYREG_USB_ARB_RW5_WA_MSB
#define USBUART_USB__ARB_RW6_DR CYREG_USB_ARB_RW6_DR
#define USBUART_USB__ARB_RW6_RA CYREG_USB_ARB_RW6_RA
#define USBUART_USB__ARB_RW6_RA_MSB CYREG_USB_ARB_RW6_RA_MSB
#define USBUART_USB__ARB_RW6_WA CYREG_USB_ARB_RW6_WA
#define USBUART_USB__ARB_RW6_WA_MSB CYREG_USB_ARB_RW6_WA_MSB
#define USBUART_USB__ARB_RW7_DR CYREG_USB_ARB_RW7_DR
#define USBUART_USB__ARB_RW7_RA CYREG_USB_ARB_RW7_RA
#define USBUART_USB__ARB_RW7_RA_MSB CYREG_USB_ARB_RW7_RA_MSB
#define USBUART_USB__ARB_RW7_WA CYREG_USB_ARB_RW7_WA
#define USBUART_USB__ARB_RW7_WA_MSB CYREG_USB_ARB_RW7_WA_MSB
#define USBUART_USB__ARB_RW8_DR CYREG_USB_ARB_RW8_DR
#define USBUART_USB__ARB_RW8_RA CYREG_USB_ARB_RW8_RA
#define USBUART_USB__ARB_RW8_RA_MSB CYREG_USB_ARB_RW8_RA_MSB
#define USBUART_USB__ARB_RW8_WA CYREG_USB_ARB_RW8_WA
#define USBUART_USB__ARB_RW8_WA_MSB CYREG_USB_ARB_RW8_WA_MSB
#define USBUART_USB__BUF_SIZE CYREG_USB_BUF_SIZE
#define USBUART_USB__BUS_RST_CNT CYREG_USB_BUS_RST_CNT
#define USBUART_USB__CR0 CYREG_USB_CR0
#define USBUART_USB__CR1 CYREG_USB_CR1
#define USBUART_USB__CWA CYREG_USB_CWA
#define USBUART_USB__CWA_MSB CYREG_USB_CWA_MSB
#define USBUART_USB__DMA_THRES CYREG_USB_DMA_THRES
#define USBUART_USB__DMA_THRES_MSB CYREG_USB_DMA_THRES_MSB
#define USBUART_USB__DYN_RECONFIG CYREG_USB_DYN_RECONFIG
#define USBUART_USB__EP0_CNT CYREG_USB_EP0_CNT
#define USBUART_USB__EP0_CR CYREG_USB_EP0_CR
#define USBUART_USB__EP0_DR0 CYREG_USB_EP0_DR0
#define USBUART_USB__EP0_DR1 CYREG_USB_EP0_DR1
#define USBUART_USB__EP0_DR2 CYREG_USB_EP0_DR2
#define USBUART_USB__EP0_DR3 CYREG_USB_EP0_DR3
#define USBUART_USB__EP0_DR4 CYREG_USB_EP0_DR4
#define USBUART_USB__EP0_DR5 CYREG_USB_EP0_DR5
#define USBUART_USB__EP0_DR6 CYREG_USB_EP0_DR6
#define USBUART_USB__EP0_DR7 CYREG_USB_EP0_DR7
#define USBUART_USB__EP_ACTIVE CYREG_USB_EP_ACTIVE
#define USBUART_USB__EP_TYPE CYREG_USB_EP_TYPE
#define USBUART_USB__MEM_DATA CYREG_USB_MEM_DATA_MBASE
#define USBUART_USB__OSCLK_DR0 CYREG_USB_OSCLK_DR0
#define USBUART_USB__OSCLK_DR1 CYREG_USB_OSCLK_DR1
#define USBUART_USB__PM_ACT_CFG CYREG_PM_ACT_CFG5
#define USBUART_USB__PM_ACT_MSK 0x01u
#define USBUART_USB__PM_STBY_CFG CYREG_PM_STBY_CFG5
#define USBUART_USB__PM_STBY_MSK 0x01u
#define USBUART_USB__SIE_EP1_CNT0 CYREG_USB_SIE_EP1_CNT0
#define USBUART_USB__SIE_EP1_CNT1 CYREG_USB_SIE_EP1_CNT1
#define USBUART_USB__SIE_EP1_CR0 CYREG_USB_SIE_EP1_CR0
#define USBUART_USB__SIE_EP2_CNT0 CYREG_USB_SIE_EP2_CNT0
#define USBUART_USB__SIE_EP2_CNT1 CYREG_USB_SIE_EP2_CNT1
#define USBUART_USB__SIE_EP2_CR0 CYREG_USB_SIE_EP2_CR0
#define USBUART_USB__SIE_EP3_CNT0 CYREG_USB_SIE_EP3_CNT0
#define USBUART_USB__SIE_EP3_CNT1 CYREG_USB_SIE_EP3_CNT1
#define USBUART_USB__SIE_EP3_CR0 CYREG_USB_SIE_EP3_CR0
#define USBUART_USB__SIE_EP4_CNT0 CYREG_USB_SIE_EP4_CNT0
#define USBUART_USB__SIE_EP4_CNT1 CYREG_USB_SIE_EP4_CNT1
#define USBUART_USB__SIE_EP4_CR0 CYREG_USB_SIE_EP4_CR0
#define USBUART_USB__SIE_EP5_CNT0 CYREG_USB_SIE_EP5_CNT0
#define USBUART_USB__SIE_EP5_CNT1 CYREG_USB_SIE_EP5_CNT1
#define USBUART_USB__SIE_EP5_CR0 CYREG_USB_SIE_EP5_CR0
#define USBUART_USB__SIE_EP6_CNT0 CYREG_USB_SIE_EP6_CNT0
#define USBUART_USB__SIE_EP6_CNT1 CYREG_USB_SIE_EP6_CNT1
#define USBUART_USB__SIE_EP6_CR0 CYREG_USB_SIE_EP6_CR0
#define USBUART_USB__SIE_EP7_CNT0 CYREG_USB_SIE_EP7_CNT0
#define USBUART_USB__SIE_EP7_CNT1 CYREG_USB_SIE_EP7_CNT1
#define USBUART_USB__SIE_EP7_CR0 CYREG_USB_SIE_EP7_CR0
#define USBUART_USB__SIE_EP8_CNT0 CYREG_USB_SIE_EP8_CNT0
#define USBUART_USB__SIE_EP8_CNT1 CYREG_USB_SIE_EP8_CNT1
#define USBUART_USB__SIE_EP8_CR0 CYREG_USB_SIE_EP8_CR0
#define USBUART_USB__SIE_EP_INT_EN CYREG_USB_SIE_EP_INT_EN
#define USBUART_USB__SIE_EP_INT_SR CYREG_USB_SIE_EP_INT_SR
#define USBUART_USB__SOF0 CYREG_USB_SOF0
#define USBUART_USB__SOF1 CYREG_USB_SOF1
#define USBUART_USB__USBIO_CR0 CYREG_USB_USBIO_CR0
#define USBUART_USB__USBIO_CR1 CYREG_USB_USBIO_CR1
#define USBUART_USB__USBIO_CR2 CYREG_USB_USBIO_CR2
#define USBUART_USB__USB_CLK_EN CYREG_USB_USB_CLK_EN

/* USBUART_Dm */
#define USBUART_Dm__0__MASK 0x80u
#define USBUART_Dm__0__PC CYREG_IO_PC_PRT15_7_6_PC1
#define USBUART_Dm__0__PORT 15u
#define USBUART_Dm__0__SHIFT 7
#define USBUART_Dm__AG CYREG_PRT15_AG
#define USBUART_Dm__AMUX CYREG_PRT15_AMUX
#define USBUART_Dm__BIE CYREG_PRT15_BIE
#define USBUART_Dm__BIT_MASK CYREG_PRT15_BIT_MASK
#define USBUART_Dm__BYP CYREG_PRT15_BYP
#define USBUART_Dm__CTL CYREG_PRT15_CTL
#define USBUART_Dm__DM0 CYREG_PRT15_DM0
#define USBUART_Dm__DM1 CYREG_PRT15_DM1
#define USBUART_Dm__DM2 CYREG_PRT15_DM2
#define USBUART_Dm__DR CYREG_PRT15_DR
#define USBUART_Dm__INP_DIS CYREG_PRT15_INP_DIS
#define USBUART_Dm__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define USBUART_Dm__LCD_EN CYREG_PRT15_LCD_EN
#define USBUART_Dm__MASK 0x80u
#define USBUART_Dm__PORT 15u
#define USBUART_Dm__PRT CYREG_PRT15_PRT
#define USBUART_Dm__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define USBUART_Dm__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define USBUART_Dm__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define USBUART_Dm__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define USBUART_Dm__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define USBUART_Dm__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define USBUART_Dm__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define USBUART_Dm__PS CYREG_PRT15_PS
#define USBUART_Dm__SHIFT 7
#define USBUART_Dm__SLW CYREG_PRT15_SLW

/* USBUART_Dp */
#define USBUART_Dp__0__MASK 0x40u
#define USBUART_Dp__0__PC CYREG_IO_PC_PRT15_7_6_PC0
#define USBUART_Dp__0__PORT 15u
#define USBUART_Dp__0__SHIFT 6
#define USBUART_Dp__AG CYREG_PRT15_AG
#define USBUART_Dp__AMUX CYREG_PRT15_AMUX
#define USBUART_Dp__BIE CYREG_PRT15_BIE
#define USBUART_Dp__BIT_MASK CYREG_PRT15_BIT_MASK
#define USBUART_Dp__BYP CYREG_PRT15_BYP
#define USBUART_Dp__CTL CYREG_PRT15_CTL
#define USBUART_Dp__DM0 CYREG_PRT15_DM0
#define USBUART_Dp__DM1 CYREG_PRT15_DM1
#define USBUART_Dp__DM2 CYREG_PRT15_DM2
#define USBUART_Dp__DR CYREG_PRT15_DR
#define USBUART_Dp__INP_DIS CYREG_PRT15_INP_DIS
#define USBUART_Dp__INTSTAT CYREG_PICU15_INTSTAT
#define USBUART_Dp__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define USBUART_Dp__LCD_EN CYREG_PRT15_LCD_EN
#define USBUART_Dp__MASK 0x40u
#define USBUART_Dp__PORT 15u
#define USBUART_Dp__PRT CYREG_PRT15_PRT
#define USBUART_Dp__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define USBUART_Dp__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define USBUART_Dp__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define USBUART_Dp__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define USBUART_Dp__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define USBUART_Dp__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define USBUART_Dp__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define USBUART_Dp__PS CYREG_PRT15_PS
#define USBUART_Dp__SHIFT 6
#define USBUART_Dp__SLW CYREG_PRT15_SLW
#define USBUART_Dp__SNAP CYREG_PICU15_SNAP

/* PWM0_CTRL */
#define PWM0_CTRL_Sync_ctrl_reg__0__MASK 0x01u
#define PWM0_CTRL_Sync_ctrl_reg__0__POS 0
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB12_13_ACTL
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB12_13_CTL
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB12_13_CTL
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB12_13_CTL
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_COUNT_COUNT_REG CYREG_B0_UDB12_13_CTL
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_MASK_MASK_REG CYREG_B0_UDB12_13_MSK
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_MASK_PERIOD_REG CYREG_B0_UDB12_13_MSK
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_PERIOD_MASK_REG CYREG_B0_UDB12_13_MSK
#define PWM0_CTRL_Sync_ctrl_reg__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB12_13_MSK
#define PWM0_CTRL_Sync_ctrl_reg__1__MASK 0x02u
#define PWM0_CTRL_Sync_ctrl_reg__1__POS 1
#define PWM0_CTRL_Sync_ctrl_reg__CONTROL_AUX_CTL_REG CYREG_B0_UDB12_ACTL
#define PWM0_CTRL_Sync_ctrl_reg__CONTROL_REG CYREG_B0_UDB12_CTL
#define PWM0_CTRL_Sync_ctrl_reg__CONTROL_ST_REG CYREG_B0_UDB12_ST_CTL
#define PWM0_CTRL_Sync_ctrl_reg__COUNT_REG CYREG_B0_UDB12_CTL
#define PWM0_CTRL_Sync_ctrl_reg__COUNT_ST_REG CYREG_B0_UDB12_ST_CTL
#define PWM0_CTRL_Sync_ctrl_reg__MASK 0x03u
#define PWM0_CTRL_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB12_MSK_ACTL
#define PWM0_CTRL_Sync_ctrl_reg__PERIOD_REG CYREG_B0_UDB12_MSK
#define PWM0_CTRL_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB12_MSK_ACTL

/* PWM1_CTRL */
#define PWM1_CTRL_Sync_ctrl_reg__0__MASK 0x01u
#define PWM1_CTRL_Sync_ctrl_reg__0__POS 0
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB13_14_ACTL
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB13_14_CTL
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB13_14_CTL
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB13_14_CTL
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_COUNT_COUNT_REG CYREG_B0_UDB13_14_CTL
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_MASK_MASK_REG CYREG_B0_UDB13_14_MSK
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_MASK_PERIOD_REG CYREG_B0_UDB13_14_MSK
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_PERIOD_MASK_REG CYREG_B0_UDB13_14_MSK
#define PWM1_CTRL_Sync_ctrl_reg__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB13_14_MSK
#define PWM1_CTRL_Sync_ctrl_reg__1__MASK 0x02u
#define PWM1_CTRL_Sync_ctrl_reg__1__POS 1
#define PWM1_CTRL_Sync_ctrl_reg__CONTROL_AUX_CTL_REG CYREG_B0_UDB13_ACTL
#define PWM1_CTRL_Sync_ctrl_reg__CONTROL_REG CYREG_B0_UDB13_CTL
#define PWM1_CTRL_Sync_ctrl_reg__CONTROL_ST_REG CYREG_B0_UDB13_ST_CTL
#define PWM1_CTRL_Sync_ctrl_reg__COUNT_REG CYREG_B0_UDB13_CTL
#define PWM1_CTRL_Sync_ctrl_reg__COUNT_ST_REG CYREG_B0_UDB13_ST_CTL
#define PWM1_CTRL_Sync_ctrl_reg__MASK 0x03u
#define PWM1_CTRL_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB13_MSK_ACTL
#define PWM1_CTRL_Sync_ctrl_reg__PERIOD_REG CYREG_B0_UDB13_MSK
#define PWM1_CTRL_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB13_MSK_ACTL

/* Sensor_In */
#define Sensor_In__0__MASK 0x02u
#define Sensor_In__0__PC CYREG_PRT0_PC1
#define Sensor_In__0__PORT 0u
#define Sensor_In__0__SHIFT 1
#define Sensor_In__AG CYREG_PRT0_AG
#define Sensor_In__AMUX CYREG_PRT0_AMUX
#define Sensor_In__BIE CYREG_PRT0_BIE
#define Sensor_In__BIT_MASK CYREG_PRT0_BIT_MASK
#define Sensor_In__BYP CYREG_PRT0_BYP
#define Sensor_In__CTL CYREG_PRT0_CTL
#define Sensor_In__DM0 CYREG_PRT0_DM0
#define Sensor_In__DM1 CYREG_PRT0_DM1
#define Sensor_In__DM2 CYREG_PRT0_DM2
#define Sensor_In__DR CYREG_PRT0_DR
#define Sensor_In__INP_DIS CYREG_PRT0_INP_DIS
#define Sensor_In__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Sensor_In__LCD_EN CYREG_PRT0_LCD_EN
#define Sensor_In__MASK 0x02u
#define Sensor_In__PORT 0u
#define Sensor_In__PRT CYREG_PRT0_PRT
#define Sensor_In__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Sensor_In__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Sensor_In__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Sensor_In__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Sensor_In__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Sensor_In__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Sensor_In__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Sensor_In__PS CYREG_PRT0_PS
#define Sensor_In__SHIFT 1
#define Sensor_In__SLW CYREG_PRT0_SLW

/* Vbus_IRQ */
#define Vbus_IRQ__ES2_PATCH 0u
#define Vbus_IRQ__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define Vbus_IRQ__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define Vbus_IRQ__INTC_MASK 0x20u
#define Vbus_IRQ__INTC_NUMBER 5u
#define Vbus_IRQ__INTC_PRIOR_NUM 7u
#define Vbus_IRQ__INTC_PRIOR_REG CYREG_INTC_PRIOR5
#define Vbus_IRQ__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define Vbus_IRQ__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define Vbus_IRQ__INTC_VECT (CYREG_INTC_VECT_MBASE+0x0Au)

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

/* RGB_LED */
#define RGB_LED__0__MASK 0x20u
#define RGB_LED__0__PC CYREG_PRT2_PC5
#define RGB_LED__0__PORT 2u
#define RGB_LED__0__SHIFT 5
#define RGB_LED__1__MASK 0x40u
#define RGB_LED__1__PC CYREG_PRT2_PC6
#define RGB_LED__1__PORT 2u
#define RGB_LED__1__SHIFT 6
#define RGB_LED__2__MASK 0x80u
#define RGB_LED__2__PC CYREG_PRT2_PC7
#define RGB_LED__2__PORT 2u
#define RGB_LED__2__SHIFT 7
#define RGB_LED__AG CYREG_PRT2_AG
#define RGB_LED__AMUX CYREG_PRT2_AMUX
#define RGB_LED__BIE CYREG_PRT2_BIE
#define RGB_LED__BIT_MASK CYREG_PRT2_BIT_MASK
#define RGB_LED__BYP CYREG_PRT2_BYP
#define RGB_LED__CTL CYREG_PRT2_CTL
#define RGB_LED__DM0 CYREG_PRT2_DM0
#define RGB_LED__DM1 CYREG_PRT2_DM1
#define RGB_LED__DM2 CYREG_PRT2_DM2
#define RGB_LED__DR CYREG_PRT2_DR
#define RGB_LED__INP_DIS CYREG_PRT2_INP_DIS
#define RGB_LED__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define RGB_LED__LCD_EN CYREG_PRT2_LCD_EN
#define RGB_LED__MASK 0xE0u
#define RGB_LED__PORT 2u
#define RGB_LED__PRT CYREG_PRT2_PRT
#define RGB_LED__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define RGB_LED__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define RGB_LED__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define RGB_LED__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define RGB_LED__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define RGB_LED__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define RGB_LED__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define RGB_LED__PS CYREG_PRT2_PS
#define RGB_LED__SHIFT 5
#define RGB_LED__SLW CYREG_PRT2_SLW

/* RTC_isr */
#define RTC_isr__ES2_PATCH 0u
#define RTC_isr__INTC_CLR_EN_REG CYREG_INTC_CLR_EN0
#define RTC_isr__INTC_CLR_PD_REG CYREG_INTC_CLR_PD0
#define RTC_isr__INTC_MASK 0x01u
#define RTC_isr__INTC_NUMBER 0u
#define RTC_isr__INTC_PRIOR_NUM 7u
#define RTC_isr__INTC_PRIOR_REG CYREG_INTC_PRIOR0
#define RTC_isr__INTC_SET_EN_REG CYREG_INTC_SET_EN0
#define RTC_isr__INTC_SET_PD_REG CYREG_INTC_SET_PD0
#define RTC_isr__INTC_VECT (CYREG_INTC_VECT_MBASE+0x00u)

/* Vbus */
#define Vbus__0__MASK 0x80u
#define Vbus__0__PC CYREG_PRT1_PC7
#define Vbus__0__PORT 1u
#define Vbus__0__SHIFT 7
#define Vbus__AG CYREG_PRT1_AG
#define Vbus__AMUX CYREG_PRT1_AMUX
#define Vbus__BIE CYREG_PRT1_BIE
#define Vbus__BIT_MASK CYREG_PRT1_BIT_MASK
#define Vbus__BYP CYREG_PRT1_BYP
#define Vbus__CTL CYREG_PRT1_CTL
#define Vbus__DM0 CYREG_PRT1_DM0
#define Vbus__DM1 CYREG_PRT1_DM1
#define Vbus__DM2 CYREG_PRT1_DM2
#define Vbus__DR CYREG_PRT1_DR
#define Vbus__INP_DIS CYREG_PRT1_INP_DIS
#define Vbus__INTSTAT CYREG_PICU1_INTSTAT
#define Vbus__LCD_COM_SEG CYREG_PRT1_LCD_COM_SEG
#define Vbus__LCD_EN CYREG_PRT1_LCD_EN
#define Vbus__MASK 0x80u
#define Vbus__PORT 1u
#define Vbus__PRT CYREG_PRT1_PRT
#define Vbus__PRTDSI__CAPS_SEL CYREG_PRT1_CAPS_SEL
#define Vbus__PRTDSI__DBL_SYNC_IN CYREG_PRT1_DBL_SYNC_IN
#define Vbus__PRTDSI__OE_SEL0 CYREG_PRT1_OE_SEL0
#define Vbus__PRTDSI__OE_SEL1 CYREG_PRT1_OE_SEL1
#define Vbus__PRTDSI__OUT_SEL0 CYREG_PRT1_OUT_SEL0
#define Vbus__PRTDSI__OUT_SEL1 CYREG_PRT1_OUT_SEL1
#define Vbus__PRTDSI__SYNC_OUT CYREG_PRT1_SYNC_OUT
#define Vbus__PS CYREG_PRT1_PS
#define Vbus__SHIFT 7
#define Vbus__SLW CYREG_PRT1_SLW
#define Vbus__SNAP CYREG_PICU1_SNAP

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
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
#define CYDEV_CHIP_JTAG_ID 0x1E093069u
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
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_JTAG_5
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 1
#define CYDEV_DEBUG_ENABLE_MASK 0x01u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000000u
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_USB_CLK_OSC_LOCKING_ENABLED_AT_PWR_UP 
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 3.3
#define CYDEV_VDDIO1_MV 3300
#define CYDEV_VDDIO2 3.3
#define CYDEV_VDDIO2_MV 3300
#define CYDEV_VDDIO3 3.3
#define CYDEV_VDDIO3_MV 3300
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 3.3
#define CYDEV_VIO1_MV 3300
#define CYDEV_VIO2 3.3
#define CYDEV_VIO2_MV 3300
#define CYDEV_VIO3 3.3
#define CYDEV_VIO3_MV 3300
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
