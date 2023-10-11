#include <stdio.h>
#include <stdlib.h>

//行列を移動させる
void move_matrix(int M, int N, int *m, int *n, int move_direction_value){
  switch(move_direction_value){
    case 104: {printf("left\n");  *n -= 1; break;}
    case 106: {printf("down\n");  *m += 1; break;}
    case 107: {printf("up\n");    *m -= 1; break;}
    case 108: {printf("right\n"); *n += 1; break;}
    default: printf("error\n");
  }
  if(*m < 0) *m = 0;
  else if(*m >= M) *m = M - 1;
  if(*n < 0) *n = 0;
  else if(*n >= N) *n = N - 1;
}

//行列の表示
void display_matrix(int M, int N, int m, int n, double A[16][16]){
  for(int i = 0; i < M; i++){
  printf("|");
    for(int j = 0; j < N; j++){
      if(i == m && j == n) printf(" ●%15.10lf", A[i][j]);
      else printf("%17.10lf", A[i][j]);
    }
    printf("|\n");
  }
}

//指定された正方行列をゼロ行列に変換
void zero_matrix(int M, int N, double A[16][16]){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      A[i][j] = 0;
    }
  }
}

//入力を行い、数字と文字に分ける
void judge_character_or_value(int *mode_select, char input[16], char move_direction_character[16], char matrix_element_character[16]){
  printf("\n'h':left 'j:up ''k':down 'l':right\ninput matrix element or character: ");
  scanf("%s", input);
  int matrix_element_number = 0;
  int move_direction_number = 0;
  for(int i = 0; i < 16; i++){
    if(input[i] == '\0'){ 
      matrix_element_character[matrix_element_number] = '\0';
      move_direction_character[move_direction_number] = '\0';
      break;
    }
    else if(input[i] >= 'a' && input[i] <= 'z'){
      move_direction_character[move_direction_number] = input[i]; 
      move_direction_number++;
    }
    else if(input[i] >= '0' && input[i] <= '9'){
      matrix_element_character[matrix_element_number] = input[i];
      matrix_element_number++;
    }
    else break;
  }
  printf("%s\n", move_direction_character);
}


//行列の数字を数値に変換
double conversion_matrix_element(char matrix_element_character[16], int mode_select){
  double matrix_element_value = 0;
  matrix_element_value = atof(matrix_element_character);
  printf("matrix element value: %f\n", matrix_element_value);
  return matrix_element_value;
}

//行列の移動方向の文字を数値に変更してswitch文で扱えるようにする
int conversion_move_direction(char move_direction_character[16], int mode_select){
  int move_direction_value;
  move_direction_value = move_direction_character[0];
  printf("move direction value: %d\n", move_direction_value);
  return move_direction_value;
}





int main(){

  int M, N;
  double A[16][16], x[16], b[16];
  int m = 0, n = 0;
  int mode_select = 0;

  char move_direction_character[16];
  int  move_direction_value;
  char matrix_element_character[16];
  int  matrix_element_value;
  char input[16];

  printf("M行N列の正方行列を解きますか\n M = N = ");
  scanf("%d", &M); N = M;
  
  zero_matrix(M, N, A);

  while(1){
    display_matrix(M, N, m, n, A);

    judge_character_or_value(&mode_select, input, move_direction_character, matrix_element_character);
    printf("%d\n", mode_select);

    matrix_element_value = conversion_matrix_element(matrix_element_character, mode_select);

    move_direction_value = conversion_move_direction(move_direction_character, mode_select);

    move_matrix(M, N, &m, &n, move_direction_value);
  }

  return 0;
}
