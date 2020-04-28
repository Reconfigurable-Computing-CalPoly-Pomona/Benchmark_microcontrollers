module holl_data
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

logic wr_go, WR, DATA_Signal;
reg [31:0] rd_reg;
wire[31:0] data_input, data_output;//, 


//signal declaration
sync_one_port_ram #(.DATA_WIDTH(32), .ADDR_WIDTH(5) )  Memory  // number of address bits
(.clk(clk), .we_a(write), .addr_a(addr), .din_a(wr_data), .dout_a(data_output));//, .we_b(1'b0), .addr_b(5'b0), .din_b(32'b0), .dout_b()); 

always_ff @(posedge clk)
     rd_reg <= data_output;


assign rd_data = rd_reg;

endmodule  

