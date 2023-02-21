
#pragma once
#include "driver/elevio.h"

void addToQueue(int floor, ButtonType button, int queue[4][3], int current_floor, int *door_closed, float *door_timer);

void stopForCall(int current_floor, MotorDirection direction, int queue[4][3], int *door_closed, float *door_timer);