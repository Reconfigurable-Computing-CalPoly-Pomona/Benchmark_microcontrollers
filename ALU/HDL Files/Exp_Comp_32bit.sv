`timescale 1ns / 1ps

    //32 bit Floating Point Adder
    //1 bit Sign (0+ & 1-), 8 bit Exponent, 23 bit Single Precision Representation

module Exp_Comp_32bit(
input [31:0] Addend1, Addend2,
input clk,
output [31:0] Value1_Larger, Value2_Smaller
    );
    
    logic [7:0] exp_diff;
    logic [31:0] Working1_Larger;
    logic [22:0] Working2_Smaller;
    logic SmallerSign;
    
    always_ff @(posedge clk)
        begin
        
        if(Addend1[30:23] > Addend2[30:23]) //input1 is larger then input2
            begin
            exp_diff = Addend1[30:23] - Addend2[30:23];
            Working2_Smaller = ({1'b1, Addend2[22:0]} >> (exp_diff+1));//|23'b00000000000000000000000;
            Working1_Larger = ({Addend1[31:23], 1'b1 , Addend1[22:0]} >> 1);
            SmallerSign = Addend2[31];
            end
        if(Addend1[30:23] < Addend2[30:23]) //input2 is larger than input1
            begin
            exp_diff = Addend2[30:23] - Addend1[30:23];
            Working2_Smaller = ({1'b1, Addend1[22:0]} >> (exp_diff+1));//normalizing
            Working1_Larger = ({Addend2[31:23], 1'b1, Addend2[22:0]}) >> 1;
            SmallerSign = Addend1[31];
            end
            
        if(Addend1[30:23] == Addend2[30:23]) //input1 is larger then input2
            begin
            Working2_Smaller = {1'b1, Addend2[22:0]}>>1;
            Working1_Larger = {Addend1[31:23], 1'b1, Addend1[22:0]}>>1;
            SmallerSign = Addend2[31];
            end
        end
    
    assign Value1_Larger = Working1_Larger;
    assign Value2_Smaller = {SmallerSign, Working1_Larger[30:23], Working2_Smaller};
    
endmodule
