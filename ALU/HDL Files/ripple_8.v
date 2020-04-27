`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:29:28 PM
// Design Name: 
// Module Name: ripple_8
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

//8 bit Ripple-carry adder
module ripple_8(
output wire[7:0] sum,
output wire cout,
input wire[7:0] in1,
input wire[7:0] in2,
input wire cin
    );
wire c1,c2,c3,c4,c5,c6,c7;
full_adder FA1(sum[0],c1,in1[0],in2[0],cin);
full_adder FA2(sum[1],c2,in1[1],in2[1],c1);
full_adder FA3(sum[2],c3,in1[2],in2[2],c2);
full_adder FA4(sum[3],c4,in1[3],in2[3],c3);
full_adder FA5(sum[4],c5,in1[4],in2[4],c4);
full_adder FA6(sum[5],c6,in1[5],in2[5],c5);
full_adder FA7(sum[6],c7,in1[6],in2[6],c6);
full_adder FA8(sum[7],cout,in1[7],in2[7],c7);
endmodule
