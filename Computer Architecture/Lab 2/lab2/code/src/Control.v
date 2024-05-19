`include "/root/project/code/src/Definition.v"

module Control(opcode_i, Noop_i, RegWrite_o, MemtoReg_o, MemRead_o, MemWrite_o, ALUOp_o, ALUSrc_o, Branch_o);

input [6:0] opcode_i;
input Noop_i;

output reg RegWrite_o, MemtoReg_o, MemRead_o, MemWrite_o, ALUSrc_o, Branch_o;
output reg [1:0] ALUOp_o;

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        RegWrite_o = 1'b0;
    end
    else begin
        // R type, I type, and load instruction
        if (opcode_i == `opcode_R || opcode_i == `opcode_I || opcode_i == `opcode_load) begin
            RegWrite_o = 1'b1;
        end
        // store and branch instruction
        else if (opcode_i == `opcode_store || opcode_i == `opcode_branch) begin
            RegWrite_o = 1'b0;
        end
    end
end

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        MemtoReg_o = 1'b0;
    end
    else begin
        // load instruction
        if (opcode_i == `opcode_load) begin
            MemtoReg_o = 1'b1;
        end
        // R type, I type, store, and branch instruction
        else if (opcode_i == `opcode_R || opcode_i == `opcode_I || opcode_i == `opcode_store || opcode_i == `opcode_branch) begin
            MemtoReg_o = 1'b0;
        end
    end
end

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        MemRead_o = 1'b0;
    end
    else begin
        // load instruction
        if (opcode_i == `opcode_load) begin
            MemRead_o = 1'b1;
        end
        // R type, I type, store, and branch instruction
        else if (opcode_i == `opcode_R || opcode_i == `opcode_I || opcode_i == `opcode_store || opcode_i == `opcode_branch) begin
            MemRead_o = 1'b0;
        end
    end
end

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        MemWrite_o = 1'b0;
    end
    else begin
        // store instruction
        if (opcode_i == `opcode_store) begin
            MemWrite_o = 1'b1;
        end
        // R type, I type, load, and branch instruction
        else if (opcode_i == `opcode_R || opcode_i == `opcode_I || opcode_i == `opcode_load || opcode_i == `opcode_branch) begin
            MemWrite_o = 1'b0;
        end
    end
end

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        ALUOp_o = 2'b00;
    end
    else begin
        // load and store instruction
        if (opcode_i == `opcode_load || opcode_i == `opcode_store) begin
            ALUOp_o = 2'b00;
        end
        // branch instruction
        else if (opcode_i == `opcode_branch) begin
            ALUOp_o = 2'b01;
        end
        // R type instruction
        else if (opcode_i == `opcode_R) begin
            ALUOp_o = 2'b10;
        end
        // I type instruction
        else if (opcode_i == `opcode_I) begin
            ALUOp_o = 2'b11;
        end
    end
end

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        ALUSrc_o = 1'b0;
    end
    // I type, load, and store instruction
    if (opcode_i == `opcode_I || opcode_i == `opcode_load || opcode_i == `opcode_store) begin
        ALUSrc_o = 1'b1;
    end
    // R type and branch instruction
    else if (opcode_i == `opcode_R || opcode_i == `opcode_branch) begin
        ALUSrc_o = 1'b0;
    end
end

always @(*) begin
    // noop
    if (Noop_i == 1'b1 || opcode_i == `opcode_noop) begin
        Branch_o = 1'b0;
    end
    else begin
        // branch instruction
        if (opcode_i == `opcode_branch) begin
            Branch_o = 1'b1;
        end
        // R type, I type, load, and store instruction
        else if (opcode_i == `opcode_R || opcode_i == `opcode_I || opcode_i == `opcode_load || opcode_i == `opcode_store) begin
            Branch_o = 1'b0;
        end
    end
end

endmodule