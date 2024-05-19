module Hazard_Detection(IFID_rs1_i, IFID_rs2_i, IDEX_rd_i, IDEX_MemRead_i, PC_Write_o, Stall_o, Noop_o);

input [4:0] IFID_rs1_i, IFID_rs2_i, IDEX_rd_i;
input IDEX_MemRead_i;

output reg PC_Write_o, Stall_o, Noop_o;

always @(*) begin
    if ((IDEX_MemRead_i == 1'b1) && ((IDEX_rd_i == IFID_rs1_i) || (IDEX_rd_i == IFID_rs2_i))) begin
        PC_Write_o = 1'b0;
        Stall_o = 1'b1;
        Noop_o = 1'b1;
    end
    else begin
        PC_Write_o = 1'b1;
        Stall_o = 1'b0;
        Noop_o = 1'b0;
    end
end

endmodule