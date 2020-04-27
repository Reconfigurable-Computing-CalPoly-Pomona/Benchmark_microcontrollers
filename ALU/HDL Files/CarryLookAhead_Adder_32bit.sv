//with help from fpga4student.com
`timescale 1ns / 1ps
module CarryLookAhead_Adder_32bit(
    input [31:0] Addend1, Addend2,
    input CarryIn,
    output [31:0] Sum,
    output CarryOut
);

logic [31:0] P, G;
logic [32:0] C;

assign C[0] = CarryIn;
assign CarryOut = C[32];

genvar i, j;
    generate

    for(i = 0; i < 32; i++) begin: CarryLookAhead
        assign G[i] = Addend1[i]&Addend2[i];
        assign P[i] = Addend1[i]|Addend2[i];
        assign C[i+1] = G[i]|(P[i]&C[i]);
    end

    for(j = 0; j < 32; j++) begin: Adder
        assign Sum[j] = Addend1[j]^Addend2[j]^C[j];
    end 
endgenerate 

endmodule