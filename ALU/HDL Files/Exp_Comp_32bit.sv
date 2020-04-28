`timescale 1ns / 1ps
module Exp_Comp_32bit(
input [31:0] Addend1, Addend2,
input clk,
output [31:0] NormalizedL, NormalizedS,
output LargerSign, SmallerSign,
output [7:0] LargerExpo
    );
    
    logic [7:0] exp_diff, expTemp;
    logic [31:0] Working1_Larger, Working2_Smaller;
    logic LargeSign, SmallSign;
    
    always_ff @(posedge clk)
        begin
        
        if(Addend1[30:23] > Addend2[30:23]) //input1 is larger then input2
            begin
            exp_diff = Addend1[30:23] - Addend2[30:23];
            Working2_Smaller = ({1'b1, Addend2[22:0]} >> (exp_diff))|32'h00000000;
            Working1_Larger = ({1'b1 , Addend1[22:0]})|32'h00000000;
            SmallSign = Addend2[31];
            LargeSign = Addend1[31];
            expTemp = Addend1[30:23];
            end
        if(Addend1[30:23] < Addend2[30:23]) //input2 is larger than input1
            begin
            exp_diff = Addend2[30:23] - Addend1[30:23];
            Working2_Smaller = ({1'b1, Addend1[22:0]} >> (exp_diff))|32'h00000000;//normalizing
            Working1_Larger = ({1'b1, Addend2[22:0]})|32'h00000000;
            SmallSign = Addend1[31];
            LargeSign = Addend2[31];
            expTemp = Addend2[30:23];
            end
            
        if(Addend1[30:23] == Addend2[30:23]) //input1 is larger then input2
            begin
            Working2_Smaller = {1'b1, Addend2[22:0]}|32'h00000000;
            Working1_Larger = {1'b1, Addend1[22:0]}|32'h00000000;
            SmallSign = Addend2[31];
            LargeSign = Addend1[31];
            expTemp = Addend1[30:23];
            end
        end
    
    assign LargerExpo = expTemp;
    assign LargerSign = LargeSign;
    assign SmallerSign = SmallSign;
    assign NormalizedL = Working1_Larger;
    assign NormalizedS = Working2_Smaller;
    
endmodule

