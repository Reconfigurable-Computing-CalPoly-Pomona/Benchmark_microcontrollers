`timescale 1ns / 1ps

module holl_FPadd(
    input  logic clk,
    input  logic reset,
    // slot interface
    input  logic cs,
    input  logic read,
    input  logic write,
    input  logic [4:0] addr,
    input  logic [31:0] wr_data,
    output logic [31:0] rd_data
    );
reg wr_A0, wr_A1, wr_A2; 
reg [31:0] rd_data_reg;
logic [31:0] Addend0, Addend1, SumOut;

    
FPadder_32bit FloatingPoint_Adder32 (.clk(clk), .Addend1(Addend0), .Addend2(Addend1), .Sum(SumOut));
   
   
// body
   always_ff @(posedge clk, posedge reset)
    begin
      rd_data_reg = SumOut;
      if (reset)
        begin
         Addend0 <= 0;
         Addend1 <= 0;
        end
      else
         begin
             if (wr_A0)
                Addend0 = wr_data;
             if (wr_A1)
                Addend1 = wr_data;
         end
    end 
       
//decoding

   assign wr_A0 = write & cs & addr[0];
   assign wr_A1 = write & cs & addr[1];

   assign rd_data[31:0] = rd_data_reg;   
    
endmodule