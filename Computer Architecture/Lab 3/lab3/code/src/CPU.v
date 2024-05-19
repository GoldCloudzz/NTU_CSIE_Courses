`include "/root/project/code/src/Definition.v"

module CPU(clk_i, rst_i);

// Port
input clk_i, rst_i;

// PC
wire [31:0] PC_i, PC_o;
wire [31:0] adder_PC;
wire [31:0] PC_temp;

// Instruction
wire [31:0] instruction;
wire [4:0] rs1_addr, rs2_addr, rd_addr;
wire [2:0] funct3;
wire [6:0] funct7;
wire [6:0] opcode;

// Operands
wire [31:0] rs1_data, rs2_data, rd_data;
wire [31:0] immediate;

// Control signals
wire RegWrite, MemtoReg, MemRead, MemWrite, ALUSrc, Branch;
wire [1:0] ALUOp;

// Branch predictor
wire predict;
wire [31:0] target_PC;

// Data hazard detection unit
wire PCWrite, Stall, Noop;

// Control hazard detection unit
wire mispredict;
wire [31:0] PC_rollback;

// Forwarding unit
wire [1:0] ForwardA, ForwardB;
wire [31:0] ForwardA_data, ForwardB_data;

// ALU
wire [3:0] ALUCtr;
wire [31:0] ALU_data1_in, ALU_data2_in;
wire [31:0] ALU_data_out;
wire Zero;

// Memory
wire [31:0] memory_data;

// IF/ID latch
wire [31:0] IFID_PC;
wire [31:0] IFID_instruction;

// ID/EX latch
wire [31:0] IDEX_PC;
wire [31:0] IDEX_rs1_data, IDEX_rs2_data;
wire [4:0] IDEX_rs1_addr, IDEX_rs2_addr, IDEX_rd_addr;
wire [31:0] IDEX_immediate;
wire [2:0] IDEX_funct3;
wire [6:0] IDEX_funct7;
wire IDEX_RegWrite, IDEX_MemtoReg, IDEX_MemRead, IDEX_MemWrite, IDEX_ALUSrc, IDEX_Branch;
wire [1:0] IDEX_ALUOp;
wire IDEX_predict;

// EX/MEM latch
wire [31:0] EXMEM_rs2_data;
wire [4:0] EXMEM_rd_addr;
wire [31:0] EXMEM_ALU_data;
wire EXMEM_RegWrite, EXMEM_MemtoReg, EXMEM_MemRead, EXMEM_MemWrite;

// MEM/WB latch
wire [31:0] MEMWB_ALU_data, MEMWB_memory_data;
wire [4:0] MEMWB_rd_addr;
wire MEMWB_RegWrite, MEMWB_MemtoReg;

// IF stage

Adder Adder_PC_nontaken(PC_o, 32'd4, adder_PC);

Adder Adder_PC_taken(IFID_PC, immediate << 1, target_PC);

MUX_1 MUX_PC_branch(adder_PC, target_PC, (Branch && predict), PC_temp);

MUX_1 MUX_PC_mispredict(PC_temp, PC_rollback, mispredict, PC_i);

PC PC(rst_i, clk_i, PCWrite, PC_i, PC_o);

Instruction_Memory Instruction_Memory(PC_o, instruction);

IFID_Register IF_ID(clk_i, Stall, (mispredict || (Branch && predict)), PC_o, instruction, IFID_PC, IFID_instruction);

// ID stage

assign funct7 = IFID_instruction[31:25];
assign rs2_addr = IFID_instruction[24:20];
assign rs1_addr = IFID_instruction[19:15];
assign funct3 = IFID_instruction[14:12];
assign rd_addr = IFID_instruction[11:7];
assign opcode = IFID_instruction[6:0];

Registers Registers(rst_i, clk_i, rs1_addr, rs2_addr, MEMWB_rd_addr, rd_data, MEMWB_RegWrite, rs1_data, rs2_data);

Imm_Gen Imm_Gen(IFID_instruction, immediate);

Control Control(opcode, Noop, RegWrite, MemtoReg, MemRead, MemWrite, ALUOp, ALUSrc, Branch);

Data_Hazard_Detection Data_Hazard_Detection(rs1_addr, rs2_addr, IDEX_rd_addr, IDEX_MemRead, PCWrite, Stall, Noop);

Branch_Predictor branch_predictor(clk_i, IDEX_Branch, Zero, predict);

IDEX_Register ID_EX(clk_i, mispredict, IFID_PC, rs1_data, rs2_data, rs1_addr, rs2_addr, rd_addr, immediate, funct3, funct7, RegWrite, MemtoReg, MemRead, MemWrite, ALUOp, ALUSrc, Branch, predict, IDEX_PC, IDEX_rs1_data, IDEX_rs2_data, IDEX_rs1_addr, IDEX_rs2_addr, IDEX_rd_addr, IDEX_immediate, IDEX_funct3, IDEX_funct7, IDEX_RegWrite, IDEX_MemtoReg, IDEX_MemRead, IDEX_MemWrite, IDEX_ALUOp, IDEX_ALUSrc, IDEX_Branch, IDEX_predict);

// EX stage

ForwardingUnit ForwardingUnit(IDEX_rs1_addr, IDEX_rs2_addr, EXMEM_rd_addr, MEMWB_rd_addr, EXMEM_RegWrite, MEMWB_RegWrite, ForwardA, ForwardB);

MUX_2 MUX_A(IDEX_rs1_data, rd_data, EXMEM_ALU_data, 32'b0, ForwardA, ForwardA_data);
MUX_2 MUX_B(IDEX_rs2_data, rd_data, EXMEM_ALU_data, 32'b0, ForwardB, ForwardB_data);

assign ALU_data1_in = ForwardA_data;
MUX_1 MUX_ALU(ForwardB_data, IDEX_immediate, IDEX_ALUSrc, ALU_data2_in);

ALUControl ALUControl(IDEX_ALUOp, IDEX_funct3, IDEX_funct7, ALUCtr);

ALU ALU(ALU_data1_in, ALU_data2_in, ALUCtr, ALU_data_out, Zero);

Control_Hazard_Detection Control_Hazard_Detection(IDEX_Branch, IDEX_predict, Zero, IDEX_PC, IDEX_immediate, mispredict, PC_rollback);

EXMEM_Register EXMEM_Register(clk_i, ForwardB_data, IDEX_rd_addr, ALU_data_out, IDEX_RegWrite, IDEX_MemtoReg, IDEX_MemRead, IDEX_MemWrite, EXMEM_rs2_data, EXMEM_rd_addr, EXMEM_ALU_data, EXMEM_RegWrite, EXMEM_MemtoReg, EXMEM_MemRead, EXMEM_MemWrite);

// MEM stage

Data_Memory Data_Memory(clk_i, EXMEM_ALU_data, EXMEM_MemRead, EXMEM_MemWrite, EXMEM_rs2_data, memory_data);

MEMWB_Register MEMWB_Register(clk_i, EXMEM_ALU_data, memory_data, EXMEM_rd_addr, EXMEM_RegWrite, EXMEM_MemtoReg, MEMWB_ALU_data, MEMWB_memory_data, MEMWB_rd_addr, MEMWB_RegWrite, MEMWB_MemtoReg);

// WB stage

MUX_1 MUX_WB(MEMWB_ALU_data, MEMWB_memory_data, MEMWB_MemtoReg, rd_data);

endmodule