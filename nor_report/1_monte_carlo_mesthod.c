#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

double calculate_area_ratio(int length_side, int coordinate_x, int coordinate_y){
  double length_circle_radius = pow(length_side / 2, 2);
  double length_random;
  double in = 0;
  coordinate_x = rand() % (length_side + 1);
  coordinate_y = rand() % (length_side + 1);
  length_random = pow(coordinate_x - (length_side / 2), 2) + pow(coordinate_y - (length_side / 2), 2);
  if(length_random <= length_circle_radius){
   in++; 
  }
  return (4 * in / 1);
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
  double pi = 0;

  srand((unsigned int)time(NULL));

  number_trials = 1;
  length_side   = 2147483647;

  PI = calculate_area_ratio(length_side, coordinate_x, coordinate_y);

  while(1){
    pi += calculate_area_ratio(length_side, coordinate_x, coordinate_y);
    PI = pi / number_trials;
    printf("円周率 =%9f, 合致率 =%10f%%, 試行回数:%f\n", PI, PI / M_PI * 100, number_trials);
    number_trials++;
  }

  return 0;
}
