#include <stdio.h>
#include <stdlib.h>

//行列の表示
void display_matrix(int M, int N, int m, int n, double A[16][16], double b[16]){
  for(int i = 0; i < M; i++){
  printf("|");
    for(int j = 0; j < N; j++){
      if(i == m && j == n) printf(" ●%15.10lf", A[i][j]);
      else printf("%17.10lf", A[i][j]);
    }
    printf("|%17.10lf|\n", b[i]);
  }
}

void display_equation(int M, int N, int m, int n, double A[16][16], double b[16]){
  for(int i = 0; i < M; i++){
  printf("|");
    for(int j = 0; j < N; j++){
      printf("%17.10lf", A[i][j]);
    }
    if(i == m) printf("| ●%15.10lf|\n", b[i]);
    else printf("|%17.10lf|\n", b[i]);
  }
}

void display_solution(int M, double x[16]){
  for(int i = 0; i < M; i++){
    printf("  x%d = %7.3f, ", i + 1, x[i]);
  }
  printf("\n");
}

//行列を移動させる
void move_matrix(int M, int N, int *m, int *n, int *mode_flag, int move_direction_value){
  switch(move_direction_value){
    case 104: *n -= 1; break;
    case 106: *m += 1; break;
    case 107: *m -= 1; break;
    case 108: *n += 1; break;
    case  98: *mode_flag += 1; break;
    default: printf("error\n");
  }
  if(*m < 0) *m = 0;
  else if(*m >= M) *m = M - 1;
  if(*n < 0) *n = 0;
  else if(*n >= N) *n = N - 1;
}

void move_solution(int M, int *m, int *mode_flag, int move_direction_value){
  switch(move_direction_value){
    case 106: *m += 1; break;
    case 107: *m -= 1; break;
    case  99: *mode_flag += 1; break;
    default : printf("error\n");
  }
  if(*m < 0) *m = 0;
  else if(*m >= M) *m = M - 1;
}

void input_matrix_element(int M, int N, int *m, int *n, double A[16][16], double *matrix_element_value){
  A[*m][*n] = *matrix_element_value;
}

void input_b_element(int M, int N, int *m, int *n, double b[16], double *matrix_element_value){
  b[*m] = *matrix_element_value;
}



//適当な解の入力
void input_random_solution(double X, int M, double x[M]){
  printf("\n");
  printf("適当な解を入力してください。: ");
  scanf("%lf", &X);
  for(int i = 0; i < M; i++){
    x[i] = X;
  }
}

void calculate_matrix(int M, int N, double A[M][N], double x[M], double b[M]){
  int r; double B[M]; 
  printf("\n解を求めます。\n何回繰り返しますか。: ");
  scanf("%d", &r);
  for(int k = 0; k < r; k++){
    for(int I = 0; I < M; I++){
      B[I] = b[I];
    }
    for(int i = 0; i < M; i++){
      for(int j = 0; j < N; j++){
	if(i != j){
	  B[i] -= (A[i][j] * x[j]);
	}
      }
      x[i] = B[i] / A[i][i];
    }
    printf("%4d: ", k + 1);
  }
  display_solution(M, x);
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
void judge_character_or_value(int *mode_select, int mode_flag, char input[16], char move_direction_character[16], char matrix_element_character[16]){
  switch(mode_flag){
    case 1: printf("\n'h':left 'j:down ''k':up 'l':right 'b':input b");break;
    case 2: printf("\n'j':down 'k':up 'c':calculate"); break;
  }
  printf("\ninput matrix element or character:");
  scanf("%s", input);

  if(input[0] >= 'a' && input[0] <= 'z') {
    move_direction_character[0] = input[0];
      if(input[1] != '\0'){
	move_direction_character = "\0";
      }
  }
  else if(input[0] >= '0' && input[0] <= '9'){
    for(int i = 0; i < 16; i++){
      if(input[i] >= '0' && input[i] <= '9'){
	matrix_element_character[i] = input[i];
      }
      else matrix_element_character = "\0";
    }
  }

  }


//行列の数字を数値に変換
double conversion_matrix_element(char matrix_element_character[16], int matrix_element_value_memo, int mode_select){
  double matrix_element_value;
  matrix_element_value = atof(matrix_element_character);

  if(matrix_element_value == 0) matrix_element_value = 0;
  else matrix_element_value_memo = matrix_element_value;
  return matrix_element_value_memo;
}

//行列の移動方向の文字を数値に変更してswitch文で扱えるようにする
int conversion_move_direction(char move_direction_character[16], int mode_select){
  int move_direction_value;
  move_direction_value = move_direction_character[0];
  return move_direction_value;
}


int main(){

  int M, N;
  double A[16][16], x[16], b[16];
  int m = 0, n = 0;
  int X;
  int mode_select = 0;
  int mode_flag = 1;

  char move_direction_character[16];
  int  move_direction_value;
  char matrix_element_character[16];
  double  matrix_element_value, matrix_element_value_memo;
  char input[16];

  printf("M行N列の正方行列を解きますか\n M = N = ");
  scanf("%d", &M); N = M;
  
  zero_matrix(M, N, A);

  while(mode_flag == 1){
    display_matrix(M, N, m, n, A, b);
    judge_character_or_value(&mode_select, mode_flag, input, move_direction_character, matrix_element_character);
    matrix_element_value = conversion_matrix_element(matrix_element_character, matrix_element_value_memo, mode_select);
    move_direction_value = conversion_move_direction(move_direction_character, mode_select);
    move_matrix(M, N, &m, &n, &mode_flag, move_direction_value);
    input_matrix_element(M, N, &m, &n, A, &matrix_element_value);
  }
  m = 0;
  while(mode_flag == 2){
    display_equation(M, N, m, n, A, b);
    judge_character_or_value(&mode_select, mode_flag, input, move_direction_character, matrix_element_character);
    matrix_element_value = conversion_matrix_element(matrix_element_character, matrix_element_value_memo, mode_select);
    move_direction_value = conversion_move_direction(move_direction_character, mode_select);
    move_solution(M, &m, &mode_flag, move_direction_value);
    input_b_element(M, N, &m, &n, b, &matrix_element_value);
  }
  input_random_solution(X, M, x);
  display_equation(M, N, m, n, A, b);

  calculate_matrix(M, N, A, x, b);

  return 0;
}
