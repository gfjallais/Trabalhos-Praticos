from calendar import c
import string
import random

Num = 100
e = 1
c = 1
a = 1

def RandomStringGenerator():
    print_list = [a for a in string.printable if a not in string.whitespace]

    string_size = random.randrange(1, 11)

    random_list = random.choices(print_list, k=string_size)

    random_string = "".join(random_list)

    return random_string


def RandomMessage(number_words):
    message = ""

    for i in range(number_words - 1):
        message += RandomStringGenerator() + " "

    message += RandomStringGenerator()

    return message


def generateENTREGAS(number_Entregas, arquivo):
    for i in range(number_Entregas):
        User_Number = random.randrange(0, 150)

        Message_Number = random.randrange(0, 500)

        Word_number = random.randrange(1, 30)
        Output_string = (
            ""
            + "\nENTREGA "
            + str(User_Number)
            + " "
            + str(Message_Number)
            + " "
            + str(Word_number)
            + " "
            + RandomMessage(Word_number)
        )

        arquivo.write(Output_string)


def generateCONSULTAS(number_Consultas, arquivo):
    for i in range(number_Consultas):
        User_Number = random.randrange(0, 150)

        Message_Number = random.randrange(0, 500)

        Output_string = (
            "" + "\nCONSULTA " + str(User_Number) + " " + str(Message_Number)
        )

        arquivo.write(Output_string)


def generateAPAGAS(number_Apagas, arquivo):
    for i in range(number_Apagas):
        User_Number = random.randrange(0, 150)

        Message_Number = random.randrange(0, 500)

        Output_string = "" + "\nAPAGA " + str(User_Number) + " " + str(Message_Number)

        arquivo.write(Output_string)

File_name = "entrada.txt"
Output_file = open(File_name, "w")

# Hash_Table_Size = int(input("Tamanho desejado para Tabela Hash: "))
Hash_Table_Size = 100
Output_file.write(str(Hash_Table_Size))

# Number_Entregas_File = int(input("Número desejado de ENTREGAs no arquivo: "))
Number_Entregas_File = int(Num*e)
generateENTREGAS(Number_Entregas_File, Output_file)

# Number_Consultas_File = int(input("Número desejado de CONSULTAs no arquivo: "))
Number_Consultas_File = int(Num*c)
generateCONSULTAS(Number_Consultas_File, Output_file)

# Number_Exclusoes_File = int(input("Número desejado de APAGAs no arquivo: "))
Number_Exclusoes_File = int(Num*a)
generateAPAGAS(Number_Exclusoes_File, Output_file)
