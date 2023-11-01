#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char alphabet_2nd[27][27];
char sentence_2nd[27][1000000];
int  sentence_2nd_number = 0;
int  alphabet_2nd_counter[27][27];

int get_random(int min, int max);
void make_random_sentence(int chr_counter, int blank_counter,  int output_counter, int blank_flag, char chr_output, char sentence[1000000], char sentence_output[1000000]);

char alphabet_2nd[27][27];
int  alphabet_2nd_counter[27][27];
int  chr_2nd_counter[27];
int  blank_2nd_counter[27];

int main(){
  int  chr_limit_counter = 0;

  int  alphabet_1st_number;

  int  alphabet_low_counter[26];
  char alphabet_low[26];

  int  alphabet_upp_counter[26];
  char alphabet_upp[26];

  int  alphabet_number = 0;

  char sentence[1000000];
  char sentence_output[1000000];
  int  sentence_output_number = 0;
  char sentence_original[1000000];
  int  sentence_number = 0;

  char chr_output;
  int  chr_counter = 0;
  int  chrblank_counter = 0;
  int  blank_counter = 0;
  int  blank_flag = 0;
  int  indection_flag = 0;

  for(int i = 0; i < 26; i++){
    alphabet_low_counter[i] = 0;
    alphabet_upp_counter[i] = 0;
  }
  //アルファベットの識別子を設定
  for(int alp = 'a'; alp <= 'z'; alp++){
    alphabet_low[alphabet_number] = alp;
    alphabet_number++;
  } alphabet_number = 0;
  for(int alp = 'A'; alp <= 'Z'; alp++){
    alphabet_upp[alphabet_number] = alp;
    alphabet_number++;
  } alphabet_number = 0;
  for(int i = 0; i < 27; i++){
    for(int alp = 'a'; alp <= 'z'; alp++){
      alphabet_2nd[i][alphabet_number] = alp;
      alphabet_number++;
    }
    alphabet_number = 0;
  }
  for(int i = 0; i < 27; i++){
    alphabet_2nd[i][26] = ' ';
  }

  //アルファベットを認識
  FILE *fp;
  char text[] = "bible.txt";
  char chr;

  fp = fopen(text, "r");
  while((chr = fgetc(fp)) != EOF){
    chr_limit_counter++;
   //setence_originalに原文の改行や記号を取り除いたものを保存 
    if(isalpha(chr)){
      sentence_original[sentence_number] = tolower(chr); sentence_number++;
      for(int i = 0; i < 26; i++){//アルファベットの個数を調べる
        if     (chr == alphabet_low[i]){alphabet_low_counter[i] += 1; alphabet_2nd_counter[alphabet_1st_number][i]++; alphabet_1st_number = i; break;}
	      else if(chr == alphabet_upp[i]){alphabet_upp_counter[i] += 1; alphabet_2nd_counter[alphabet_1st_number][i]++; alphabet_1st_number = i; break;}
      }
      sentence[chr_counter] = tolower(chr);
      chr_counter++;
      blank_flag = 1; indection_flag = 1;
    }
    else if(chr == ' ' && blank_flag && indection_flag){
      sentence_original[sentence_number] = ' '; sentence_number++;
      alphabet_2nd_counter[alphabet_1st_number][26]++;
      alphabet_1st_number = 26;
      blank_flag = 0;
      blank_counter++;
    }
    else if(chr == '\n' && blank_flag && indection_flag){
      sentence_original[sentence_number] = ' '; sentence_number++;
      alphabet_2nd_counter[alphabet_1st_number][26]++;
      alphabet_1st_number = 26;
      indection_flag = 0;
      blank_counter++;
    }
    if(chr_limit_counter == 1000000)break;
  }
  fclose(fp);

  for(int i = 0; i < blank_counter; i++){
    sentence[chr_counter + i] = ' ';
  }
  //結果を表示
  for(int i = 0; i < 26; i++){
    printf("%c:%10d| %c:%10d\n", alphabet_low[i], alphabet_low_counter[i], alphabet_upp[i], alphabet_upp_counter[i]);
  } 

  for(int i = 0; i < 27; i++){
    printf("%c: ", alphabet_low[i]);
    for(int j = 0; j < 27; j++){
      printf("%5d ", alphabet_2nd_counter[i][j]);
    } printf("\n");
  }
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      for(int k = 0; k < alphabet_2nd_counter[i][j]; k++){
	      sentence_2nd[i][sentence_2nd_number] = alphabet_2nd[i][j];
	      sentence_2nd_number++;
      }
    } sentence_2nd_number = 0;
  }
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 26; j++){
      chr_2nd_counter[i] += alphabet_2nd_counter[i][j];
    }
  }
  for(int i = 0; i < 27; i++){
    blank_2nd_counter[i] = alphabet_2nd_counter[i][26];
  }
  for(int i = 0; i < 27; i++){
    printf("%5d, %5d\n", chr_2nd_counter[i], blank_2nd_counter[i]);
  }


  //ランダムに文字を出力
  srand((unsigned int)time(NULL));
  chr_output = sentence[get_random(0, chr_counter - 1)];
  sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
  for(int r = 0; r < 100; r++){
    for(int i = 0; i < 27; i++){
      if(chr_output == alphabet_2nd[i][i]){
        chr_output = sentence_2nd[i][get_random(0, chr_2nd_counter[i] + blank_2nd_counter[i] - 2)];
        sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
        break;
      }
    }
  } sentence_output_number = 0;
  printf("2次近似:%s.\n", sentence_output);

  blank_flag = 0;
  srand((unsigned int)time(NULL));
    for(int i = 0; i < 100; i++){
      if(blank_flag == 1){
        chr_output = sentence[get_random(0, chr_counter + blank_counter - 2)];
        if(chr_output == ' '){
          sentence_output[sentence_output_number] = chr_output;
          sentence_output_number++;
          blank_flag = 0;
        }
        else{
          sentence_output[sentence_output_number] = chr_output;
          sentence_output_number++;
        } 
      }
      else if(blank_flag == 0){
        chr_output = sentence[get_random(0, chr_counter - 1)];
        sentence_output[sentence_output_number] = chr_output;
        sentence_output_number++;
        blank_flag = 1;
      }
    }
  printf("1次近似:%s.\n", sentence_output);
  return 0;
}


int get_random(int min, int max){
  return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

