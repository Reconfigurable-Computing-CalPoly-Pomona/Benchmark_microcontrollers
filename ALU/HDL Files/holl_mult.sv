`timescale 1ns / 1ps

module holl_mult
   (
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
reg wr_A0, wr_A1, read_Up, read_Low; 
logic [31:0] Multiplicand0, Multiplicand1;
logic [63:0] rd_data_reg, Prod;//, ProdSave;
  
  
//multiplier_32bit_CLA Mult_32(.multicand(Multiplicand0), .multiplier(Multiplicand1), .product(Prod));

assign Prod = Multiplicand0 * Multiplicand1; //temporary stand-in

  
// body
   always_ff @(posedge clk)
    begin
         rd_data_reg = Prod;
       if (wr_A0)
            Multiplicand0 = wr_data;
       if (wr_A1)
            Multiplicand1 = wr_data;
    end 
       
//decoding

   assign wr_A0 = write & cs & addr[0];
   assign wr_A1 = write & cs & addr[1];
   assign read_Up = read & cs & addr[2];

   assign rd_data[31:0] = (read_Up) ? rd_data_reg[63:32] : rd_data_reg[31:0];    
    
endmodule

