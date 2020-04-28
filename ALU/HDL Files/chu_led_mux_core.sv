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

//logic wr_go;
logic [4:0] address, A;
logic [31:0] rd_reg, data_input, datI, data_output; 


//signal declaration
sync_one_port_ram #(.DATA_WIDTH(32), .ADDR_WIDTH(5) )  Memory  // number of address bits
(.clk(clk), .we_a((write|~read)), .addr_a(addr), .din_a(datI), .dout_a(data_output)); 

always_ff @(posedge clk)
    begin
        rd_reg <= data_output;
        data_input <= wr_data;
        //address <= addr;
     end
        
//assign A = address;
assign datI = data_input;
assign rd_data = rd_reg;

endmodule  

