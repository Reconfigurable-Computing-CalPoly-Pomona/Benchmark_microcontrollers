`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:41:35 PM
// Design Name: 
// Module Name: subtractor_9
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

//9 bit subtractor
module subtractor_9(
output wire [8:0] diff,
output wire bout,
input wire[8:0] min,
input wire bin
    );
wire b1,b2,b3,b4,b5,b6,b7,b8;
full_subtractor_sub1 sub1(diff[0],b1,min[0],bin);
full_subtractor_sub1 sub2(diff[1],b2,min[1],b1);
full_subtractor_sub1 sub3(diff[2],b3,min[2],b2);
full_subtractor_sub1 sub4(diff[3],b4,min[3],b3);
full_subtractor_sub1 sub5(diff[4],b5,min[4],b4);
full_subtractor_sub1 sub6(diff[5],b6,min[5],b5);
full_subtractor_sub1 sub7(diff[6],b7,min[4],b6);
full_subtractor_sub0 sub8(diff[7],b8,min[7],b7);  //Two most significant subtrahends are 0 in 001111111
full_subtractor_sub0 sub9(diff[8],bout,min[8],b8);
endmodule
