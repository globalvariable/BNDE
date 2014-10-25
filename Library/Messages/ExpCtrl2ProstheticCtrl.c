#include "ExpCtrl2ProstheticCtrl.h"


bool get_exp_ctrl_2_prosthetic_ctrl_msg_type_string(ExpCtrl2ProstheticCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_TRIAL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_TRIAL");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIAL_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIAL_TIMEOUT");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_TRIAL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_TRIAL");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ELLIPSOID_THRESHOLD:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ELLIPSOID_THRESHOLD");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_ENABLED:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_ENABLED");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_DISABLED:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_DISABLED");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_RECORDING");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STOP_RECORDING");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CANCEL_RECORDING");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_LEVER_PRESS_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_LEVER_PRESS_TIMEOUT");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_BY_NOSE_RETRACT:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_BY_NOSE_RETRACT");
			return TRUE;
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CHANGE_TARGET:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CHANGE_TARGET");
			return TRUE;
/////////////////////////		
		case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_PROSTHETIC_CTRL_MSG_INVALID");
			return FALSE;
	}
}


ExpCtrl2ProstheticCtrlMsg* allocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpCtrl2ProstheticCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "allocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "Created exp_ctrl_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2ProstheticCtrlMsg* deallocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2ProstheticCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "deallocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

ExpCtrl2ProstheticCtrlMsg* allocate_shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_EXP_CTRL_2_PROSTHETIC_CTRL, sizeof(ExpCtrl2ProstheticCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "allocate_shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "Created shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2ProstheticCtrlMsg* allocate_shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_EXP_CTRL_2_PROSTHETIC_CTRL, 0);
	if (msg_buffer == NULL)
		print_message(ERROR_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "allocate_shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "Could not create shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer.");		
	else
		print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "allocate_shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "Created shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2ProstheticCtrlMsg* deallocate_shm_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2ProstheticCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "deallocate_shm_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_EXP_CTRL_2_PROSTHETIC_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2ProstheticCtrlMsgType msg_type, ExpCtrl2ProstheticCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpCtrl2ProstheticCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_CTRL_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2ProstheticCtrl", "write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_ctrl_2_prosthetic_ctrl_msg_buffer_item(ExpCtrl2ProstheticCtrlMsg* msg_buffer, ExpCtrl2ProstheticCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	ExpCtrl2ProstheticCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == EXP_CTRL_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
