
#include <stdio.h>
#include "driver/elevio.h"
#include "elevator.h"

void addToQueue(int floor, ButtonType button, int queue[4][3], int current_floor, int *door_closed, float *door_timer){
    if (floor != current_floor){
        elevio_buttonLamp(floor, button, 1);  // Turns on button light
        queue[floor][button] = 1;
    }
    else{
        openDoor(current_floor, queue, door_closed, door_timer);
    }

    // If at current floor: reset timer for door
}

void stopForCall(int current_floor, MotorDirection direction, int queue[4][3], int *door_closed, float *door_timer){
    if (queue[current_floor][BUTTON_CAB]){
        openDoor(current_floor, queue, door_closed, door_timer);
    }
    else if ((queue[current_floor][BUTTON_HALL_DOWN] || queue[current_floor][BUTTON_HALL_UP]) && \
            (direction == DIRN_STOP)){
        openDoor(current_floor, queue, door_closed, door_timer);
    }
    else if (((direction == DIRN_UP) && queue[current_floor][BUTTON_HALL_UP]) || \
            ((direction == DIRN_DOWN) && queue[current_floor][BUTTON_HALL_DOWN])){
        openDoor(current_floor, queue, door_closed, door_timer);
    }
}