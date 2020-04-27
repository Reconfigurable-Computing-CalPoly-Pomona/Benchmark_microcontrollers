module sync_one_port_ram
 #(parameter DATA_WIDTH = 8, // number of bits
 ADDR_WIDTH = 10) // number of address bits
 (
     input logic clk,
     input logic we_a,
     input logic [ADDR_WIDTH - 1: 0] addr_a,
     input logic [DATA_WIDTH - 1:0] din_a,
     output logic [DATA_WIDTH - 1:0] dout_a
 );

 // signal declarations
 logic [DATA_WIDTH - 1: 0] ram [0:2**ADDR_WIDTH - 1];

 always_ff @(posedge clk)
     begin
     // write operation
         if(we_a)
            ram[addr_a] <= din_a;
         // read operation
         dout_a <= ram[addr_a];
    end
   
endmodule