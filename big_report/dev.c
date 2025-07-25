#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int get_random(int min, int max);

int main(){
  int  alphabet_low_number = 0;
  int  alphabet_low_counter[26];
  char alphabet_low[26];
  int  alphabet_upp_number = 0;
  int  alphabet_upp_counter[26];
  char alphabet_upp[26];
  char sentence[10000];
  char sentence_output[10000];
  char chr_output;
  int  output_counter = 0;
  int  chr_counter = 0;
  int  blank_counter = 0;
  int  blank_flag = 0;

  for(int i = 0; i < 26; i++){
    alphabet_low_counter[i] = 0;
    alphabet_upp_counter[i] = 0;
  }

  //アルファベットの識別子を設定
  for(int alp = 'a'; alp <= 'z'; alp++){
    alphabet_low[alphabet_low_number] = alp;
    alphabet_low_number++;
  }
  for(int alp = 'A'; alp <= 'Z'; alp++){
    alphabet_upp[alphabet_upp_number] = alp;
    alphabet_upp_number++;
  }

  //アルファベットを認識
  FILE *fp;
  char text[] = "text1.txt";
  char chr;

  fp = fopen(text, "r");
  while((chr = fgetc(fp)) != EOF){
    if(chr == ' ') {blank_counter++;}
    for(int i = 0; i < 26; i++){
      if(isalpha(chr)){
	    if     (chr == alphabet_low[i]){alphabet_low_counter[i] += 1; break;}
	    else if(chr == alphabet_upp[i]){alphabet_upp_counter[i] += 1; break;}
      }
    } 
  }
  fclose(fp);

  //結果を表示
  for(int i = 0; i < 26; i++){
    printf("%c:%10d| %c:%10d\n", alphabet_low[i], alphabet_low_counter[i], alphabet_upp[i], alphabet_upp_counter[i]);
  } printf("blank:%5d, chr:%5d\n", blank_counter, chr_counter); 

//入力された文章をアルファベット順に整列させる
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < alphabet_low_counter[i] + alphabet_upp_counter[i]; j++){
      sentence[chr_counter] = alphabet_low[i];
      chr_counter++;
    }
  }
  for(int i = 0; i < blank_counter; i++){
    sentence[chr_counter + i] = ' ';
  }
  printf("%s, %d\n", sentence, chr_counter);


  //ランダムに文字を出力
  srand((unsigned int)time(NULL));
  for(int i = 0; i < chr_counter + blank_counter; i++){
    if(blank_flag == 1){
      chr_output = sentence[get_random(0, chr_counter + blank_counter - 2)];
      if(chr_output == ' '){
        sentence_output[output_counter] = chr_output;
        output_counter++;
        blank_flag = 0;
      }
      else{
        sentence_output[output_counter] = chr_output;
        output_counter++;
      } 
    }
    else if(blank_flag == 0){
      chr_output = sentence[get_random(0, chr_counter - 1)];
      sentence_output[output_counter] = chr_output;
      output_counter++;
      blank_flag = 1;
    }
  } 
  printf("%s\n", sentence_output);
  

  return 0;
}


int get_random(int min, int max){
  return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}








