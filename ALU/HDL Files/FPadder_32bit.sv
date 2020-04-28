`timescale 1ns / 1ps

module FPadder_32bit(
input clk,
input [31:0] Addend1, Addend2,
output [31:0] Sum
    );
    logic [31:0] out, NormalizedL, NormalizedS;
    logic [7:0] LargerExpo;
    logic LargerSign, SmallerSign; 

Exp_Comp_32bit A0 (.Addend1(Addend1), .Addend2(Addend2), .*);
Adder_32bit_Signed A1 (.Sum(out), .*);
assign Sum = out;
    
endmodule
