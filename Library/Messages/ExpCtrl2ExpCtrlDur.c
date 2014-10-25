#include "ExpCtrl2ExpCtrlDur.h"

bool get_exp_ctrl_2_trial_dur_hand_msg_type_string(ExpCtrl2ExpCtrlDurMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING:
			if (str != NULL)
				strcpy(str, "EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING");
			return TRUE;	
		case EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING:
			if (str != NULL)
				strcpy(str, "EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING");
			return TRUE;	
/////////////////////////		
		case EXP_CTRL_2_TRIAL_DUR_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_TRIAL_DUR_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_TRIAL_DUR_HAND_MSG_INVALID");
			return FALSE;
	}
}

ExpCtrl2ExpCtrlDurMsg* allocate_exp_ctrl_2_trial_dur_hand_msg_buffer(ExpCtrl2ExpCtrlDurMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_ctrl_2_trial_dur_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_ctrl_2_trial_dur_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpCtrl2ExpCtrlDurMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2ExpCtrlDur", "allocate_exp_ctrl_2_trial_dur_hand_msg_buffer", "Created exp_ctrl_2_trial_dur_hand_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2ExpCtrlDurMsg* deallocate_exp_ctrl_2_trial_dur_hand_msg_buffer(ExpCtrl2ExpCtrlDurMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2ExpCtrlDurMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2ExpCtrlDur", "deallocate_exp_ctrl_2_trial_dur_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(ExpCtrl2ExpCtrlDurMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2ExpCtrlDurMsgType msg_type, ExpCtrl2ExpCtrlDurMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpCtrl2ExpCtrlDurMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_CTRL_2_TRIAL_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2ExpCtrlDur", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_ctrl_2_trial_dur_hand_msg_buffer_item(ExpCtrl2ExpCtrlDurMsg* msg_buffer, ExpCtrl2ExpCtrlDurMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	ExpCtrl2ExpCtrlDurMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == EXP_CTRL_2_TRIAL_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
