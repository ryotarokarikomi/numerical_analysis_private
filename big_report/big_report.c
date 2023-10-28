#include <stdio.h>
#include <ctype.h>
#include <string.h>

char word[1024][32];

int main(){
  int  alphabet_low_number = 0;
  int  alphabet_low_counter[26];
  char alphabet_low[26];
  int  alphabet_upp_number = 0;
  int  alphabet_upp_counter[26];
  char alphabet_upp[26];
  int  word_number = 0;
  int  word_length = 0; 
  int  word_flag = 0;
  int  compare_word_flag = 0;
  int  word_counter[1024];
  int blank = 0;

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
  for(int i = 0; i < 26; i++){
    printf("%c", alphabet_low[i]);
    printf("%c", alphabet_upp[i]);
  } printf("\n");

  //アルファベットを認識
  FILE *fp;
  char sentence[] = "sentence1.txt";
  char chr;
  fp = fopen(sentence, "r");

  while((chr = fgetc(fp)) != EOF){
    if(chr == ' ') {blank++;}
    for(int i = 0; i < 26; i++){
      if('a' <= chr && chr <= 'z' || 'A' <= chr && chr <= 'Z'){
	if     (chr == alphabet_low[i]){alphabet_low_counter[i] += 1; break;}
	else if(chr == alphabet_upp[i]){alphabet_upp_counter[i] += 1; break;}
      }
    } 
    if('a' <= chr && chr <= 'z' || 'A' <= chr && chr <= 'Z'){
      if(word_flag == 1){
	word_counter[word_number] = 0; 
	word_number++; 
	word_length = 0; 
	word_flag = 0; 
	for(int i = 0; i < word_number - 1; i++){
	  printf("%s == %s\n", word[word_number - 1], word[i]);
	  if(strcmp(word[word_number - 1], word[i]) == 0){
	    printf("same word\n");
	    word_counter[i]++;
	    /*for(int j = 0; j < word_length; j++){
	      word[i][j] = '\0';
	    }
	    word_number--;
	    break;*/
	  }
	}
      }
      word[word_number][word_length] = tolower(chr);
      word_length++;
    }
    else if(chr == ' ' || chr == '\n'){word_flag = 1;}

       
    
  }

  fclose(fp);

  //結果を表示
  for(int i = 0; i < 26; i++){
    printf("%c:%10d| %c:%10d\n", alphabet_low[i], alphabet_low_counter[i], alphabet_upp[i], alphabet_upp_counter[i]);
  } printf("blank:%5d\n", blank); 
  
  for(int i = 0; i <= word_number; i++){
    printf("%s, ", word[i]);
  } printf("\n");
  printf("\nnumber of words:%d\n", word_number + 1);
  for(int i=0; i < word_number; i++){
    printf("%d\n", word_counter[i]); 
  }

  return 0;
}











