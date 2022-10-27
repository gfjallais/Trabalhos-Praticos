.data
vetor: .word 1 2 3 4 5 6 7
.text
main:
la x12, vetor
addi x13, x0, 7
addi x13, x13, -1
slli x13, x13, 2
add x13, x13, x12
jal x1, inverte
beq x0, x0, FIM
##### START MODIFIQUE AQUI START #####
##### x12 endereço inicial do vetor
##### x13 endereço final do vetor
add x5, x0, x0
inverte: addi sp, sp, -12
		 sw x1, 8(sp)
		 slli x6, x5, 2
		 add x28, x12, x6
		 sub x29, x13, x6
         sw x28, 4(sp)
         sw x29, 0(sp)
         blt x28, x29, l1
         jalr x0, 0(x1)
l1: addi x5, x5, 1
	jal x1, inverte
    lw x29, 0(sp)
    lw x28, 4(sp)
    lw x6, 0(x29)
    lw x7, 0(x28)
    sw x6, 0(x28)
    sw x7, 0(x29)
    lw x1, 8(sp)
	addi sp, sp, 12
    jalr x0, 0(x1)
##### END MODIFIQUE AQUI END #####
FIM: add x1, x0, x10