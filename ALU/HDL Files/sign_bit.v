`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:22:38 PM
// Design Name: 
// Module Name: sign_bit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sign_bit(
output wire sign,
input wire[31:0] in1,
input wire[31:0] in2
    );
xor(sign,in1[31],in2[31]);
endmodule
