#include "ExpCtrlDur2ExpCtrl.h"

bool get_trial_dur_hand_2_exp_ctrl_msg_type_string(ExpCtrlDur2ExpCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_DUR_HAND_2_EXP_CTRL_MSG_TIMEOUT:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_HAND_2_EXP_CTRL_MSG_TIMEOUT");
			return TRUE;	
		case TRIAL_DUR_HAND_2_EXP_CTRL_MSG_EMERGENCY_EXIT:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_HAND_2_EXP_CTRL_MSG_EMERGENCY_EXIT");
			return TRUE;	
/////////////////////////		
		case TRIAL_DUR_HAND_2_EXP_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_DUR_HAND_2_EXP_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_DUR_HAND_2_EXP_CTRL_MSG_INVALID");
			return FALSE;
	}
}

ExpCtrlDur2ExpCtrlMsg* allocate_trial_dur_hand_2_exp_ctrl_msg_buffer(ExpCtrlDur2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_dur_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_dur_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpCtrlDur2ExpCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrlDur2ExpCtrl", "allocate_trial_dur_hand_2_exp_ctrl_msg_buffer", "Created trial_dur_hand_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrlDur2ExpCtrlMsg* deallocate_trial_dur_hand_2_exp_ctrl_msg_buffer(ExpCtrlDur2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrlDur2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrlDur2ExpCtrl", "deallocate_trial_dur_hand_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_trial_dur_hand_2_exp_ctrl_msg_buffer(ExpCtrlDur2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, ExpCtrlDur2ExpCtrlMsgType msg_type, ExpCtrlDur2ExpCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpCtrlDur2ExpCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_DUR_HAND_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrlDur2ExpCtrl", "write_to_trial_dur_hand_2_exp_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_dur_hand_2_exp_ctrl_msg_buffer_item(ExpCtrlDur2ExpCtrlMsg* msg_buffer, ExpCtrlDur2ExpCtrlMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	ExpCtrlDur2ExpCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == TRIAL_DUR_HAND_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
