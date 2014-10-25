#include "DioCtrlComponentStatus.h"


bool get_dio_ctrl_comp_status_type_string(DioCtrlCompStatus dio_ctrl_comp_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (dio_ctrl_comp_status_type)
	{
		case DIO_CTRL_COMP_STATUS_LOW:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_LOW");
			return TRUE;		
		case DIO_CTRL_COMP_STATUS_LOW_SUCCESS:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_LOW_SUCCESS");
			return TRUE;		
		case DIO_CTRL_COMP_STATUS_HIGH:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_HIGH");
			return TRUE;
		case DIO_CTRL_COMP_STATUS_HIGH_SUCCESS:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_HIGH_SUCCESS");
			return TRUE;	
		case DIO_CTRL_COMP_STATUS_READY_FOR_SWITCHING:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_READY_FOR_SWITCHING");
			return TRUE;
/////////////////////////		
		case DIO_CTRL_COMP_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_COMP_STATUS_INVALID");
			return FALSE;
	}
}
