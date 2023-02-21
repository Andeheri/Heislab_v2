
#include "elevator.h"
#include "light.h"
#include "driver/elevio.h"

void openDoor(int current_floor, int queue[4][3], int *door_closed, float *door_timer){
    elevio_doorOpenLamp(1);
    elevio_motorDirection(DIRN_STOP);
    *door_closed = 0;
    *door_timer = 3;  // Resets door timer
    reset_floor(current_floor, queue);
}