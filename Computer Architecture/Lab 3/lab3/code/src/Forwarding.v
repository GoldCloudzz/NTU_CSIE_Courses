module ForwardingUnit(IDEX_rs1_i, IDEX_rs2_i, EXMEM_rd_i, MEMWB_rd_i, EXMEM_RegWrite_i, MEMWB_RegWrite_i, ForwardA_o, ForwardB_o);

input [4:0] IDEX_rs1_i, IDEX_rs2_i, EXMEM_rd_i, MEMWB_rd_i;
input EXMEM_RegWrite_i, MEMWB_RegWrite_i;

output reg [1:0] ForwardA_o, ForwardB_o;

always @(*) begin
    // EX hazard
    if ((EXMEM_RegWrite_i == 1'b1) && (EXMEM_rd_i != 5'b00000) && (EXMEM_rd_i == IDEX_rs1_i)) begin
        ForwardA_o = 2'b10;
    end
    // MEM hazard
    else if ((MEMWB_RegWrite_i == 1'b1) && (MEMWB_rd_i != 5'b00000) && (MEMWB_rd_i == IDEX_rs1_i)) begin
        ForwardA_o = 2'b01;
    end
    // No hazard
    else begin
        ForwardA_o = 2'b00;
    end
end

always @(*) begin
    // EX hazard
    if ((EXMEM_RegWrite_i == 1'b1) && (EXMEM_rd_i != 5'b00000) && (EXMEM_rd_i == IDEX_rs2_i)) begin
        ForwardB_o = 2'b10;
    end
    // MEM hazard
    else if ((MEMWB_RegWrite_i == 1'b1) && (MEMWB_rd_i != 5'b00000) && (MEMWB_rd_i == IDEX_rs2_i)) begin
        ForwardB_o = 2'b01;
    end
    // No hazard
    else begin
        ForwardB_o = 2'b00;
    end
end

endmodule