#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


int main(){
  int coordinate_x;
  int coordinate_y;
  int coordinate_center_x;
  int coordinate_center_y;
  int length_side;
  double in = 0, out = 0;
  double number_of_trials;
  int length_circle_radius;
  double length_random;
  double length_circle;

  srand((unsigned int)time(NULL));

  number_of_trials = 100;
  length_side = 10;
  length_circle_radius = length_side / 2;
    for(int j = 0; j < 10; j++){
    for(int i = 0; i < number_of_trials; i++){
      coordinate_x = rand() % (length_side + 1);
      coordinate_y = rand() % (length_side + 1);
      length_random = sqrt(pow(coordinate_x - 5, 2) + pow(coordinate_y - 5, 2));
      if(length_random < length_circle_radius){
       in++; 
      }
      else out++;
    }
    printf("%f\n", in / number_of_trials * 100);
    in = 0;
  }

  return 0;
}
