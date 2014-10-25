#include "ProstheticCtrlDirectionTypes.h"


bool get_prosthetic_ctrl_direction_type_string(ProstheticCtrlDirectionType direction_type, char *str)
{
	switch (direction_type)
	{
		case PROSTHETIC_CTRL_DIRECTION_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_UP:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_UP");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_DOWN:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_DOWN");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_UP_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_UP_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_UP_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_UP_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_DOWN_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_DOWN_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_DOWN_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_DOWN_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_UP:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_UP");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_DOWN:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_DOWN");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_UP_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_UP_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_UP_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_UP_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_DOWN_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_DOWN_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_FORWARD_DOWN_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_FORWARD_DOWN_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_UP:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_UP");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_DOWN:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_DOWN");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_UP_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_UP_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_UP_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_UP_RIGHT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_DOWN_LEFT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_DOWN_LEFT");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_BACKWARD_DOWN_RIGHT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_BACKWARD_DOWN_RIGHT");
			return TRUE;

		case PROSTHETIC_CTRL_DIRECTION_ROTATE_CLOCKWISE:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_ROTATE_CLOCKWISE");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_ROTATE_COUNTER_CLOCKWISE:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_ROTATE_COUNTER_CLOCKWISE");
			return TRUE;

		case PROSTHETIC_CTRL_DIRECTION_STATIONARY:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_STATIONARY");
			return TRUE;
		case PROSTHETIC_CTRL_DIRECTION_UNSPECIFIED:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_UNSPECIFIED");
			return TRUE;

////////////////////////		
		case PROSTHETIC_CTRL_DIRECTION_NULL:
 			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_NULL");
			return FALSE;
		default:
 			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_DIRECTION_INVALID");
			return FALSE;
	}
}