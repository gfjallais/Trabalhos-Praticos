#include "rock.hpp"

using namespace std;
int INT_MIN = -2147483647;

// Inicia o processo para encontrar o subarray com a maior soma e o máximo de shows
void max_subarray_sum_dq(float *shows, int size){
  int l = 0; int r = size;
  float aux[3] = {-1000000, -1000000, -1000000};
  max_subsum(shows, &l, &r, aux);
  cout << aux[1] + 1 << " " << aux[2] + 1 << endl;
}

//Função para encontrar o subarray com a maior soma e o máximo de shows
float max_subsum(float* shows, int *left, int *right, float *aux){

  if(*left > *right) return INT_MIN;

  if(*left == *right){
    if(shows[*left] > aux[0]){
      aux[0] = shows[*left];
      aux[1] = *left;
      aux[2] = *left;
    }
    if(shows[*left] == aux[0]){
      aux[0] = shows[*left];
      if(*left > aux[2] - aux[1]){
        aux[1] = *left;
        aux[2] = *left;
      }
    }
    return shows[*left];
  }

  int mid = (*left + *right)/2;
  int mid_minus = mid - 1;
  int mid_plus = mid + 1;
  
  return max(max(max_subsum(shows, left, &mid_minus, aux), max_subsum(shows, &mid_plus, right, aux)), 
             max_subsum_w_mid(shows, left, &mid, right, aux));
}

// Função para encontrar o maior subarray com a maior soma quando este inclui o elemento do meio
float max_subsum_w_mid(float* shows, int *left, int *mid, int *right, float *aux){
  
  int l = -1, r = -1;
  float soma = 0, left_sum = INT_MIN, right_sum = INT_MIN;

  for (int i = *mid; i >= *left; i--) {
    soma = soma + shows[i];
    if (soma > left_sum){
      l = i;
      left_sum = soma;
    }

  }

  soma = 0;
  for (int i = *mid; i <= *right; i++) {
    soma = soma + shows[i];
    if (soma > right_sum){
      right_sum = soma;
      r = i;
    } 
  }

  float max_s = max(left_sum + right_sum - shows[*mid], 
               max(left_sum, right_sum));
  if(max_s >  aux[0]){
    aux[0] = max_s;
    aux[1] = l;
    aux[2] = r;
  }
  if(max_s  == aux[0]){
    aux[0] = max_s;
    if(r - l > aux[2] - aux[1]){
        aux[1] = l;
        aux[2] = r;
    }
  }
  return max_s;
}