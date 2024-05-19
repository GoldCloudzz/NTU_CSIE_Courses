`include "/root/project/code/src/Definition.v"

module ALUControl(ALUOp, funct3, funct7, ALUCtr);

input [1:0] ALUOp;
input [2:0] funct3;
input [6:0] funct7;

output reg [3:0] ALUCtr;

always @(*) begin
    // arithmetic operations
    if (funct3 == 3'b000) begin
        // addi
        if (ALUOp == 2'b00) begin
            ALUCtr = `ALU_ADD;
        end
        // add
        else if (funct7 == 7'b0000000) begin
            ALUCtr = `ALU_ADD;
        end
        // sub
        else if (funct7 == 7'b0100000) begin
            ALUCtr = `ALU_SUB;
        end
        // mul
        else if (funct7 == 7'b0000001) begin
            ALUCtr = `ALU_MUL;
        end
    end
    // sll
    else if (funct3 == 3'b001) begin
        ALUCtr = `ALU_SLL;
    end
    // xor
    else if (funct3 == 3'b100) begin
        ALUCtr = `ALU_XOR;
    end
    // srai
    else if (funct3 == 3'b101) begin
        ALUCtr = `ALU_SRA;
    end
    // and
    else if (funct3 == 3'b111) begin
        ALUCtr = `ALU_AND;
    end
end

endmodule