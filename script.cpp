#include <random>
#include <fstream>
#include <iomanip>

int main() {
    int LO = -5;
    int HI = 5;
    int num_casos_teste = 100;

    std::ofstream MyFile_in("entrada.txt");

    for (int i = 0; i < num_casos_teste; i++){

        int num_amigos = rand() % 50 + 1;
        int num_shows = rand() % 100 + 1;

        MyFile_in << num_amigos << " " << num_shows << std::endl;

        for(int j = 0; j < num_amigos; j++){

            for(int k = 0; k < num_shows; k++){

                MyFile_in << std::setprecision(1) << LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO))) << " ";

            }

            MyFile_in << std::endl;

        }

    }
    // Close the file
    MyFile_in.close();
    

}
