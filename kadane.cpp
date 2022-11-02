#include <climits>
#include <iostream>
#include <fstream>
using namespace std;

std::ofstream MyFile_out("saida.txt");

void maxSubArraySum(float a[], int size)
{
    float max_so_far = INT_MIN, max_ending_here = 0,
        start = 0, end = 0, s = 0;
 
    for (int i = 0; i < size; i++) {
        max_ending_here += a[i];
 
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
 
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    
    MyFile_out << max_so_far << " " << start + 1 << " " << end + 1 << endl;
}
 
/*Driver program to test maxSubArraySum*/

int main() {
  
  unsigned int qtd_amigos; // 1 <= qtd_amigos <= 50
  unsigned int qtd_shows; // 1 <= qtd_shows <= 100000
  float aux;
  
  while(cin >> qtd_amigos >> qtd_shows){

    if(qtd_amigos == 0 && qtd_shows == 0) break;
    
    float shows[qtd_shows] = {0};

    for(unsigned int i = 0; i < qtd_amigos; i++){
      for(unsigned int j = 0; j < qtd_shows; j++){
        cin >> aux;
        shows[j] += aux;
      }
    }

    maxSubArraySum(shows, qtd_shows);

  }
  MyFile_out.close();
  return 0;
}