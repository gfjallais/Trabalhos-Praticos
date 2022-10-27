`include "lfsr8.sv"

module lfsr8_tb();

    integer f_out;
    reg clk;
    wire [1:8] q;
    reg [1:8] d;


    initial begin

        f_out = "lfsr8_tb.out", "w");

        if(!f_out)
            $display("Arquivo não abriu corretamente");

        clk = 1'b0;

        d = 1;

        repeat(1020) begin

            #1
            
            clk = ~clk;

            if(clk == 1) begin
                $fwrite(f_out, "%d ", q);
            end

        end

        $fclose(f_out); 
    end

    lfsr8 RNG(clk, d, q);
endmodule