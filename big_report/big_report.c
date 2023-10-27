#include <stdio.h>

int main(){
  int  alphabet_low_number = 0;
  int  alphabet_low_counter[26];
  char alphabet_low[26];
  int  alphabet_upp_number = 0;
  int  alphabet_upp_counter[26];
  char alphabet_upp[26];
  
  int blank = 0;

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
  char sentence[] = "sentence.txt";
  char chr;
  fp = fopen(sentence, "r");

  while((chr = fgetc(fp)) != EOF){
    putchar(chr);
    for(int i = 0; i < 26; i++){
      if(chr == ' ') {blank++; break;}
      else if(chr == alphabet_low[i]){alphabet_low_counter[i] += 1; break;}
      else if(chr == alphabet_upp[i]){alphabet_upp_counter[i] += 1; break;}
    }
  }

  fclose(fp);

  //結果を表示
  for(int i = 0; i < 26; i++){
    printf("%c:%5d| %c:%5d\n", alphabet_low[i], alphabet_low_counter[i], alphabet_upp[i], alphabet_upp_counter[i]);
  } printf("blank:%5d\n", blank); 
  
  return 0;
}
