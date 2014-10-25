#include "ExpDurStatus.h"


bool get_trial_dur_status_type_string(ExpDurationStatus trial_dur_status_type, char *str)  // pass NULL if you only want checking (to be faster) 
{
	switch (trial_dur_status_type)
	{
		case TRIAL_DUR_STATUS_HANDLING_ENABLED:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_STATUS_HANDLING_ENABLED");
			return TRUE;		
		case TRIAL_DUR_STATUS_HANDLING_DISABLED:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_STATUS_HANDLING_DISABLED");
			return TRUE;
/////////////////////////		
		case TRIAL_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_STATUS_TYPE_INVALID");
			return FALSE;
	}
}
