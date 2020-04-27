`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 04:45:43 PM
// Design Name: 
// Module Name: product
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


module product(
output wire[47:0] sum,
input wire[23:0] min,
input wire[23:0] q
    );
    
assign sum = min*q;
    
//wire[23:0] temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10; //diagonal m
//wire[23:0] temp11,temp12,temp13,temp14,temp15,temp16,temp17,temp18,temp19,temp20;
//wire[23:0] temp21,temp22,temp23,temp24;
//wire[23:0] ptemp1,ptemp2,ptemp3,ptemp4,ptemp5,ptemp6,ptemp7,ptemp8,ptemp9,ptemp10; //vertical p
//wire[23:0] ptemp11,ptemp12,ptemp13,ptemp14,ptemp15,ptemp16,ptemp17,ptemp18,ptemp19,ptemp20;
//wire[23:0] ptemp21,ptemp22,ptemp23;
//row r1 (ptemp1,temp1,sum[0],min,24'h000000,q[0]);
//row r2 (ptemp2,temp2,sum[1],temp1,ptemp1,q[1]);
//row r3 (ptemp3,temp3,sum[2],temp2,ptemp2,q[2]);
//row r4 (ptemp4,temp4,sum[3],temp3,ptemp3,q[3]);
//row r5 (ptemp5,temp5,sum[4],temp4,ptemp4,q[4]);
//row r6 (ptemp6,temp6,sum[5],temp5,ptemp5,q[5]);
//row r7 (ptemp7,temp7,sum[6],temp6,ptemp6,q[6]);
//row r8 (ptemp8,temp8,sum[7],temp7,ptemp7,q[7]);
//row r9 (ptemp9,temp9,sum[8],temp8,ptemp8,q[8]);
//row r10 (ptemp10,temp10,sum[9],temp9,ptemp9,q[9]);
//row r11 (ptemp11,temp11,sum[10],temp10,ptemp10,q[10]);
//row r12 (ptemp12,temp12,sum[11],temp11,ptemp11,q[11]);
//row r13 (ptemp13,temp13,sum[12],temp12,ptemp12,q[12]);
//row r14 (ptemp14,temp14,sum[13],temp13,ptemp13,q[13]);
//row r15 (ptemp15,temp15,sum[14],temp14,ptemp14,q[14]);
//row r16 (ptemp16,temp16,sum[15],temp15,ptemp15,q[15]);
//row r17 (ptemp17,temp17,sum[16],temp16,ptemp16,q[16]);
//row r18 (ptemp18,temp18,sum[17],temp17,ptemp17,q[17]);
//row r19 (ptemp19,temp19,sum[18],temp18,ptemp18,q[18]);
//row r20 (ptemp20,temp20,sum[19],temp19,ptemp19,q[19]);
//row r21 (ptemp21,temp21,sum[20],temp20,ptemp20,q[20]);
//row r22 (ptemp22,temp22,sum[21],temp21,ptemp21,q[21]);
//row r23 (ptemp23,temp23,sum[22],temp22,ptemp22,q[22]);
//row r24 (sum[47:24],temp24,sum[23],temp23,ptemp23,q[23]);
endmodule
