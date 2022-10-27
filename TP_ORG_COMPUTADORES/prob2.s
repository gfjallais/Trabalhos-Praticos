.data
vetor: .word 1 2 3 4 5 6 7 8 9 10
.text
main:
la x12, vetor
addi x13, x0, 11
addi x14, x0, 1 # Flag se é cnpj ou cpf
jal x1, verificadastro
beq x0,x0,FIM
##### START MODIFIQUE AQUI START #####
verificacpf: addi x5, x0, 11
			 beq x5, x13, tamanho_aceito_cpf
			 jalr x0, 0(x1)
tamanho_aceito_cpf:addi x10, x0, 1
			 add x5, x0, x0 # soma = 0
		     addi x6, x0, 10 # i = 10
             addi x29, x0, 2
             addi x28, x12, 40 # vetor[10]
loop1:       slli x7, x6, 2 # i * 4 pq é 32 bits
             sub x7, x28, x7 # cpf[10 - i]
             lw x7, 0(x7) # conteudo de cpf[10 - i]
             mul x7, x7, x6 # cpf[10 - i] * i
             add x5, x5, x7 # soma += cpf[10 - i] * i
             addi x6, x6, -1 # i--
             bge x6, x29, loop1
             addi x28, x0, 11 
             rem x7, x5, x28 # soma%11
             blt x7, x29, condition1 # soma%11 < 2
             sub x30, x28, x7 # digito1 = 11 - soma%11
             beq x0, x0, else
condition1:  add x30, x0, x0 # digito1 = 0
else:	 	 add x5, x0, x0 # soma = 0
 			 addi x6, x0, 11 # i = 11
             addi x29, x0, 3
             addi x28, x12, 44 # vetor[11]
loop2:    	 slli x7, x6, 2 # i * 4 pq é 32 bits
             sub x7, x28, x7 # cpf[11 - i]
             lw x7, 0(x7) # conteudo de cpf[11 - i]
             mul x7, x7, x6 # cpf[11 - i] * i
             add x5, x5, x7 # soma += cpf[11 - i] * i
             addi x6, x6, -1 # i--
             bge x6, x29, loop2
             slli x4, x30, 1 # digito1 * 2
             add x5, x5, x4  # soma+= digito1 *2
             addi x28, x0, 11 
             rem x7, x5, x28 # soma%11
             addi x29, x29, -1
             blt x7, x29, condition2 # soma%11 < 2
             addi x6, x0, 11
             sub x31, x6, x7 # digito2 = 11 - soma%11
             beq x0, x0, verificacao
condition2:  add x31, x0, x0 # digito2 = 0
verificacao: addi x7, x12, 36
             lw x7, 0(x7) # cpf[9]
			 addi x6, x12, 40 
             lw x6, 0(x6) # cpf[10]
             beq x30, x7, condition3
             add x10, x0, x0
condition3:  beq x31, x6, return1
			 add x10, x0, x0
return1: 	 jalr x0, 0(x1)
##################################################
verificacnpj:addi x5, x0, 14
			 beq x5, x13, tamanho
		 	 jalr x0, 0(x1)
tamanho:	 addi x10, x0, 1
			 addi x6, x0, 5 # num = 5
			 add x5, x0, x0 # soma = 0
             add x7, x0, x0 # i = 0
             addi x30, x0, 12
             addi x28, x0, 1
loop_cnpj1:	 slli x31, x7, 2
			 bne x6, x28, if1 # if(num == 1)
			 addi x6, x6, 8 # num = 9
if1:		 add x29, x12, x31 # endereço cnpj[i]
			 lw x29, 0(x29) # conteudo cnpj[i]
             mul x29, x29, x6 # num * cnpj[i]
             add x5, x5, x29 # soma += num * cnpj[i]
			 addi x7, x7, 1 # i++
             addi x6, x6, -1 # num--
             blt x7, x30, loop_cnpj1
             addi x30, x0, 11 
             rem x7, x5, x30 # soma%11
             addi x29, x0, 2
             blt x7, x29, cd_cnpj1 # soma%11 < 2
             sub x30, x30, x7 # digito1 = 11 - soma%11
             beq x0, x0, else_cnpj1
cd_cnpj1:    add x30, x0, x0 # digito1 = 0
else_cnpj1:	 addi x6, x0, 6 # num = 6
			 add x5, x0, x0 # soma = 0
             add x7, x0, x0 # i = 0
             addi x31, x0, 12
             addi x28, x0, 1
loop_cnpj2:	 slli x8, x7, 2
			 bne x6, x28, if2 # if(num == 1)
			 addi x6, x6, 8 # num = 9
if2:		 add x29, x12, x8 # endereço cnpj[i]
			 lw x29, 0(x29) # conteudo cnpj[i]
             mul x29, x29, x6 # num * cnpj[i]
             add x5, x5, x29 # soma += num * cnpj[i]
			 addi x7, x7, 1 # i++
             addi x6, x6, -1 # num--
             blt x7, x31, loop_cnpj2
             slli x4, x30, 1
             add x5, x5, x4
			 addi x31, x0, 11 
             rem x7, x5, x31 # soma%11
             addi x29, x0, 2
             blt x7, x29, condition1 # soma%11 < 2
             sub x31, x31, x7 # digito2 = 11 - soma%11
             beq x0, x0, verificacao2
cd_cnpj2:    add x31, x0, x0 # digito2 = 0
verificacao2:addi x7, x12, 48
             lw x7, 0(x7) # cpf[12]
			 addi x6, x12, 52
             lw x6, 0(x6) # cpf[13]
             beq x30, x7, cd_cnpj3
             add x10, x0, x0
cd_cnpj3:  	 beq x31, x6, return2
			 add x10, x0, x0
return2: 	 jalr x0, 0(x1)
######################################################
verificadastro: add x5, x0, x14
			 beq x5, x0, verificacpf
             beq x0, x0, verificacnpj
			 jalr x0, 0(x1) 
##### END MODIFIQUE AQUI END #####
FIM: add x1, x0, x10