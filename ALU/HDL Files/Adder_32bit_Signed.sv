`timescale 1ns / 1ps

module Adder_32bit_Signed(
input [31:0] Value1_Larger, Value2_Smaller,
output [31:0] Sum
    );
    logic [8:0] tempExp;
    logic [23:0] WorkingSum = 24'b000000000000000000000000;
    
    always_comb
    begin
    if(Value1_Larger[31] == 1) //larger is neg
        begin
        if(Value2_Smaller[31] == 1) //smaller is neg
            begin
            WorkingSum = Value1_Larger[22:0] + Value2_Smaller[22:0];
                if(WorkingSum[23] == 1) //overflow
                        tempExp = Value1_Larger[31:23] + 8'b00000001;
                else
                        tempExp = Value1_Larger[31:23];
            end
        if(Value2_Smaller[31] == 0) //smaller is pos
            begin
            WorkingSum = Value1_Larger[22:0] - Value2_Smaller[22:0];
            tempExp = Value1_Larger[31:23];
            end
        end
    if(Value1_Larger[31] == 0) //larger is pos
        begin
        if(Value2_Smaller[31] == 1) //smaller is neg
            begin
            WorkingSum = Value1_Larger[22:0] - Value2_Smaller[22:0];
            tempExp = Value1_Larger[31:23];
            end
        if(Value2_Smaller[31] == 0) //smaller is pos
            begin
            WorkingSum = Value1_Larger[22:0] + Value2_Smaller[22:0];
                if(WorkingSum[23] == 1) //overflow
                        tempExp = Value1_Larger[31:23] + 8'b00000001;
                else
                        tempExp = Value1_Larger[31:23];
            end
        end
    end
 
 assign Sum = {tempExp, WorkingSum[21:0], 1'b0}; 
    
endmodule
