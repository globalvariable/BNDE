#include "HandleExpCtrl2ExpCtrlDurMsgs.h"


bool handle_exp_control_to_trial_dur_handler_msg(ExpDurationStatus *trial_duration_status, TimeStamp current_time, ExpCtrl2ExpCtrlDurMsg *msgs_exp_ctrl_2_trial_dur_hand, TimeStamp *handling_end_time)
{
	ExpCtrl2ExpCtrlDurMsgItem msg_item;
	char str_exp_ctrl_msg[EXP_CTRL_2_TRIAL_DUR_HAND_MSG_STRING_LENGTH];
	char str_dur_status[TRIAL_DUR_STATUS_MAX_STRING_LENGTH];
	while (get_next_exp_ctrl_2_trial_dur_hand_msg_buffer_item(msgs_exp_ctrl_2_trial_dur_hand, &msg_item))
	{
		get_exp_ctrl_2_trial_dur_hand_msg_type_string(msg_item.msg_type, str_exp_ctrl_msg);
//		print_message(INFO_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_exp_ctrl_msg);
		switch (msg_item.msg_type)
		{
			case EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING:	
				switch (*trial_duration_status)
				{
					case TRIAL_DUR_STATUS_HANDLING_ENABLED:
						print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_exp_ctrl_msg);
						get_trial_dur_status_type_string(*trial_duration_status, str_dur_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_dur_status);
					case TRIAL_DUR_STATUS_HANDLING_DISABLED:
						*trial_duration_status = TRIAL_DUR_STATUS_HANDLING_ENABLED;
						*handling_end_time = msg_item.additional_data;
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_exp_ctrl_msg);
						get_trial_dur_status_type_string(*trial_duration_status, str_dur_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_dur_status);
				}
				break;
			case EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING:	
				switch (*trial_duration_status)
				{
					case TRIAL_DUR_STATUS_HANDLING_ENABLED:
						*trial_duration_status = TRIAL_DUR_STATUS_HANDLING_DISABLED;
						break;
					case TRIAL_DUR_STATUS_HANDLING_DISABLED:
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_exp_ctrl_msg);
						get_trial_dur_status_type_string(*trial_duration_status, str_dur_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_dur_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrl2ExpCtrlDurMsgs", "handle_exp_control_to_trial_dur_handler_msg", str_exp_ctrl_msg);
		}
	}
	return TRUE;
}
