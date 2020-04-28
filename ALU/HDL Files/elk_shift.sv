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
    logic Wr_Val, Wr_Shift, ShiftDir;
    logic [4:0] Shift;
    reg [31:0] rd_data_reg;
    logic [31:0] ValueIn, ValueOut;
  
  barrel32 shifter (.Data_IN(ValueIn), .Sel(Shift), .Data_OUT(ValueOut));
  
   // body
   always_ff @(posedge clk, posedge reset)
    begin
      rd_data_reg = ValueOut;
      if (reset)
        begin
         rd_data_reg <= 0;
        end
      else
         begin
            if(Wr_Val)
                ValueIn = wr_data;
            if(Wr_Shift)
                begin
                    ShiftDir = wr_data[5]; //if 0 -> R; if 1 -> L
                        if(ShiftDir == 0)
                            Shift =  wr_data[4:0];
                        if(ShiftDir == 1)
                            Shift =  (~wr_data[4:0])| 5'b00001;
                end           
         end
    end 
       
//decoding
    assign Wr_Val = cs && write && addr[0]; 
    assign Wr_Shift = cs && write && addr[1];
    assign rd_data[31:0] = rd_data_reg;    
    
endmodule  


