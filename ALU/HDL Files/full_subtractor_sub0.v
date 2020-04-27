`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:39:15 PM
// Design Name: 
// Module Name: full_subtractor_sub0
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

// 1 bit subtractor with subtrahend = 0
module full_subtractor_sub0(
output wire diff,  //difference
output wire bout,  //borrow out
input wire min,    //minuend
input wire bin     //borrow out
    );
xor(diff,min,bin);
and(bout,~min,bin);
endmodule
