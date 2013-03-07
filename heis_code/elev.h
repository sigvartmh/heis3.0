// Wrapper for libComedi Elevator control.
// These functions provides an interface to the elevators in the real time lab
//
// 2007, Martin Korsgaard
#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__


// Number of floors
#define N_FLOORS 4
#define N_QUEUES 3 


/**
  Sets the speed of the elevator. 
  @param speed New speed of elevator. Positive values denote upward movement
    and vice versa. Set speed to 0 to stop the elevator. From -300 to 300 gives
    sensible speeds. 
*/
void elev_set_speed(int speed);



/**
  Turn door-open lamp on or off.
  @param value Non-zero value turns lamp on, 0 turns lamp off.
*/
void elev_set_door_open_lamp(int value);



/**
  Get signal from obstruction switch.
  @return 1 if obstruction is enabled. 0 if not.
*/
int elev_get_obstruction_signal(void);



/**
  Get signal from stop button.
  @return 1 if stop button is pushed, 0 if not.
*/
int elev_get_stop_signal(void);


/**
  Get floor sensor signal.
  @return -1 if elevator is not on a floor. 0-3 if elevator is on floor. 0 is
    ground floor, 3 is top floor.
*/
int elev_get_floor_sensor_signal(void);


/** Egenkode
  @returns current floor indicator lamp value
  from 0..3 calculated bitwise
*/
int elev_get_floor_indicator(void);

int elev_get_motor_dir(void);

//debugging
void print_queues(int queues[N_QUEUES][N_FLOORS]);


/**
  Button types for function elev_set_button_lamp() and elev_get_button().
*/
typedef enum tag_elev_lamp_type { 
    BUTTON_CALL_UP	 = 0, 
    BUTTON_CALL_DOWN = 1, 
    BUTTON_COMMAND	 = 2 
} elev_button_type_t;

/**
  State types for statemachine
*/
typedef enum state { 
    STATE_IDLE		= 0, 
    STATE_UP		= 1, 
    STATE_DOWN		= 2,
    STATE_DOOR_OPEN = 3,
    STATE_STOP		= 4,
    STATE_UNDEF		= 5
} current_state_t;

/**
  Gets a button signal.
  @param button Which button type to check. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside the elevator).
  @param floor Which floor to check button. Must be 0-3.
  @return 0 if button is not pushed. 1 if button is pushed.
*/
int elev_get_button_signal(elev_button_type_t button, int floor);



/**
  Set a button lamp.
  @param lamp Which type of lamp to set. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside" the elevator).
  @param floor Floor of lamp to set. Must be 0-3
  @param value Non-zero value turns lamp on, 0 turns lamp off.
*/
void elev_set_button_lamp(elev_button_type_t button, int floor, int value);



/**
  Initialize elevator hardware.
  @return Non-zero on success, 0 on failure.
*/
int elev_init(void);



#endif // #ifndef __INCLUDE_DRIVER_H__

