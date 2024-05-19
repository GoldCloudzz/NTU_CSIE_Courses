`include "/root/project/code/src/Definition.v"

module ALU(data1_i, data2_i, ALUCtr_i, data_o);

input [31:0] data1_i, data2_i;
input [3:0] ALUCtr_i;

output reg [31:0] data_o;

wire [4:0] shamt;
assign shamt = data2_i[4:0];

always @(*) begin
    case (ALUCtr_i) 
        `ALU_NOP: data_o = 32'b0;
        `ALU_AND: data_o = data1_i & data2_i;
        `ALU_XOR: data_o = data1_i ^ data2_i;
        `ALU_ADD: data_o = data1_i + data2_i;
        `ALU_SUB: data_o = data1_i - data2_i;
        `ALU_MUL: data_o = data1_i * data2_i;
        `ALU_SLL: data_o = data1_i << data2_i;
        `ALU_SRA: data_o = data1_i >>> shamt;
    endcase
end

endmodule