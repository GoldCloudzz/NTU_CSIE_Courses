module Branch_Predictor(clk_i, Branch_i, result_i, predict_o);

input clk_i;
input Branch_i, result_i;

output predict_o;

reg [1:0] state;

initial state = 2'b11;

always @ (posedge clk_i) begin
    if (Branch_i == 1'b1) begin
        // Correct prediction
        if (result_i == 1'b1) begin
            if (state != 2'b11) begin
                state <= (state + 2'b01);
            end
            else begin
                state <= state;
            end
        end
        // Wrong prediction
        if (result_i == 1'b0) begin
            if (state != 2'b00) begin
                state <= (state - 2'b01);
            end
            else begin
                state <= state;
            end
        end
    end
    // No prediction
    else begin
        state <= state;
    end
end

assign predict_o = state >> 1;

endmodule