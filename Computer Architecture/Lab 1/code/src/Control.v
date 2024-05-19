`include "/root/project/code/src/Definition.v"

module Control(opcode, RegWrite, ALUSrc, ALUOp);

input [6:0] opcode;

output RegWrite;
output reg ALUSrc;
output reg [1:0] ALUOp;

assign RegWrite = 1'b1;

always @(*) begin
    // I type
    if (opcode == `opcode_I) begin
        ALUSrc = 1'b1;
    end
    // R type
    else if (opcode == `opcode_R) begin
        ALUSrc = 1'b0;
    end
end

always @(*) begin
    // I type
    if (opcode == `opcode_I) begin
        ALUOp = 2'b00;
    end
    else if (opcode == `opcode_R) begin
        ALUOp = 2'b11;
    end
end

endmodule