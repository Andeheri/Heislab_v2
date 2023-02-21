
#pragma once
#include "driver/elevio.h"

void reset_lights();
void set_floor_light(int floor);
void reset_floor(int current_floor, int queue[4][3]);