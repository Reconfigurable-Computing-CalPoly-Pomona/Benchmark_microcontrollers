`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 04:58:59 PM
// Design Name: 
// Module Name: normalize
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


module normalize(
output wire[22:0] adj_mantissa, //adjusted mantissa (after extracting our required part)
output wire norm_flag,
input wire[47:0] prdt
    ); //returns norm = 1 if normalization needs to be done
and(norm_flag,prdt[47],1'b1); //sel = 1 if leading one is at 47 ... needs normalization
//if sel = 0, leading zero not at 47 ... no need of normalization
//wire[1:0] results[22:0]; //Mantissa result is all zeros
wire[22:0] results[1:0];
assign results[0] = prdt[45:23];
assign results[1] = prdt[46:24];
assign adj_mantissa = {results[norm_flag+0]};
endmodule
