f = open("./TP/entrada.txt", "w")
n = 10
f.write("{n_rodadas} {din_inicial}\n".format(n_rodadas = n,din_inicial = n))
for i in range(n):
    f.write("10 50\n")
    f.write("Ab 50 1O 2P 3E 4C 5O\nBc 50 1O 2P 3E 4C 5O\nCd 50 1O 2P 3E 4C 5O\nDe 50 1O 2P 3E 4C 5O\nEf 50 1O 2P 3E 4C 5O\nFg 50 1O 2P 3E 4C 5O\nGh 50 1O 2P 3E 4C 5O\nHi 50 1O 2P 3E 4C 5O\nIj 50 1O 2P 3E 4C 5O\nJk 50 1O 2P 3E 4C 5O\n")
f.close()