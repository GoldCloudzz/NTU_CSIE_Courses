`include "/root/project/code/src/Definition.v"

module CPU(clk_i, rst_i);

// Ports
input               clk_i;
input               rst_i;

// PC
wire [31:0] PC_cur, PC_next;

Adder Adder(PC_cur, 32'd4, PC_next);

PC PC(clk_i, rst_i, PC_next, PC_cur);

// Instruction
wire [31:0] instruction;

Instruction_Memory Instruction_Memory(PC_cur, instruction);

// Two source registers
wire [31:0] rs1, rs2;

Registers Registers(rst_i, clk_i, instruction[19:15], instruction[24:20], instruction[11:7], ALUOut, RegWrite, rs1, rs2);

// Control signals
wire RegWrite, ALUSrc;
wire [1:0] ALUOp;

Control Control(instruction[6:0], RegWrite, ALUSrc, ALUOp);

wire [3:0] ALUCtr;

ALUControl ALUControl(ALUOp, instruction[14:12], instruction[31:25], ALUCtr);

// Immediate
wire [31:0] immediate;

Imm_Gen Imm_Gen(instruction[31:20], immediate);

// Operands of ALU
wire [31:0] op1, op2;

assign op1 = rs1;

MUX MUX_ALUSrc(rs2, immediate, ALUSrc, op2);

// Output of ALU
wire [31:0] ALUOut;
  
ALU ALU(op1, op2, ALUCtr, ALUOut);

endmodule

