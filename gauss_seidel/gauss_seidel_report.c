#include <stdio.h>
#include <stdlib.h>

void zero_matrix(int M, int N, double A[16][16], double b[16]){
  for(int i = 0; i < M; i++){
    b[i] = 0;
    for(int j = 0; j < N; j++){
      A[i][j] = 0;
    }
  }
}

void display_matrix(int M, int N, double A[16][16], double b[16]){
  for(int i = 0; i < N; i++) {printf("%17d", i + 1); if(i == N - 1) printf("\n");}
  for(int i = 0; i < M; i++){
    printf("  %d  |", i + 1);
    for(int j = 0; j < N; j++){
      printf("%17.10lf", A[i][j]);
    }
    printf("|%17.10lf|\n", b[i]);
  }
}

void display_position_matrix(int M, int N, int m, int n, double A[16][16], double b[16]){
  for(int i = 0; i < N; i++) {printf("%17d", i + 1); if(i == N - 1) printf("\n");}
  for(int i = 0; i < M; i++){
    printf("  %d  |", i + 1);
    for(int j = 0; j < N; j++){
      if(m == i && n == j) printf(" ●%15.10lf", A[i][j]);
      else printf("%17.10lf", A[i][j]); 
    }
    if(m == i && n == N) printf("| ●%15.10lf|\n", b[i]);
    else printf("|%17.10lf|\n", b[i]);
  } 
}

void input_charcter_or_value(char input[16], int *input_flag, int mode_select_flag){
  switch(mode_select_flag){
    case 0: printf("\ninput how many rows and columns\n"); break;
    case 1: printf("\n'w':up, 'd':down, 'a':left, 'd':right, 'c': caluculate matrix, 'f':input rows and columns, value:matrix element\n"); break;
    case 2: printf("\n'r':input matrix element, 'z':reset zero matrix, 'f':input rows and clumns, value:random solution\n"); break;
    default: break;
  }
  printf("input charcter or value: ");
  scanf("%s", input);
  if('a' <= input[0] && input[0] <= 'z') *input_flag = 1;
  else if('0' <= input[0] && input[0] <= '9') *input_flag = 2;
  printf("---------------------------------------------------------------------------------------------------------------------------------\n");
}

void convert_character_into_value(char input[16], int *input_flag, double *matrix_element_value, int *mode_select_value){
  switch(*input_flag){
    case 0: printf("please input charcter or value\n"); break;
    case 1: *mode_select_value = input[0];
            break;
    case 2: *matrix_element_value = atof(input);
            break;
    default:break;
  }
  printf("mode select value:%d\n", *mode_select_value);
}

void move_matrix(int M, int N, int *m, int *n, int *mode_select_value, int *input_matrix_flag, int *calculate_flag, int *mode_select_flag, int *input_rows_columns_flag){
  switch(*mode_select_value){
    case 119: *m -= 1; break;
    case  97: *n -= 1; break;
    case 115: *m += 1; break;
    case 100: *n += 1; break;
    case 102: *input_matrix_flag = 0; *calculate_flag = 0;  *input_rows_columns_flag = 1; *mode_select_flag = 0;  break;
    case  99: *input_matrix_flag = 0; *calculate_flag = 1; *mode_select_flag = 2; break;
    default: printf("----error----\n"); break;
  }
  if(*m < 0) *m = 0;
  else if(*m >= M) *m = M - 1;
  if(*n < 0) *n = 0;
  else if(*n >= N + 1) *n = N;
}

void reset_matrix(int *input_matrix_flag, int *calculate_flag, int mode_select_value, int *mode_select_flag, int *zero_matrix_flag, int *input_rows_columns_flag){
  switch(mode_select_value){
    case 102: *input_matrix_flag = 1; *calculate_flag = 0; *input_rows_columns_flag = 1; *mode_select_flag = 0; break;
    case 114: *input_matrix_flag = 1; *calculate_flag = 0; *mode_select_flag = 1; break;
    case 122: *input_matrix_flag = 1; *calculate_flag = 0; *mode_select_flag = 1; *zero_matrix_flag = 1; break;
    default: printf("----error----\n"); break;
  }
}

void input_matrix_element(int *m, int *n, int M, int N, double A[16][16], double b[16], double *matrix_element_value){
  if(*n == N) b[*m] = *matrix_element_value;
  else A[*m][*n] = *matrix_element_value;
  if(*m <= M) *m += 1;
  if(*m == M && *n == N) {*m = M - 1; *n = N;}
  else if(*m == M) {*m = 0; *n += 1;}
}

void input_random_solution(int M, double x[16], double random_solution){
  for(int i = 0; i < M; i++) x[i] = random_solution;
}

void calculate_matrix(int M, int N, double A[16][16], double b[16], double x[16]){
  int r; double B[M]; 
  printf("\ncalculate a matrix\nhow many times do you repeat?: ");
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
  printf("%5d:", k + 1);
  for(int i = 0; i < M; i++) {printf("   x[%d] = %18.10lf", i + 1, x[i]); if(i == M - 1) printf("\n");}
  } 
}

int main(){
  int m = 0, n = 0; //行列の移動のための変数
  double a[16][16], b[16], x[16]; //行列
  char input[16]; //入力のための配列
  double matrix_element_value = 0; //行列の要素の数値
  int mode_select_value = 0; //移動機能のための文字を数値に変換するための変数
  int input_flag = 0; //ここから
  int input_matrix_flag = 1; 
  int calculate_flag = 1; 
  int mode_select_flag = 0; 
  int zero_matrix_flag = 0; 
  int input_rows_columns_flag = 1; //ここまでが移動機能のためのフラッグ
  double random_solution; //適当な解を入力するための変数

  while(1){ //全体のループ
    while(input_rows_columns_flag){ //行列の数を指定するループ
      matrix_element_value = 0;
      input_charcter_or_value(input, &input_flag, mode_select_flag); 
      convert_character_into_value(input, &input_flag, &matrix_element_value, &mode_select_value);
      m = n = matrix_element_value;
      zero_matrix(m, n, a, b);
      if(matrix_element_value > 1) {input_rows_columns_flag = 0; input_matrix_flag = calculate_flag = 1; mode_select_flag = 1;}
      else printf("----error----\n");
    }
    while(input_matrix_flag){ //行列の移動と要素の入力のループ
      display_position_matrix(m, n, m, n, a, b);
      input_charcter_or_value(input, &input_flag, mode_select_flag);
      convert_character_into_value(input, &input_flag, &matrix_element_value, &mode_select_value);
      switch(input_flag){
	case 1: move_matrix(m, n, &m, &n, &mode_select_value, &input_matrix_flag, &calculate_flag, &mode_select_flag, &input_rows_columns_flag); break;
	case 2: input_matrix_element(&m, &n, m, n, a, b, &matrix_element_value); break;
	default: break;
      }
      input_flag = 0;
    }
    while(calculate_flag){ //計算のためのループ
      input_charcter_or_value(input, &input_flag, mode_select_flag);
      convert_character_into_value(input, &input_flag, &random_solution, &mode_select_value);
      switch(input_flag){
	case 1: reset_matrix(&input_matrix_flag, &calculate_flag, mode_select_value, &mode_select_flag, &zero_matrix_flag, &input_rows_columns_flag); break;
	case 2: input_random_solution(m, x, random_solution); calculate_matrix(m, n, a, b, x); break;
	default: break;
      }
      if(zero_matrix_flag) zero_matrix(m, n, a, b);
      n = m = 0;
      input_flag = 0;
    }
  }

  return 0;
}
