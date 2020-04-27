`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:25:32 PM
// Design Name: 
// Module Name: full_adder
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

//1 bit Full Adder
module full_adder(
output wire sum,
output wire cout,
input wire in1,
input wire in2,
input wire cin
    );
wire temp1;
wire temp2;
wire temp3;
xor(sum,in1,in2,cin);
and(temp1,in1,in2);
and(temp2,in1,cin);
and(temp3,in2,cin);
or(cout,temp1,temp2,temp3);
endmodule
