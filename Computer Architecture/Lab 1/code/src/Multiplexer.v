module MUX(a, b, signal, out);

input [31:0] a, b;
input signal;

output [31:0] out;

assign out = (signal == 1'b0) ? a : b;

endmodule