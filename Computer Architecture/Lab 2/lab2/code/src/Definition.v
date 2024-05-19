`define opcode_I 7'b0010011
`define opcode_R 7'b0110011
`define opcode_load 7'b0000011
`define opcode_store 7'b0100011
`define opcode_branch 7'b1100011
`define opcode_noop 7'b0000000

`define ALU_NOP 4'b0000
`define ALU_AND 4'b0001
`define ALU_XOR 4'b0010
`define ALU_ADD 4'b0011
`define ALU_SUB 4'b0100
`define ALU_MUL 4'b0101
`define ALU_SLL 4'b0110
`define ALU_SRA 4'b0111