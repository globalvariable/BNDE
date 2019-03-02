#include "HandleExpCtrlDur.h"



bool handle_exp_control_duration(ExpDurationStatus *trial_duration_status, TimeStamp current_time, TimeStamp handling_end_time, ExpCtrlDur2ExpCtrlMsg *msgs_trial_dur_hand_2_exp_ctrl)
{
	char str_dur_status[TRIAL_DUR_STATUS_MAX_STRING_LENGTH];
	switch (*trial_duration_status)
	{
		case TRIAL_DUR_STATUS_HANDLING_DISABLED:
			break;	// do nothing
		case TRIAL_DUR_STATUS_HANDLING_ENABLED:
			if (current_time >= handling_end_time)
			{
				*trial_duration_status = TRIAL_DUR_STATUS_HANDLING_DISABLED;	
				if (! write_to_trial_dur_hand_2_exp_ctrl_msg_buffer(msgs_trial_dur_hand_2_exp_ctrl, current_time, TRIAL_DUR_HAND_2_EXP_CTRL_MSG_TIMEOUT, 0))
					return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur", "handle_exp_control_duration", "! write_to_trial_dur_hand_2_exp_ctrl_msg_buffer()."); 
			}	
			break;	// do nothing
		default: 
			get_trial_dur_status_type_string(*trial_duration_status, str_dur_status);  
			return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrlDur", "handle_exp_control_duration", str_dur_status);		
	}
	return TRUE;
}
