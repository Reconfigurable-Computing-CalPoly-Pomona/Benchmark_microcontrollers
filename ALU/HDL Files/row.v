`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/23/2020 02:50:08 PM
// Design Name: 
// Module Name: row
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


module row(
output wire[23:0] ppo,
output wire[23:0] mout,
output wire sum,
input wire[23:0] min,
input wire[23:0] ppi,
input wire q
    );
wire c1,c2,c3,c4,c5,c6,c7,c8,c9,c10;
wire c11,c12,c13,c14,c15,c16,c17,c18,c19,c20;
wire c21,c22,c23;
block b1 (sum,c1,mout[0],min[0],ppi[0],q,1'b0);
block b2 (ppo[0],c2,mout[1],min[1],ppi[1],q,c1);
block b3 (ppo[1],c3,mout[2],min[2],ppi[2],q,c2);
block b4 (ppo[2],c4,mout[3],min[3],ppi[3],q,c3);
block b5 (ppo[3],c5,mout[4],min[4],ppi[4],q,c4);
block b6 (ppo[4],c6,mout[5],min[5],ppi[5],q,c5);
block b7 (ppo[5],c7,mout[6],min[6],ppi[6],q,c6);
block b8 (ppo[6],c8,mout[7],min[7],ppi[7],q,c7);
block b9 (ppo[7],c9,mout[8],min[8],ppi[8],q,c8);
block b10 (ppo[8],c10,mout[9],min[9],ppi[9],q,c9);
block b11 (ppo[9],c11,mout[10],min[10],ppi[10],q,c10);
block b12 (ppo[10],c12,mout[11],min[11],ppi[11],q,c11);
block b13 (ppo[11],c13,mout[12],min[12],ppi[12],q,c12);
block b14 (ppo[12],c14,mout[13],min[13],ppi[13],q,c13);
block b15 (ppo[13],c15,mout[14],min[14],ppi[14],q,c14);
block b16 (ppo[14],c16,mout[15],min[15],ppi[15],q,c15);
block b17 (ppo[15],c17,mout[16],min[16],ppi[16],q,c16);
block b18 (ppo[16],c18,mout[17],min[17],ppi[17],q,c17);
block b19 (ppo[17],c19,mout[18],min[18],ppi[18],q,c18);
block b20 (ppo[18],c20,mout[19],min[19],ppi[19],q,c19);
block b21 (ppo[19],c21,mout[20],min[20],ppi[20],q,c20);
block b22 (ppo[20],c22,mout[21],min[21],ppi[21],q,c21);
block b23 (ppo[21],c23,mout[22],min[22],ppi[22],q,c22);
block b24 (ppo[22],ppo[23],mout[23],min[23],ppi[23],q,c23);
endmodule
