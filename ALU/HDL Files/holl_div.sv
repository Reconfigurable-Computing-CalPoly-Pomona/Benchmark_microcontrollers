
module holl_div(
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
//reg wr_A0, wr_A1, read_Low; 
//logic [31:0] Dividend0, Dividend1;
//logic [31:0] rd_data_reg, Quot;//, ProdSave;
  

//assign Quot = Dividend0 / Dividend1; //temporary stand-in

  
//// body
//   always_ff @(posedge clk)
//    begin
//         rd_data_reg = Quot;
//       if (wr_A0)
//            Dividend0 = wr_data;
//       if (wr_A1)
//            Dividend1 = wr_data;
//    end 
       
////decoding

//   assign wr_A0 = write & cs & addr[0];
//   assign wr_A1 = write & cs & addr[1];

   assign rd_data[31:0] = 0;    
    
endmodule