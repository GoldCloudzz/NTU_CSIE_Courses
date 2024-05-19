module BranchUnit(data1_i, data2_i, Branch_i, PC_i, immediate_i, Flush_o, target_PC_o);

input [31:0] data1_i, data2_i;
input Branch_i;
input [31:0] PC_i;
input [31:0] immediate_i;

output reg Flush_o;
output [31:0] target_PC_o;

Adder Adder(PC_i, (immediate_i << 1), target_PC_o);

always @(*) begin
    // branch taken
    if ((data1_i == data2_i) && (Branch_i == 1'b1)) begin
        Flush_o = 1'b1;
    end
    else begin
        Flush_o = 1'b0;
    end
end

endmodule