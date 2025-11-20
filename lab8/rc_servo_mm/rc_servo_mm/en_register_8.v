module en_register_8(input wire [7:0] D, input wire clk, en, output reg [7:0] Q);

	always@(posedge clk) begin
		if (en)
			Q <= D;
	end
	
endmodule
