`ifndef _CHU_IO_MAP_INCLUDED
`define _CHU_IO_MAP_INCLUDED

// system clock rate in MHz; used for timer, uart, ddfs etc
`define SYS_CLK_FREQ 100

//io base address for microBlaze MCS
`define BRIDGE_BASE 0xc0000000

// slot module definition
// format: SLOT`_ModuleType_Name
`define S0_SYS_TIMER  0
`define S1_UART1      1
`define S2_LED        2
`define S3_SW         3
`define S4_ADD        4
`define S5_MULT       5
`define S6_DIV        6
`define S7_SHFT       7
`define S8_RAM1       8
`define S9_RAM2       9
`define S10_FPA      10
`define S11_FPM      11
`define S12_FPD     12
`define S13_ADSR     13

// video module definition
`define V0_SYNC      0
`define V1_MOUSE     1
`define V2_OSD       2
`define V3_GHOST     3
`define V4_USER4     4
`define V5_USER5     5
`define V6_GRAY      6
`define V7_BAR       7

// video frame buffer
`define FRAME_OFFSET 0x00c00000
`define FRAME_BASE   BRIDGE_BASE+FRAME_OFFSET

`endif //_CHU_IO_MAP

