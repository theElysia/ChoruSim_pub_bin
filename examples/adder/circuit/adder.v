module adder #(
    parameter WIDTH = 8
) (
    input  wire             clk,
    input  wire             rst,
    // input  wire             en,
    input  wire [WIDTH-1:0] a,
    input  wire [WIDTH-1:0] b,
    output wire [WIDTH-1:0] c
);

    reg [WIDTH-1:0] d;
    assign c = d;

    always @(posedge clk)
        if (rst) d <= 0;
        else d <= a + b;

endmodule
