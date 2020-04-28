`timescale 1ns / 1ps

module Adder_32bit_Signed(
input [31:0] NormalizedL, NormalizedS,
input LargerSign, SmallerSign,
input [7:0] LargerExpo,
output [31:0] Sum
    );
    logic [7:0] tempExp;
    logic [32:0] WorkingSum = 24'b000000000000000000000000;
    logic [22:0] OutSum;
    
    always_comb
    begin
    if(LargerSign == 1) //larger is neg
        begin
        if(SmallerSign == 1) //smaller is neg
            begin
                WorkingSum = NormalizedL + NormalizedS;
                    if(WorkingSum[24] == 1) //overflow
                            begin
                                tempExp = LargerExpo + 8'b00000001;
                                OutSum = WorkingSum[23:1];
                            end
                    else
                            begin
                                tempExp = LargerExpo;
                                OutSum = WorkingSum[22:0];
                            end
            end
        if(SmallerSign == 0) //smaller is pos
            begin
                WorkingSum = NormalizedL - NormalizedS;
                tempExp = LargerExpo;
                OutSum = WorkingSum[22:0];
            end
        end
    if(LargerSign == 0) //larger is pos
        begin
        if(SmallerSign == 1) //smaller is neg
            begin
                WorkingSum = NormalizedL - NormalizedS;
                tempExp = LargerExpo;
                OutSum = WorkingSum[22:0];
            end
        if(SmallerSign == 0) //smaller is pos
            begin
                WorkingSum = NormalizedL + NormalizedS;
                    if(WorkingSum[24] == 1) //overflow
                            begin
                                tempExp = LargerExpo + 8'b00000001;
                                OutSum = WorkingSum[23:1];
                            end
                    else
                            begin
                                tempExp = LargerExpo;
                                OutSum = WorkingSum[22:0];
                            end
            end
        end
    end
 
 assign Sum = {LargerSign, tempExp, OutSum}; 
    
endmodule
