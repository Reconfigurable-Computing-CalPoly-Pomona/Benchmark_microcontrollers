// specifiy I/O core parameters in this level 

`include "chu_io_map.svh"
module mmio_sys_sampler
#(
  parameter N_SW = 8,
            N_LED = 8
)	
(
   input logic clk,
   input logic reset,
   // FPro bus 
   input  logic mmio_cs,
   input  logic mmio_wr,
   input  logic mmio_rd,
   input  logic [20:0] mmio_addr, 
   input  logic [31:0] mmio_wr_data,
   output logic [31:0] mmio_rd_data,
   // switches and LEDs
   input  logic [N_SW-1:0] sw,
   output logic [N_LED-1:0] led,
   // uart
   input  logic rx,
   output logic tx,          
   // 4 analog input pair
   input  logic [3:0] adc_p, adc_n,
   // pwm 
   output logic [7:0] pwm,
   // btn
   input logic [4:0] btn,
   // 8-digit 7-seg LEDs
   output logic [7:0] an,
   output logic [7:0] sseg,
   // spi accelerator
   output logic acl_sclk, acl_mosi,
   input  logic acl_miso,
   output logic acl_ss,
   // i2c temperature sensor  
   output logic tmp_i2c_scl,
   inout  tri tmp_i2c_sda,
   // ps2
   inout  tri ps2d,
   inout  tri ps2c,
   // ddfs square wave output
   output  logic  ddfs_sq_wave,
   // 1-bit dac 
    output logic  pdm 
);

   //declaration
   logic [63:0] mem_rd_array;
   logic [63:0] mem_wr_array;
   logic [63:0] cs_array;
   logic [4:0] reg_addr_array [63:0];
   logic [31:0] rd_data_array [63:0]; 
   logic [31:0] wr_data_array [63:0];
   logic [15:0] adsr_env;

   // body
   // instantiate mmio controller 
   chu_mmio_controller ctrl_unit
   (.clk(clk),
    .reset(reset),
    .mmio_cs(mmio_cs),
    .mmio_wr(mmio_wr),
    .mmio_rd(mmio_rd),
    .mmio_addr(mmio_addr), 
    .mmio_wr_data(mmio_wr_data),
    .mmio_rd_data(mmio_rd_data),
    // slot interface
    .slot_cs_array(cs_array),
    .slot_mem_rd_array(mem_rd_array),
    .slot_mem_wr_array(mem_wr_array),
    .slot_reg_addr_array(reg_addr_array),
    .slot_rd_data_array(rd_data_array), 
    .slot_wr_data_array(wr_data_array)
    );
  
   // slot 0: system timer 
   chu_timer timer_slot0 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S0_SYS_TIMER]),
    .read(mem_rd_array[`S0_SYS_TIMER]),
    .write(mem_wr_array[`S0_SYS_TIMER]),
    .addr(reg_addr_array[`S0_SYS_TIMER]),
    .rd_data(rd_data_array[`S0_SYS_TIMER]),
    .wr_data(wr_data_array[`S0_SYS_TIMER])
    );

   // slot 1: UART 
   chu_uart #(.FIFO_DEPTH_BIT(8))  uart_slot1 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S1_UART1]),
    .read(mem_rd_array[`S1_UART1]),
    .write(mem_wr_array[`S1_UART1]),
    .addr(reg_addr_array[`S1_UART1]),
    .rd_data(rd_data_array[`S1_UART1]),
    .wr_data(wr_data_array[`S1_UART1]), 
    .tx(tx),
    .rx(rx)
    );

   // slot 2: gpo 
   chu_gpo #(.W(N_LED)) gpo_slot2 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S2_LED]),
    .read(mem_rd_array[`S2_LED]),
    .write(mem_wr_array[`S2_LED]),
    .addr(reg_addr_array[`S2_LED]),
    .rd_data(rd_data_array[`S2_LED]),
    .wr_data(wr_data_array[`S2_LED]),
    .dout(led)
    );

   // slot 3: gpi 
   chu_gpi #(.W(N_SW)) gpi_slot3 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S3_SW]),
    .read(mem_rd_array[`S3_SW]),
    .write(mem_wr_array[`S3_SW]),
    .addr(reg_addr_array[`S3_SW]),
    .rd_data(rd_data_array[`S3_SW]),
    .wr_data(wr_data_array[`S3_SW]),
    .din(sw)
    );
    
    // slot 4: Adder 
    holl_add adder_slot4 
    (.clk(clk),
     .reset(reset),
     .cs(cs_array[`S4_ADD]),
     .read(mem_rd_array[`S4_ADD]),
     .write(mem_wr_array[`S4_ADD]),
     .addr(reg_addr_array[`S4_ADD]),
     .rd_data(rd_data_array[`S4_ADD]),
     .wr_data(wr_data_array[`S4_ADD])
     );
   //assign rd_data_array[`S4_USER] = 32'h00000000;
   
   // slot 5: Multiplier
   holl_mult multiplier_slot5 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S5_MULT]),
    .read(mem_rd_array[`S5_MULT]),
    .write(mem_wr_array[`S5_MULT]),
    .addr(reg_addr_array[`S5_MULT]),
    .rd_data(rd_data_array[`S5_MULT]),
    .wr_data(wr_data_array[`S5_MULT])
    );
    
   // slot 6: Divider
    holl_div divider_slot6 //
    (.clk(clk),
     .reset(reset),
     .cs(cs_array[`S6_DIV]),
     .read(mem_rd_array[`S6_DIV]),
     .write(mem_wr_array[`S6_DIV]),
     .addr(reg_addr_array[`S6_DIV]),
     .rd_data(rd_data_array[`S6_DIV]),
     .wr_data(wr_data_array[`S6_DIV])
     );
     
    // slot 6: Shift 
     elk_shift shifter_slot7 //
     (.clk(clk),
      .reset(reset),
      .cs(cs_array[`S7_SHFT]),
      .read(mem_rd_array[`S7_SHFT]),
      .write(mem_wr_array[`S7_SHFT]),
      .addr(reg_addr_array[`S7_SHFT]),
      .rd_data(rd_data_array[`S7_SHFT]),
      .wr_data(wr_data_array[`S7_SHFT])
      );
       
   // slot 8: Data1
   holl_data data1_slot8 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S8_RAM1]),
    .read(mem_rd_array[`S8_RAM1]),
    .write(mem_wr_array[`S8_RAM1]),
    .addr(reg_addr_array[`S8_RAM1]),
    .rd_data(rd_data_array[`S8_RAM1]),
    .wr_data(wr_data_array[`S8_RAM1])
    );
    
   // slot 9: Data2 
   holl_data  data2_slot9 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S9_RAM2]),
    .read(mem_rd_array[`S9_RAM2]),
    .write(mem_wr_array[`S9_RAM2]),
    .addr(reg_addr_array[`S9_RAM2]),
    .rd_data(rd_data_array[`S9_RAM2]),
    .wr_data(wr_data_array[`S9_RAM2])
    );
    
   // slot 10: 
    holl_FPadd FPadder_slot10 
    (.clk(clk),
     .reset(reset),
     .cs(cs_array[`S10_FPA]),
     .read(mem_rd_array[`S10_FPA]),
     .write(mem_wr_array[`S10_FPA]),
     .addr(reg_addr_array[`S10_FPA]),
     .rd_data(rd_data_array[`S10_FPA]),
     .wr_data(wr_data_array[`S10_FPA])
     );
     
   // slot 11: Floating Point Multiplication
    Shank_FPmult FPmultiplier_slot11 
    (.clk(clk),
     .reset(reset),
     .cs(cs_array[`S11_FPM]),
     .read(mem_rd_array[`S11_FPM]),
     .write(mem_wr_array[`S11_FPM]),
     .addr(reg_addr_array[`S11_FPM]),
     .rd_data(rd_data_array[`S11_FPM]),
     .wr_data(wr_data_array[`S11_FPM])
     );
     
   // slot 12: Floating Point Division 
   holl_FPdiv FPdivider_slot12 
   (.clk(clk),
    .reset(reset),
    .cs(cs_array[`S12_FPD]),
    .read(mem_rd_array[`S12_FPD]),
    .write(mem_wr_array[`S12_FPD]),
    .addr(reg_addr_array[`S12_FPD]),
    .rd_data(rd_data_array[`S12_FPD]),
    .wr_data(wr_data_array[`S12_FPD])
    );
    
//   // slot 13: adsr 
//   chu_adsr_core adsr_slot13 
//   (.clk(clk),
//    .reset(reset),
//    .cs(cs_array[`S13_ADSR]),
//    .read(mem_rd_array[`S13_ADSR]),
//    .write(mem_wr_array[`S13_ADSR]),
//    .addr(reg_addr_array[`S13_ADSR]),
//    .rd_data(rd_data_array[`S13_ADSR]),
//    .wr_data(wr_data_array[`S13_ADSR]),
//    .adsr_env(adsr_env)
//    );

   // assign 0's to all unused slot rd_data signals
   generate
      genvar i;
      for (i=14; i<64; i=i+1) begin
         assign rd_data_array[i] = 32'h0;
      end
   endgenerate
endmodule



