#include <stdio.h>
#include <stdlib.h>

void zero_matrix(int M, int N, double A[16][16], double b[16]){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      A[i][j] = 0;
    }
  }
}

void display_matrix(int M, int N, double A[16][16], double b[16]){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      printf("|%17.10lf", A[i][j]);
    }
    printf("|%17.10lf|\n", b[i]);
  }
}

void display_position_matrix(int M, int N, int m, int n, double A[16][16], doubleb[16]){
  
}

void input_charcter_or_value(char input[16], int *input_flag){
  printf("\ninput charcter or value: ");
  scanf("%s", input);
  if('a' <= input[0] && input[0] <= 'z') *input_flag += 1;
  else if('0' <= input[0] && input[0] <= '9') *input_flag += 2;
}

void convert_character_into_value(char input[16], int *input_flag, double *matrix_element_value, double *mode_select_value){
  switch(*input_flag){
    case 0: printf("please input charcter or value\n"); break;
    case 1: printf("mode select\n"); 
            *matrix_element_value = input[0];
            break;
    case 2: printf("matrix element\n"); 
            *mode_select_value = atof(input);
            break;
    default:break;
  }
  *input_flag = 0;
}

int main(){
  int M, N;
  double A[16][16], b[16], x[16];
  char input[16]; int input_flag = 0;
  double matrix_element_value = 0;
  double mode_select_value = 0;

  printf("input how many rows and columns: ");
  scanf("%d", &M); N = M;
  zero_matrix(M, N, A, b);
  while(1){
    display_matrix(M, N, A, b);
    input_charcter_or_value(input, &input_flag);
    convert_character_into_value(input, &input_flag, &matrix_element_value, &mode_select_value);
    printf("%lf, %lf\n", matrix_element_value, mode_select_value);
  }

  return 0;
}
