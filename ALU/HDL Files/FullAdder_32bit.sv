`timescale 1ns / 1ps

module FullAdder_32bit(
input [31:0] A, B,
input CarryIn,
output CarryOut,
output [31:0] Sum
);
wire [31:0] S;
wire d, C;

FullAdder_16bit E0(.X(A[15:0]), .Y(B[15:0]), .Ci(CarryIn), .Sum(S[15:0]), .Co(d));
FullAdder_16bit E1(.X(A[31:16]), .Y(B[31:16]), .Ci(d), .Sum(S[31:16]), .Co(C));

assign Sum = S;
assign CarryOut = C;
endmodule