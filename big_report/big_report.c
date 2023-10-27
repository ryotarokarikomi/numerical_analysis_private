#include <stdio.h>

int main(){
  int  alphabet_number_low = 0;
  int  alphabet_counter_low[26];
  char alphabet_low[26];
  int  alphabet_number_upp = 0;
  int  alphabet_counter_upp[26];
  char alphabet_upp[26];
  
  int unknown = 0;

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

  FILE *fp;
  char sentence[] = "sentence.txt";
  char chr;
  fp = fopen(sentence, "r");

  while((chr = fgetc(fp)) != EOF){
    putchar(chr);
    for(int i = 0; i < 26; i++){
      if     (chr == alphabet_low[i]){alphabet_counter_low[i] += 1; break;}
      else if(chr == alphabet_upp[i]){alphabet_counter_upp[i] += 1; break;}
    }
  }

  fclose(fp);

  for(int i = 0; i < 26; i++){
    printf("%c:%5d| %c:%5d\n", alphabet_low[i], alphabet_counter_low[i], alphabet_upp[i], alphabet_counter_upp[i]);

  } 
  
  return 0;
}
