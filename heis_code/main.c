// REPLACE THIS FILE WITH YOUR OWN CODE.
// READ ELEV.H FOR INFORMATION ON HOW TO USE THE ELEVATOR FUNCTIONS.

#include "elev.h"
#include "ui.h"
#include "sm_macro.h"
#include <stdio.h>
#include "io.h"
#include "channels.h"


// legges i elev.h
static int queues[N_QUEUES][N_FLOORS] = {{0}};

int main()
{
	//initialize states
	int state = STATE_UNDEF;
	int previousState = 0;
	int floor = 0;
    // Initialize hardware
    if (!elev_init())
    {
        printf(__FILE__ ": Unable to initialize elevator hardware\n");
        return 1;
    }

    if (!ui_init())
    {
        printf(__FILE__ ": Unable to initialize elevator user interface\n");
        return 1;
    }

    printf("Activate obstruction and press the STOP button to stop elevator and exit program.\n");

    //Move elevator towards next bottom floor
    //if (elev_get_floor_sensor_signal() < 0)
    //{
    //    elev_set_speed(-100);
    //}
    while (1) {
		if(elev_get_floor_sensor_signal()>=0){
   		floor = elev_get_floor_sensor_signal();
		}
        //get button signal
		ui_button_signals(queues);
		ui_set_floor_indicator(floor);

		if(state != previousState){
        print_queues(queues);			
		printf("\nChanged queue:\n");
		print_queues(queues);
		printf("\n%d\n",state);
		printf("\nFloor Indicator: %i\n", ui_get_floor_indicator());
		}
        
        if(elev_get_stop_signal())
        {
            state = STATE_STOP;
        }
        
        // STATEMACHINE
        switch(state)
        {

            case STATE_IDLE:
			     if(state != previousState)
                    printf("\nidle\n");
	
				state = sm_idle(queues,previousState);
				previousState = STATE_IDLE;
				break;
            //ikke obst.

            //bestilling


            case STATE_UP:
                if(state != previousState)
			     printf("\nup\n");				
			        
				state = sm_up(queues);
				previousState = STATE_UP;
				break;

            case STATE_DOWN:
			     if(state != previousState)
                 printf("\ndown\n");

				state = sm_down(queues);
				previousState = STATE_DOWN;
                break;

            case STATE_DOOR_OPEN:
                if(state != previousState)
			         printf("\ndoor open\n");
				state =sm_door_open(queues,previousState);
                previousState = STATE_DOOR_OPEN;
				break;

            case STATE_STOP:
                if(state != previousState)
			      printf("\nstop state\n");
                //kanskje gøre denne mer modulær type
				state = sm_stop(queues);
				break;

            case STATE_UNDEF:
			printf("\nundef state\n");
            	//If the elevator do not are on a floor, move until it gets to the floor underneath
				state = sm_undef();			
				break;
                //break;//crash it!
		}


    	// Check if stop button and obstruction is active, if so, stop elevator and exit program.
		/*
		if (elev_get_obstruction_signal() &&  elev_get_stop_signal() ) {
            elev_set_speed(0);
            break;
    	}
		*/

    }//End While

    return 0;

}

