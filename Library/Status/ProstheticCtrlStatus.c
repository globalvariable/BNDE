#include "ProstheticCtrlStatus.h"


bool get_prosthetic_ctrl_status_type_string(ProstheticCtrlStatus prosthetic_ctrl_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (prosthetic_ctrl_status_type)
	{
		case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL");
			return TRUE;		
		case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT");
			return TRUE;		
		case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL");
			return TRUE;
		case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT");
			return TRUE;
		case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT");
			return TRUE;
		case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT");
			return TRUE;
		case PROSTHETIC_CTRL_STATUS_DISABLED:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_DISABLED");
			return TRUE;

/////////////////////////		
		case PROSTHETIC_CTRL_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_STATUS_INVALID");
			return FALSE;
	}
}
