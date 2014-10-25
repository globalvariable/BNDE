#include "ProstheticCtrl2ExpCtrl.h"


bool get_prosthetic_ctrl_2_exp_ctrl_msg_type_string(ProstheticCtrl2ExpCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_END_TRIAL_REQUEST:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_END_TRIAL_REQUEST");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_INITIAL_DIST_2_TARGET:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_INITIAL_DIST_2_TARGET");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_TARGET:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_TARGET");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_OUT_OF_ROBOT_SPACE:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_OUT_OF_ROBOT_SPACE");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_LEVER_PRESS:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_LEVER_PRESS");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_REWARD_THRES:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_LEVER_PRESS");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_THRESHOLD:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_THRESHOLD");
			return TRUE;
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_THRESHOLD_2:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_THRESHOLD_2");
			return TRUE;
////////////////////////		
		case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_EXP_CTRL_MSG_INVALID");
			return FALSE;
	}
}


ProstheticCtrl2ExpCtrlMsg* allocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ProstheticCtrl2ExpCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2ExpCtrl", "allocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer", "Created prosthetic_ctrl_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2ExpCtrlMsg* deallocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ProstheticCtrl2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2ExpCtrl", "deallocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

ProstheticCtrl2ExpCtrlMsg* allocate_shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_PROSTHETIC_CTRL_2_EXP_CTRL, sizeof(ProstheticCtrl2ExpCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2ExpCtrl", "allocate_shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer", "Created shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2ExpCtrlMsg* allocate_shm_client_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_PROSTHETIC_CTRL_2_EXP_CTRL, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2ExpCtrl", "allocate_shm_client_prosthetic_ctrl_2_exp_ctrl_msg_buffer", "Created shm_client_prosthetic_ctrl_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2ExpCtrlMsg* deallocate_shm_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ProstheticCtrl2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2ExpCtrl", "deallocate_shm_prosthetic_ctrl_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_PROSTHETIC_CTRL_2_EXP_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2ExpCtrlMsgType msg_type, ProstheticCtrl2ExpCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ProstheticCtrl2ExpCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == PROSTHETIC_CTRL_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2ExpCtrl", "write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_prosthetic_ctrl_2_exp_ctrl_msg_buffer_item(ProstheticCtrl2ExpCtrlMsg* msg_buffer, ProstheticCtrl2ExpCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	ProstheticCtrl2ExpCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == PROSTHETIC_CTRL_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
