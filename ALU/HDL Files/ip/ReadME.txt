You will need to create a MicroBlaze processor named "cpu"
-input clock frequency 100MHz
-memory size of 128KB
-enable IO bus
-No UART, FIT, PIT, GPO, GPI, Interrupts

You will need to create a clocking wizard block named "mmcm_fpro"
-two inputs (reset, clk_in_100M)
-five outputs (clk_100M, clk_25M, clk40M, clk_67M, locked)