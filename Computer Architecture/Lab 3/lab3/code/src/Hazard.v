module Data_Hazard_Detection(IFID_rs1_i, IFID_rs2_i, IDEX_rd_i, IDEX_MemRead_i, PC_Write_o, Stall_o, Noop_o);

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

module Control_Hazard_Detection(IDEX_Branch_i, IDEX_prediction_i, Zero_i, IDEX_PC_i, IDEX_immediate_i, mispredict_o, PC_rollback_o);

input IDEX_Branch_i, IDEX_prediction_i, Zero_i;
input [31:0] IDEX_PC_i;
input [31:0] IDEX_immediate_i;

output reg mispredict_o;
output reg [31:0] PC_rollback_o;

always @(*) begin
    // Misprediction occurs
    if ((IDEX_Branch_i == 1'b1) && (IDEX_prediction_i != Zero_i)) begin
        mispredict_o = 1'b1;
    end
    // Misprediction doesn't occur
    else begin
        mispredict_o = 1'b0;
    end
end

always @(*) begin
    // Branch is taken
    if ((IDEX_Branch_i == 1'b1) && (Zero_i == 1'b1)) begin
        PC_rollback_o = IDEX_PC_i + (IDEX_immediate_i << 1);
    end
    // Branch isn't taken
    else begin
        PC_rollback_o = IDEX_PC_i + 32'd4;
    end
end

endmodule