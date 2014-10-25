#include "DioCtrlDurStatus.h"


bool get_dio_ctrl_dur_status_type_string(DioCtrlDurationStatus dio_ctrl_dur_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (dio_ctrl_dur_status_type)
	{
		case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON");
			return TRUE;
		case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF");
			return TRUE;
		case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON");
			return TRUE;
		case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF");
			return TRUE;
		case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON");
			return TRUE;
		case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case DIO_CTRL_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_DUR_STATUS_INVALID");
			return FALSE;
	}
}

