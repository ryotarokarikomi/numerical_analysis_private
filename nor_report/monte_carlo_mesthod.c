#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

double calculate_area_ratio(int number_trials, int length_side, int coordinate_x, int coordinate_y){
  double length_circle_radius = pow(length_side / 2, 2);
  double length_random;
  double in = 0;
  for(int i = 0; i < number_trials; i++){
    coordinate_x = rand() % (length_side + 1);
    coordinate_y = rand() % (length_side + 1);
    length_random = pow(coordinate_x - (length_side / 2), 2) + pow(coordinate_y - (length_side / 2), 2);
    if(length_random <= length_circle_radius){
     in++; 
    }
  }
  return (in / number_trials);
}

int main(){
  int coordinate_x;
  int coordinate_y;
  int coordinate_center_x;
  int coordinate_center_y;
  int length_side;
  double number_trials;
  double length_circle;
  double area_ratio;
  double PI;

  srand((unsigned int)time(NULL));

  number_trials = 2147483647;
  length_side   = 2147483647;

  for(int i = 0; i < 100; i++){
    area_ratio =  calculate_area_ratio(number_trials, length_side, coordinate_x, coordinate_y);
    PI = area_ratio * 4;
    printf("円周率 =%9f, 合致率 =%10f%%\n", PI, PI / M_PI * 100);
  }

  return 0;
}
