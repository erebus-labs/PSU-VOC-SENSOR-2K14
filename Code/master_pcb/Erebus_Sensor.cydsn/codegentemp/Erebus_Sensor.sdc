# THIS FILE IS AUTOMATICALLY GENERATED
# Project: E:\Capstone\Workspaces\master_pcb\Erebus_Sensor.cydsn\Erebus_Sensor.cyprj
# Date: Fri, 06 Jun 2014 05:00:47 GMT
#set_units -time ns
create_clock -name {ADC_Ext_CP_Clk(routed)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyXTAL_32kHz} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/clk_32k_xtal}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_clock -name {ADC_Ext_CP_Clk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 161 321} -nominal_period 6666.6666666666661 [list [get_pins {ClockBlock/aclk_glb_0}]]
create_clock -name {ADC_theACLK(fixed-function)} -period 6666.6666666666661 -waveform {0 3333.33333333333} -nominal_period 6666.6666666666661 [get_pins {ClockBlock/aclk_glb_ff_0}]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for E:\Capstone\Workspaces\master_pcb\Erebus_Sensor.cydsn\TopDesign\TopDesign.cysch
# Project: E:\Capstone\Workspaces\master_pcb\Erebus_Sensor.cydsn\Erebus_Sensor.cyprj
# Date: Fri, 06 Jun 2014 05:00:35 GMT
