/**
	handels button input/user interaction from panel
*/
#include "ui.h"
#include "elev.h"



void ui_remove_order_light(int floor,int direction)
{
	if(direction) {
		switch(floor) 
		{

		case 0:
			CLEAR_BIT(PORT3, LIGHT_UP1);
			CLEAR_BIT(PORT3, LIGHT_ORD1);
			break;

		case 1:
			CLEAR_BIT(PORT3, LIGHT_ORD2);
			CLEAR_BIT(PORT3, LIGHT_UP2);
			break;

		case 2:
			CLEAR_BIT(PORT3, LIGHT_ORD3);
			CLEAR_BIT(PORT3, LIGHT_UP3);
			break;

		case 3:
			CLEAR_BIT(PORT3, LIGHT_DOWN4);
			CLEAR_BIT(PORT3, LIGHT_ORD4);
			break;
		}
	}

	else {
		switch(floor) {
		
		case 0:
			CLEAR_BIT(PORT3, LIGHT_UP1);
			CLEAR_BIT(PORT3, LIGHT_ORD1);
			break;

		case 1:
			CLEAR_BIT(PORT3, LIGHT_ORD2);
			CLEAR_BIT(PORT3, LIGHT_DOWN2);
			break;
		
		case 2:
			CLEAR_BIT(PORT3, LIGHT_ORD3);
			CLEAR_BIT(PORT3, LIGHT_DOWN3);
			break;
		
		case 3:
			CLEAR_BIT(PORT3, LIGHT_DOWN4);
			CLEAR_BIT(PORT3, LIGHT_ORD4);
			break;
		}
	}
}
