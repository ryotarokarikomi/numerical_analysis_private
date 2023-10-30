#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int get_random(int min, int max);
void make_random_sentence(int chr_counter, int blank_counter, int output_counter, int blank_flag, char chr_output, char sentence[10000], char sentence_output[10000]);
void align_alphabet(int alphabet_low_counter[26], int alphabet_upp_counter[26], int *chr_counter, int blank_counter, char sentence[10000], char alphabet_low[26], char alphabet_upp[26]);

int main(){
  int  alphabet_low_number = 0;
  int  alphabet_low_counter[26];
  char alphabet_low[26];
  int  alphabet_upp_number = 0;
  int  alphabet_upp_counter[26];
  char alphabet_upp[26];
  char sentence[10000];
  char sentence_output[10000];
  char sentence_original[10000];
  char chr_output;
  int  output_counter = 0;
  int  chr_counter = 0;
  int  all_counter = 0;
  int  chrblank_counter = 0;
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
   //setence_originalに原文の改行や記号を取り除いたものを保存 
    if(isalpha(chr)){
      sentence_original[all_counter] = tolower(chr);
      all_counter++;
    }
    else if(chr == ' '){
      sentence_original[all_counter] = chr;
      all_counter++;
    }
    else if(chr == '\n'){
      if(sentence_original[all_counter - 1] != ' '){
        sentence_original[all_counter] = ' ';
        all_counter++;
      }
    }
    //アルファベットの個数を調べる
    if(chr == ' ') {blank_counter++;}
    for(int i = 0; i < 26; i++){
      if(isalpha(chr)){
	    if     (chr == alphabet_low[i]){alphabet_low_counter[i] += 1; chr_counter++; break;}
	    else if(chr == alphabet_upp[i]){alphabet_upp_counter[i] += 1; chr_counter++; break;}
      }
    } 
  }
  fclose(fp);
  printf("%d, %d\n", all_counter, chr_counter + blank_counter);

  //結果を表示
  for(int i = 0; i < 26; i++){
    printf("%c:%10d| %c:%10d\n", alphabet_low[i], alphabet_low_counter[i], alphabet_upp[i], alphabet_upp_counter[i]);
  } 
  chr_counter = 0;

  //入力された文章をアルファベット順に整列させる
  align_alphabet(alphabet_low_counter, alphabet_upp_counter, &chr_counter, blank_counter, sentence, alphabet_low, alphabet_upp);


  //ランダムに文字を出力
  for(int i = 0; i < all_counter; i++){ 
    printf("%c", sentence_original[i]);
  }
  make_random_sentence(chr_counter, blank_counter, output_counter, blank_flag, chr_output, sentence, sentence_output);   
  


  return 0;
}


int get_random(int min, int max){
  return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void align_alphabet(int alphabet_low_counter[26], int alphabet_upp_counter[26], int *chr_counter, int blank_counter, char sentence[10000], char alphabet_low[26], char alphabet_upp[26]){
  for(int i = 0; i < 26; i++){
      for(int j = 0; j < alphabet_low_counter[i] + alphabet_upp_counter[i]; j++){
        sentence[*chr_counter] = alphabet_low[i];
        *chr_counter += 1;
      }
    }
  for(int i = 0; i < blank_counter; i++){
    sentence[*chr_counter + i] = ' ';
  }
  printf("%5d\n", *chr_counter + blank_counter);
}

void make_random_sentence(int chr_counter, int blank_counter, int output_counter, int blank_flag, char chr_output, char sentence[10000], char sentence_output[10000]){
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
    printf("\n%s, %5d\n", sentence_output, chr_counter + blank_counter);
}


