#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int get_random(int min, int max);
void make_random_sentence(int chr_counter, int blank_counter,  int output_counter, int blank_flag, char chr_output, char sentence[1000000], char sentence_output[1000000]);

void input_alphabet_3rd(char alphabet_3rd[27][27][27], int alphabet_number);

char alphabet_3rd[27][27][27];
char sentence_3rd[27][27][1000000];
int  sentence_3rd_number = 0;
int  alphabet_3rd_counter[27][27][27];
int  chr_3rd_counter[27][27];
int  blank_3rd_counter[27][27];
int  alphabet_number = 0;

int main(){
  input_alphabet_3rd(alphabet_3rd, alphabet_number);
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
    printf("[%2d:%2d]", i, j);
      for(int k = 0; k < 27; k++){
        printf("%c.", alphabet_3rd[i][j][k]);
      } printf("\n");
    }   
  }
  FILE *fp;
  char text[] = "bible.txt";
  char chr;

  fp = fopen(text, "r");
  while((chr = fgetc(fp)) != EOF){
  }
  fclose(fp);


  return 0;
}

void input_alphabet_3rd(char alphabet_3rd[27][27][27], int alphabet_number){
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      for(int alp = 'a'; alp <= 'z'; alp++){
        alphabet_3rd[i][j][alphabet_number] = alp;
        alphabet_number++;
      }
      alphabet_number = 0;
    }
  }
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      alphabet_3rd[i][j][26] = ' ';
    }
  }
}
