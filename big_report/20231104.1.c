#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char alphabet_blank[27];

char alphabet_2nd[27][27];
char sentence_2nd[27][1000000];
int  sentence_2nd_number = 0;
int  alphabet_2nd_counter[27][27];
int  chr_2nd_counter[27];
int  blank_2nd_counter[27];

char alphabet_3rd[27][27][27];
char sentence_3rd[27][27][1000000];
int  sentence_3rd_number = 0;
int  alphabet_3rd_counter[27][27][27];
int  chr_3rd_counter[27][27];
int  blank_3rd_counter[27][27];

int  chr_limit_counter = 0;
int  alphabet_1st_number;
int  alphabet_2nd_number;

int  alphabet_low_counter[26];
char alphabet_low[26];
int  alphabet_upp_counter[26];
char alphabet_upp[26];
int  alphabet_number = 0;
char sentence[1000000];
int  sentence_NUMBER = 0;
char chr_output;
char sentence_output[1000000];
int  sentence_output_number = 0;
char sentence_original[1000000];
int  sentence_number = 0;
int  chr_counter = 0;
int  chrblank_counter = 0;
int  blank_counter = 0;
int  blank_flag = 0;
int  indection_flag = 0;

int  limit_output = 100;
int  alphabet_1st_number;
int  alphabet_2nd_number;

int get_random(int min, int max){
  return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void reset_counter(int alphabet_low_counter[26], int alphabet_upp_counter[26]){
  for(int i = 0; i < 26; i++){
    alphabet_low_counter[i] = 0;
    alphabet_upp_counter[i] = 0;
  }
}

void input_alphabet(char alphabet[26], int alphabet_number){
  for(int alp = 'a'; alp <= 'z'; alp++){
    alphabet[alphabet_number] = alp;
    alphabet_number++;
  }
}

void input_ALPHABET(char alphabet[26], int alphabet_number){
  for(int alp = 'A'; alp <= 'Z'; alp++){
    alphabet[alphabet_number] = alp;
    alphabet_number++;
  }
}

void input_alphabet_2nd(char alphabet_2nd[27][27], int alphabet_number){
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

void input_sentence_2nd(int alphabet_2nd_counter[27][27], char sentence_2nd[27][1000000], char alphabet_2nd[27][27], int sentence_2nd_number){
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      for(int k = 0; k < alphabet_2nd_counter[i][j]; k++){
	      sentence_2nd[i][sentence_2nd_number] = alphabet_2nd[i][j];
	      sentence_2nd_number++;
      }
    } sentence_2nd_number = 0;
  }
}

void input_sentence_3rd(int alphabet_3rd_counter[27][27][27], char sentence_3rd[27][27][1000000], char alphabet_3rd[27][27][27], int sentence_3rd_number){
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      for(int k = 0; k < 27; k++){
        for(int m = 0; m < alphabet_3rd_counter[i][j][k]; m++){
          sentence_3rd[i][j][sentence_3rd_number] = alphabet_3rd[i][j][k];
          sentence_3rd_number++;
        }
      } sentence_3rd_number = 0;
    }
  }
}

void sum_chr_2nd_counter(int chr_2nd_counter[27], int blank_2nd_counter[27], int alphabet_2nd_counter[27][27]){
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 26; j++){
      chr_2nd_counter[i] += alphabet_2nd_counter[i][j];
    }
  }
  for(int i = 0; i < 27; i++){
    blank_2nd_counter[i] = alphabet_2nd_counter[i][26];
  }
}

void sum_chr_3rd_counter(int chr_3rd_counter[27][27], int blank_3rd_counter[27][27], int alphabet_3rd_counter[27][27][27]){
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      for(int k = 0; k < 26; k++){
        chr_3rd_counter[i][j] += alphabet_3rd_counter[i][j][k];
      }
    }
  }
  for(int i = 0; i < 27; i++){
    for(int j = 0; j < 27; j++){
      blank_3rd_counter[i][j] = alphabet_3rd_counter[i][j][26];
    }
  }
}

