`include "/root/project/code/src/Definition.v"

module ALUControl(ALUOp_i, funct3_i, funct7_i, ALUCtr_o);

input [1:0] ALUOp_i;
input [2:0] funct3_i;
input [6:0] funct7_i;

output reg [3:0] ALUCtr_o;

always @(*) begin
    // load and store instruction
    if (ALUOp_i == 2'b00) begin
        ALUCtr_o = `ALU_ADD;
    end
    // branch instruction
    else if (ALUOp_i == 2'b01) begin
        ALUCtr_o = `ALU_NOP;
    end
    // R type instruction
    else if (ALUOp_i == 2'b10) begin
        // arithmetic instructions
        if (funct3_i == 3'b000) begin
            // add
            if (funct7_i == 7'b0000000) begin
                ALUCtr_o = `ALU_ADD;
            end
            // sub
            if (funct7_i == 7'b0100000) begin
                ALUCtr_o = `ALU_SUB;
            end
            // mul
            if (funct7_i == 7'b0000001) begin
                ALUCtr_o = `ALU_MUL;
            end
        end
        // sll
        else if (funct3_i == 3'b001) begin
            ALUCtr_o = `ALU_SLL;
        end
        // xor
        else if (funct3_i == 3'b100) begin
            ALUCtr_o = `ALU_XOR;
        end
        // and
        else if (funct3_i == 3'b111) begin
            ALUCtr_o = `ALU_AND;
        end
    end
    // I type instruction
    else if (ALUOp_i == 2'b11) begin
        // addi
        if (funct3_i == 3'b000) begin
            ALUCtr_o = `ALU_ADD;
        end
        // srai
        else if (funct3_i == 3'b101) begin
            ALUCtr_o = `ALU_SRA;
        end
    end
end

endmodule