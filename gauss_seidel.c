#include <stdio.h>
#include <stdlib.h>

void display_matrix(int M, int N, double A[16][16]){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      printf("%lf\n", A[i][j]);
    }
  }
}

void zero_matrix(int M, int N, double A[16][16]){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      A[i][j] = 0;
    }
  }
  display_matrix(M, N, A);
}

//入力を数字と文字に分ける
void judge_character_or_value(char input[16], char move_direction_character[16], char matrix_element_character[16]){
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
  printf("%s\n", matrix_element_character);
  printf("%s\n", move_direction_character);
}

//行列の数字を数値に変換
double conversion_matrix_element(char matrix_element_character[16]){
  double matrix_element_value;
  matrix_element_value = atof(matrix_element_character);
  printf("%f\n", matrix_element_value);
  return matrix_element_value;
}

//行列の移動方向の文字を数値に変更してswitch文で扱えるようにする
int conversion_move_direction(char move_direction_character[16]){
  int move_direction_value;
  printf("%c, ", move_direction_character[0]);
  move_direction_value = move_direction_character[0];
  printf("%d\n", move_direction_value);
  return move_direction_value;
}

//行列を移動させる
void move_matrix(int move_matrix_direction){
  switch(move_matrix_direction){
    case 104: printf("left\n"); break;
    case 106: printf("down\n"); break;
    case 107: printf("up\n"); break;
    case 108: printf("right\n"); break;
    default: printf("error\n");
  }
}



int main(){

  int M, N;
  double A[16][16], x[16], b[16];

  char move_direction_character[16];
  int  move_direction_value;
  char matrix_element_character[16];
  int  matrix_element_value;
  char input[16];

  printf("M行N列の正方行列を解きますか\n M = N = ");
  scanf("%d", &M); N = M;
  
  zero_matrix(M, N, A);

  judge_character_or_value(input, move_direction_character, matrix_element_character);

  matrix_element_value = conversion_matrix_element(matrix_element_character);

  move_direction_value = conversion_move_direction(move_direction_character);

  move_matrix(move_direction_value);



  return 0;
}
