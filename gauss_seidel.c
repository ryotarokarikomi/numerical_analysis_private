#include <stdio.h>

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

double conversion_matrix_element(char matrix_element_character[16]){

}

int conversion_move_direction(char move_direction_character[16]){
  int move_direction_value;
  printf("%c, ", move_direction_character[0]);
  move_direction_value = move_direction_character[0];
  printf("%d\n", move_direction_value);
  return move_direction_value;
}

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

  char move_direction_character[16];
  int  move_direction_value;
  char matrix_element_character[16];
  int  matrix_element_value;
  char input[16];


  judge_character_or_value(input, move_direction_character, matrix_element_character);

  move_direction_value = conversion_move_direction(move_direction_character);

  move_matrix(move_direction_value);



  return 0;
}
