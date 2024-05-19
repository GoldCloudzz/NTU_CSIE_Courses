`include "/root/project/code/src/Definition.v"

module ALU(a, b, ALUCtr, result);

input [31:0] a, b;
input [3:0] ALUCtr;

output reg [31:0] result;

wire [4:0] shamt;
assign shamt = b[4:0];

always @(*) begin
    case (ALUCtr) 
        `ALU_AND: result = a & b;
        `ALU_XOR: result = a ^ b;
        `ALU_ADD: result = a + b;
        `ALU_SUB: result = a - b;
        `ALU_MUL: result = a * b;
        `ALU_SLL: result = a << b;
        `ALU_SRA: result = a >>> shamt;
    endcase
end

endmodule