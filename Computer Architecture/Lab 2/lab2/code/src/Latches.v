module IFID_Register(clk_i, Stall_i, Flush_i, PC_i, instruction_i, PC_o, instruction_o);

input clk_i;
input Stall_i, Flush_i;
input [31:0] PC_i;
input [31:0] instruction_i;

output reg [31:0] PC_o;
output reg [31:0] instruction_o;

initial PC_o = 32'b0;
initial instruction_o = 32'b0;

always @(posedge clk_i) begin
    if (Flush_i == 1'b1) begin
        PC_o <= 32'b0;
        instruction_o <= 32'b0;
    end
    else begin
        if (Stall_i == 1'b1) begin
            PC_o <= PC_o;
            instruction_o <= instruction_o;
        end
        else begin
            PC_o <= PC_i;
            instruction_o <= instruction_i;
        end
    end
end

endmodule

module IDEX_Register(clk_i, rs1_data_i, rs2_data_i, rs1_addr_i, rs2_addr_i, rd_addr_i, immediate_i, funct3_i, funct7_i, RegWrite_i, MemtoReg_i, MemRead_i, MemWrite_i, ALUOp_i, ALUSrc_i, rs1_data_o, rs2_data_o, rs1_addr_o, rs2_addr_o, rd_addr_o, immediate_o, funct3_o, funct7_o, RegWrite_o, MemtoReg_o, MemRead_o, MemWrite_o, ALUOp_o, ALUSrc_o);

input clk_i;
input [31:0] rs1_data_i, rs2_data_i;
input [4:0] rs1_addr_i, rs2_addr_i, rd_addr_i;
input [31:0] immediate_i;
input [2:0] funct3_i;
input [6:0] funct7_i;
input RegWrite_i, MemtoReg_i, MemRead_i, MemWrite_i, ALUSrc_i;
input [1:0] ALUOp_i;

output reg [31:0] rs1_data_o, rs2_data_o;
output reg [4:0] rs1_addr_o, rs2_addr_o, rd_addr_o;
output reg [31:0] immediate_o;
output reg [2:0] funct3_o;
output reg [6:0] funct7_o;
output reg RegWrite_o, MemtoReg_o, MemRead_o, MemWrite_o, ALUSrc_o;
output reg [1:0] ALUOp_o;

initial rs1_data_o = 32'b0;
initial rs2_data_o = 32'b0;
initial rs1_addr_o = 5'b0;
initial rs2_addr_o = 5'b0;
initial rd_addr_o = 5'b0;
initial immediate_o = 32'b0;
initial funct3_o = 3'b0;
initial funct7_o = 7'b0;
initial RegWrite_o = 1'b0;
initial MemtoReg_o = 1'b0;
initial MemRead_o = 1'b0;
initial MemWrite_o = 1'b0;
initial ALUOp_o = 2'b0;
initial ALUSrc_o = 1'b0;

always @(posedge clk_i) begin
    rs1_data_o <= rs1_data_i;
    rs2_data_o <= rs2_data_i;
    rs1_addr_o <= rs1_addr_i;
    rs2_addr_o <= rs2_addr_i;
    rd_addr_o <= rd_addr_i;
    immediate_o <= immediate_i;
    funct3_o <= funct3_i;
    funct7_o <= funct7_i;
    RegWrite_o <= RegWrite_i;
    MemtoReg_o <= MemtoReg_i;
    MemRead_o <= MemRead_i;
    MemWrite_o <= MemWrite_i;
    ALUOp_o <= ALUOp_i;
    ALUSrc_o <= ALUSrc_i;
end

endmodule

module EXMEM_Register(clk_i, rs2_data_i, rd_addr_i, ALU_data_i, RegWrite_i, MemtoReg_i, MemRead_i, MemWrite_i, rs2_data_o, rd_addr_o, ALU_data_o, RegWrite_o, MemtoReg_o, MemRead_o, MemWrite_o);

input clk_i;
input [31:0] rs2_data_i;
input [4:0] rd_addr_i;
input [31:0] ALU_data_i;
input RegWrite_i, MemtoReg_i, MemRead_i, MemWrite_i;

output reg [31:0] rs2_data_o;
output reg [4:0] rd_addr_o;
output reg [31:0] ALU_data_o;
output reg RegWrite_o, MemtoReg_o, MemRead_o, MemWrite_o;

initial rs2_data_o = 32'b0;
initial rd_addr_o = 5'b0;
initial ALU_data_o = 32'b0;
initial RegWrite_o = 1'b0;
initial MemtoReg_o = 1'b0;
initial MemRead_o = 1'b0;
initial MemWrite_o = 1'b0;

always @(posedge clk_i) begin
    rs2_data_o <= rs2_data_i;
    rd_addr_o <= rd_addr_i;
    ALU_data_o <= ALU_data_i;
    RegWrite_o <= RegWrite_i;
    MemtoReg_o <= MemtoReg_i;
    MemRead_o <= MemRead_i;
    MemWrite_o <= MemWrite_i;
end

endmodule

module MEMWB_Register(clk_i, ALU_result_i, memory_data_i, rd_addr_i, RegWrite_i, MemtoReg_i, ALU_result_o, memory_data_o, rd_addr_o, RegWrite_o, MemtoReg_o);

input clk_i;
input [31:0] ALU_result_i, memory_data_i;
input [4:0] rd_addr_i;
input RegWrite_i, MemtoReg_i;

output reg [31:0] ALU_result_o, memory_data_o;
output reg [4:0] rd_addr_o;
output reg RegWrite_o, MemtoReg_o;

initial ALU_result_o = 32'b0;
initial memory_data_o = 32'b0;
initial rd_addr_o = 5'b0;
initial RegWrite_o = 1'b0;
initial MemtoReg_o = 1'b0;

always @(posedge clk_i) begin
    ALU_result_o <= ALU_result_i;
    memory_data_o <= memory_data_i;
    rd_addr_o <= rd_addr_i;
    RegWrite_o <= RegWrite_i;
    MemtoReg_o <= MemtoReg_i;
end

endmodule