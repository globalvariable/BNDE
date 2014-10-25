#include "RS232DurStatus.h"


bool get_rs232_dur_status_type_string(RS232DurationStatus rs232_dur_status_type, char *str)  // pass NULL if you only want checking (to be faster) 
{
	switch (rs232_dur_status_type)
	{
		case RS232_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "RS232_DUR_STATUS_TIMER_ON");
			return TRUE;		
		case RS232_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "RS232_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case RS232_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "RS232_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "RS232_DUR_STATUS_INVALID");
			return FALSE;
	}
}
