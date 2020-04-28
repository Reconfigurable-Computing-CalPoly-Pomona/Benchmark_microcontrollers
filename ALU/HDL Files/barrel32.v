`timescale 1ns / 1ps

//written by Bob Elkind on forums.Xilinx.com

module barrel32(Data_IN, Sel, Data_OUT);

    input   [31:0]    Data_IN;
    input   [4:0]     Sel;
    output  [31:0]    Data_OUT;
    
    reg     [31:0]    Lvl1 = 0, Lvl2 = 0, Lvl3 = 0; // not really registers, Verilog compliance
    wire    [63:0]    Stage1, Stage2;     // wires to simplify FOR loops
    integer           i, j;               // loop variables
    
    always @(*) Lvl1 <= Sel[4] ? {Data_IN[15:0], Data_IN[31:16]} : Data_IN; // rotate {0 | 16} bits
    
    assign Stage1 = {Lvl1, Lvl1};    // wraparound a la Verilog
    
    always @(*)    // rotate {0 | 4 | 8 | 12} bits
      case (Sel[3:2])
         2'b00:  Lvl2 <= Stage1[31:0];       // rotate by 0
         2'b01:  for (i=0; i<=31; i=i+1)  Lvl2[i] <= Stage1[i+4];  // rotate by 4
         2'b10:  for (i=0; i<=31; i=i+1)  Lvl2[i] <= Stage1[i+8];  // rotate by 8
         2'b11:  for (i=0; i<=31; i=i+1)  Lvl2[i] <= Stage1[i+12]; // rotate by 12
      endcase
    
    assign Stage2 = {Lvl2, Lvl2};    // wraparound a la Verilog
    
    always @(*)    // rotate {0 | 1 | 2 | 3} bits
      case (Sel[1:0])
         2'b00:  Lvl3 <= Stage2[31:0];       // rotate by 0
         2'b01:  for (j=0; j<=31; j=j+1)  Lvl3[j] <= Stage2[j+1];  // rotate by 1
         2'b10:  for (j=0; j<=31; j=j+1)  Lvl3[j] <= Stage2[j+2];  // rotate by 2
         2'b11:  for (j=0; j<=31; j=j+1)  Lvl3[j] <= Stage2[j+3];  // rotate by 3
    
      endcase
    
    assign Data_OUT = Lvl3;

endmodule
