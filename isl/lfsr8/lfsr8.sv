module lfsr8(clk, d, q);

    input [1:8] d;
    input clk;
    output reg [1:8] q;

    always @(d) begin
        q = d;
    end

    always @(posedge clk)
        begin
            q[1] <= (q[8] ^ q[6] ^ q[5] ^ q[3]);
            q[2] <= q[1];
            q[3] <= q[2];
            q[4] <= q[3];
            q[5] <= q[4];
            q[6] <= q[5];
            q[7] <= q[6];
            q[8] <= q[7];
        end

endmodule