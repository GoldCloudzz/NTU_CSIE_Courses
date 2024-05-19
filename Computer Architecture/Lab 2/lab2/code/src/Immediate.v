`include "/root/project/code/src/Definition.v"

module Imm_Gen(instruction_i, data_o);

input [31:0] instruction_i;

output [31:0] data_o;

wire [6:0] opcode;
reg [11:0] immediate;

assign opcode = instruction_i[6:0];

always @(*) begin
    // store instruction
    if (opcode == `opcode_store) begin
        immediate = {instruction_i[31:25], instruction_i[11:7]};
    end
    // branch instruction
    else if (opcode == `opcode_branch) begin
        immediate = {instruction_i[31], instruction_i[7], instruction_i[30:25], instruction_i[11:8]};
    end
    // I type and load instruction
    else if (opcode == `opcode_I || opcode == `opcode_load) begin
        immediate = instruction_i[31:20];
    end
    // R type instruction
    else if (opcode == `opcode_R) begin
        immediate = 12'b0;
    end
end

assign data_o = {{20{immediate[11]}}, immediate};

endmodule