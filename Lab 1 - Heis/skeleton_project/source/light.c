
#include "light.h"
#include "driver/elevio.h"
#include <stdio.h>


void reset_lights(){
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                elevio_buttonLamp(f, b, 0);
            }
    }
    elevio_doorOpenLamp(0);
}

void set_floor_light(int floor){
    elevio_floorIndicator(floor);
}

void reset_floor(int current_floor, int queue[4][3]){
    // Clear queue
    for (int i = 0; i < 3; i++){
        queue[current_floor][i] = 0;
    }
    for (int i = 0; i < 3; i++){
        elevio_buttonLamp(current_floor, i, 0);
    }

}