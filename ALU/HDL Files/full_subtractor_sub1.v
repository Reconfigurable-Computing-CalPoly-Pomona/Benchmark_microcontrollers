`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:36:39 PM
// Design Name: 
// Module Name: full_subtractor_sub1
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

// Subtractor with subtrahend = 1
module full_subtractor_sub1(
output wire diff,  //difference
output wire bout,  //borrow out
input wire min,    // minuend
input wire bin     // borrow in
    );
xnor(diff,min,bin);
or(bout,~min,bin);
endmodule
