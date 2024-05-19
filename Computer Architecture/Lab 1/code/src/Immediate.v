module Imm_Gen(num, result);

input [11:0] num;

output [31:0] result;

assign result = {{20{num[11]}}, num};

endmodule