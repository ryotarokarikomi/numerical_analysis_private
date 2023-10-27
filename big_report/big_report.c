#include <stdio.h>

int main(){
  int  alphabet_number_low = 0;
  char alphabet_low[26];
  int  alphabet_number_upp = 0;
  char alphabet_upp[26];

  for(int alp = 'a'; alp <= 'z'; alp++){
    alphabet_low[alphabet_number_low] = alp;
    alphabet_number_low++;
  }
  for(int alp = 'A'; alp <= 'Z'; alp++){
    alphabet_upp[alphabet_number_upp] = alp;
    alphabet_number_upp++;
  }
  for(int i = 0; i < 26; i++){
    printf("%c", alphabet_low[i]);
    printf("%c", alphabet_upp[i]);
  } printf("\n");

}

