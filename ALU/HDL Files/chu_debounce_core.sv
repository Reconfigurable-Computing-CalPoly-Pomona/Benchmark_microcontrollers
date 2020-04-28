module elk_shift
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
    // signal declaration
    //logic Wr_Val, Wr_Shift, ShiftDir;
    logic [4:0] Shift;
    reg [31:0] rd_data_reg;
    logic [31:0] ValueIn, ValueOut, V;
  
  barrel32 shifter (.Data_IN(ValueIn), .Sel(Shift), .Data_OUT(ValueOut));
  
   // body
   always_ff @(posedge clk)
    begin
        rd_data_reg <= ValueOut;
        Shift <= addr;
        if(write)
            begin
            V <= wr_data;
            end
     end 
       
//decoding
//    assign Wr_Val = cs && write && addr[0]; 
//    assign Wr_Shift = cs && write && addr[1];
    assign rd_data[31:0] = rd_data_reg;    
    assign ValueIn = V;
    
endmodule  


