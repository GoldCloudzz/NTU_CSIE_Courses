module MUX_1(data1_i, data2_i, select_i, data_o);

input [31:0] data1_i, data2_i;
input select_i;

output reg [31:0] data_o;

always @(*) begin
    case (select_i)
        1'b0: data_o = data1_i;
        1'b1: data_o = data2_i;
    endcase
end

endmodule

module MUX_2(data1_i, data2_i, data3_i, data4_i, select_i, data_o);

input [31:0] data1_i, data2_i, data3_i, data4_i;
input [1:0] select_i;

output reg [31:0] data_o;

always @(*) begin
    case (select_i)
        2'b00: data_o = data1_i;
        2'b01: data_o = data2_i;
        2'b10: data_o = data3_i;
        2'b11: data_o = data4_i;
    endcase
end

endmodule