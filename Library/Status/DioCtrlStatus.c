#include "DioCtrlStatus.h"


bool get_dio_ctrl_status_type_string(DioCtrlStatus dio_ctrl_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (dio_ctrl_status_type)
	{
		case DIO_CTRL_STATUS_COMPONENTS_UNAVAILABLE:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_STATUS_COMPONENTS_UNAVAILABLE");
			return TRUE;
		case DIO_CTRL_STATUS_COMPONENTS_AVAILABLE:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_STATUS_COMPONENTS_AVAILABLE");
			return TRUE;
/////////////////////////		
		case DIO_CTRL_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_STATUS_INVALID");
			return FALSE;
	}
}
