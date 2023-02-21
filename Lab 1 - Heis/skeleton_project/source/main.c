#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "light.h"
#include "queue.h"
#include "elevator.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    // Reset lights
    reset_lights();

    //                  Up   Down   Cab
    int queue[4][3] = {{0,   0,     0},  // 0th floor
                       {0,   0,     0},  // 1st floor
                       {0,   0,     0},  // 2nd floor
                       {0,   0,     0}}; // 3rd floor
    MotorDirection direction = DIRN_STOP;
    int current_floor = elevio_floorSensor();
    int prev_floor = -1;

    int door_closed = 1;  // Closed by default
    float door_timer = 0;

    while(1){
        // if (current_floor == 0){
        //     elevio_motorDirection(DIRN_UP);
        // }
        // else if (current_floor == N_FLOORS - 1){
        //     elevio_motorDirection(DIRN_DOWN);
        // }

        for(int floor = 0; floor < N_FLOORS; floor++){
            for(int button = 0; button < N_BUTTONS; button++){
                int btnPressed = elevio_callButton(floor, button);
                if(btnPressed){
                    printf("floor: %d, button: %d \n", floor, button);
                    addToQueue(floor, button, queue, current_floor, &door_closed, &door_timer);
                }
            }
        }

        if (door_closed){ 
            current_floor = elevio_floorSensor();
            printf("Current floor: %d\n", current_floor);
            if (current_floor != -1){
                prev_floor = current_floor;
                // Updates floor light indicator
                set_floor_light(current_floor);
                // Stops elevator and opens door
                stopForCall(current_floor, direction, queue, &door_closed, &door_timer);
            }
        }
        else{
            // Fix countdown of door_timer
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
