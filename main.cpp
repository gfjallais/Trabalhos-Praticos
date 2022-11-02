#include <iostream>
#include <string>
#include <vector>
#include "rock.hpp"


using namespace std;

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

    // for(unsigned int j = 0; j < qtd_shows; j++){
    //     cout << shows[j] << " ";
    //   }
    //   cout << endl;

    max_subarray_sum_dq(shows, qtd_shows);

  }
  return 0;
}
