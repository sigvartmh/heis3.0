// Wrapper for libComedi Elevator control.
// These functions provides an interface to the elevators in the real time lab
//
// 2007, Martin Korsgaard

//
// YOU DO NOT NEED TO EDIT THIS FILE
//Edited by Sigvart M. Hovland and Olav Kallerud
 b


#include "channels.h"
#include "elev.h"
#include "io.h"

#include <assert.h>
#include <stdlib.h>

// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3


// Matrix of lamp channels indexed by floor and button type. Excuse ugly macro.
#define LCM_SET(f) {LIGHT##f##_UP, LIGHT##f##_DOWN, LIGHT##f##_COMMAND}
static const int lamp_channel_matrix[N_FLOORS][N_BUTTONS] =
  {LCM_SET(1), LCM_SET(2), LCM_SET(3), LCM_SET(4)};


// Matrix of elevator button signal channels indexed by floor and button type.
#define SCM_SET(f) { FLOOR##f##_UP, FLOOR##f##_DOWN, FLOOR##f##_COMMAND }
static const int button_channel_matrix[N_FLOORS][N_BUTTONS] =
  {SCM_SET(1), SCM_SET(2), SCM_SET(3), SCM_SET(4)};



void elev_set_speed(int speed)
{
    // In order to sharply stop the elevator, the direction bit is toggled
    // before setting speed to zero.
    static int last_speed = 0;
    
    // If to start (speed > 0)
    if (speed > 0)
        io_clear_bit(MOTORDIR);
    else if (speed < 0)
        io_set_bit(MOTORDIR);

    // If to stop (speed == 0)
    else if (last_speed < 0)
        io_clear_bit(MOTORDIR);
    else if (last_speed > 0)
        io_set_bit(MOTORDIR);

    last_speed = speed ;

    // Write new setting to motor.
    io_write_analog(MOTOR, 2048 + 4*abs(speed));
}


int elev_get_obstruction_signal(void)
{
    return io_read_bit(OBSTRUCTION);
}



int elev_get_stop_signal(void)
{
    return io_read_bit(STOP);
}


int elev_get_floor_sensor_signal(void)
{
    if (io_read_bit(SENSOR1))
        return 0;
    else if (io_read_bit(SENSOR2))
        return 1;
    else if (io_read_bit(SENSOR3))
        return 2;
    else if (io_read_bit(SENSOR4))
        return 3;
    else
        return -1;
}

int elev_init(void)
{
    int i;

    // Init hardware
    if (!io_init())
        return 0;
    // Return success.
    return 1;
}



