#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

#define N_FLOORS 4

typedef enum queue_tag_orders
{
	 QUEUE_UP      = 0 //BUTTON_CALL_UP
	,QUEUE_DOWN    = 1 //BUTTON_CALL_DOWN
	,QUEUE_COMMAND = 2 //BUTTON_COMMAND
} order_t;


void queue_add(int queue,int floor);

void queue_remove(int queue,int floor);

/** 
Initializes Queue system
*/
bool queue_init(void);


#endif