int main(){
  
  //アルファベットの識別子を設定
  reset_counter(alphabet_low_counter, alphabet_upp_counter); //カウンターを0にリセット
  input_alphabet(alphabet_low, alphabet_number); //小文字の識別子
  input_ALPHABET(alphabet_upp, alphabet_number); //大文字の識別子
  input_alphabet(alphabet_blank, alphabet_number);
  alphabet_blank[26] = ' ';
  input_alphabet_2nd(alphabet_2nd, alphabet_number); //二番目の文字の識別子
  input_alphabet_3rd(alphabet_3rd, alphabet_number); //二番目の文字の識別子
  
  //テキストファイルを開いて文字を読み込む
  FILE *fp;
  char text[] = "text.txt";
  char chr;

  fp = fopen(text, "r");
  while((chr = fgetc(fp)) != EOF){
   //setence_originalに原文の改行や記号を取り除いたものを保存 
    if(isalpha(chr)){
      chr = tolower(chr);
      sentence_original[sentence_number] = chr; sentence_number++;
      for(int i = 0; i < 26; i++){//アルファベットの個数を調べる
        if(chr == alphabet_low[i]){
          alphabet_low_counter[i] += 1; 
          if(chr_limit_counter >= 1) alphabet_2nd_counter[alphabet_2nd_number][i]++;
          if(chr_limit_counter >= 2) alphabet_3rd_counter[alphabet_1st_number][alphabet_2nd_number][i]++;
          alphabet_1st_number = alphabet_2nd_number;
          alphabet_2nd_number = i;
          break;
        }
      }
      sentence[chr_counter] = tolower(chr);
      chr_counter++;
      blank_flag = 1; 
    }
    else if(blank_flag){
      if(chr == ' '){
        sentence_original[sentence_number] = ' '; sentence_number++;
        if(chr_limit_counter >= 1)alphabet_2nd_counter[alphabet_2nd_number][26]++;
        if(chr_limit_counter >= 2)alphabet_3rd_counter[alphabet_1st_number][alphabet_2nd_number][26]++;
        alphabet_1st_number = alphabet_2nd_number;
        alphabet_2nd_number = 26;
        blank_flag = 0;
        blank_counter++;
      }
      else if(chr == '\n'){
        sentence_original[sentence_number] = ' '; sentence_number++;
        if(chr_limit_counter >= 1)alphabet_2nd_counter[alphabet_2nd_number][26]++;
        if(chr_limit_counter >= 2)alphabet_3rd_counter[alphabet_1st_number][alphabet_2nd_number][26]++;
        alphabet_1st_number = alphabet_2nd_number;
        alphabet_2nd_number = 26;
        blank_flag = 0;
        blank_counter++;
      }
    }
    chr_limit_counter++;
    if(chr_limit_counter == 10000)break;
  }
  fclose(fp);

  for(int i = 0; i < 1101; i++){
    printf("%c", sentence_original[i]);
  } printf("\n");

  char alphabet_frequency[26];
  char afc;
  int  alphabet_counter[26];
  int  ac;
  for(int i = 0; i < 26; i++){
    alphabet_frequency[i] = alphabet_low[i];
    alphabet_counter[i]   = alphabet_low_counter[i];
  }
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      if(i != j){
        if(alphabet_counter[i] > alphabet_counter[j]){
          ac = alphabet_counter[j];
          alphabet_counter[j] = alphabet_counter[i];
          alphabet_counter[i] = ac;
          afc = alphabet_frequency[j];
          alphabet_frequency[j] = alphabet_frequency[i];
          alphabet_frequency[i] = afc;
        }
      }
    }
  }
  for(int i = 0; i < 26; i++){
    printf("%c:%5d\n", alphabet_frequency[i], alphabet_counter[i]);
  }

  printf("    ");
  for(int i = 0; i < 26; i++){
    printf("%5c,", alphabet_blank[i]);
  } printf("  ' ',\n");
  for(int i = 0; i < 26; i++){
    printf("%3c:", alphabet_blank[i]);
    for(int j = 0; j < 27; j++){
      printf("%5d,", alphabet_2nd_counter[i][j]);
    } printf("\n");
  }
  printf("' ':");
  for(int i = 0; i < 27; i++){
    printf("%5d,", alphabet_2nd_counter[26][i]);
  } printf("\n");

  printf("[%c]\n", alphabet_3rd[0][0][0]);
  printf("    ");
  for(int i = 0; i < 26; i++){
    printf("%5c,", alphabet_blank[i]);
  } printf("  ' ',\n");
  for(int i = 0; i < 26; i++){
    printf("%3c:", alphabet_blank[i]);
    for(int j = 0; j < 27; j++){
      printf("%5d,", alphabet_3rd_counter[0][i][j]);
    } printf("\n");
  }
  printf("' ':");
  for(int i = 0; i < 27; i++){
    printf("%5d,", alphabet_3rd_counter[0][26][i]);
  } printf("\n");

  for(int i = 0; i < blank_counter; i++){
    sentence[chr_counter + i] = ' ';
  }

  input_sentence_2nd(alphabet_2nd_counter, sentence_2nd, alphabet_2nd, sentence_2nd_number);
  input_sentence_3rd(alphabet_3rd_counter, sentence_3rd, alphabet_3rd, sentence_3rd_number);

  sum_chr_2nd_counter(chr_2nd_counter, blank_2nd_counter, alphabet_2nd_counter);
  sum_chr_3rd_counter(chr_3rd_counter, blank_3rd_counter, alphabet_3rd_counter);

  //ランダムに文字を出力
  //1次近似
  blank_flag = 0;
  srand((unsigned int)time(NULL));
  int limit_1st = limit_output;
  for(int i = 0; i < limit_1st; i++){
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
  } sentence_output_number = 0;
  printf("1次近似:%s.\n", sentence_output);

  //2次近似
  srand((unsigned int)time(NULL));
  chr_output = sentence[get_random(0, chr_counter - 1)];
  sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
  int limit_2nd = limit_output - sentence_output_number;
  for(int r = 0; r < limit_2nd; r++){
    for(int i = 0; i < 27; i++){
      if(chr_output == alphabet_2nd[i][i]){
        chr_output = sentence_2nd[i][get_random(0, chr_2nd_counter[i] + blank_2nd_counter[i] - 2)];
        sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
        break;
      }
    }
  } sentence_output_number = 0;
  printf("2次近似:%s.\n", sentence_output);

  //3次近似
  srand((unsigned int)time(NULL));
  chr_output = sentence[get_random(0, chr_counter - 1)];
  sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
  for(int i = 0; i < 26; i++){
    if(chr_output == alphabet_blank[i]){
      alphabet_1st_number = i; break;
    }
  }
  for(int i = 0; i < 27; i++){
    if(chr_output == alphabet_2nd[i][i]){
      chr_output = sentence_2nd[i][get_random(0, chr_2nd_counter[i] + blank_2nd_counter[i] - 2)];
      sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
      for(int j = 0; j < 27; j++){
        if(chr_output == alphabet_blank[j]){
          alphabet_2nd_number = j; break;
        }
      }
      break;
    }
  }
  int limit_3rd = limit_output - sentence_output_number;
  for(int i = 0; i < limit_3rd; i++){
    chr_output=sentence_3rd[alphabet_1st_number][alphabet_2nd_number][get_random(0, chr_3rd_counter[alphabet_1st_number][alphabet_2nd_number] + blank_3rd_counter[alphabet_1st_number][alphabet_2nd_number] - 2)];
    sentence_output[sentence_output_number] = chr_output; sentence_output_number++;
    alphabet_1st_number = alphabet_2nd_number;
    for(int j = 0; j < 27; j++){
      if(chr_output == alphabet_blank[j]){
        alphabet_2nd_number = j; break;
      }
    }
  }
  sentence_output_number = 0;
  printf("3次近似:%s.\n", sentence_output);

  return 0;
}
