#include "DioCtrl2ExpCtrl.h"


bool get_dio_ctrl_2_exp_ctrl_msg_type_string(DioCtrl2ExpCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case DIO_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_START_TRIAL_REQUEST:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_START_TRIAL_REQUEST");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_END_TRIAL_REQUEST:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_END_TRIAL_REQUEST");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_NOSE_POKE_EVENT:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_NOSE_POKE_EVENT");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_NOSE_RETRACT_EVENT:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_NOSE_RETRACT_EVENT");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_RESTRAIN_RELEASE_REQ:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_RESTRAIN_RELEASE_REQ");
			return TRUE;
		case DIO_CTRL_2_EXP_CTRL_MSG_LEVER_RELEASE:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_LEVER_RELEASE");
			return TRUE;
/////////////////////////		
		case DIO_CTRL_2_EXP_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_EXP_CTRL_MSG_INVALID");
			return FALSE;
	}

}


DioCtrl2ExpCtrlMsg* allocate_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_dio_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_dio_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(DioCtrl2ExpCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrl2ExpCtrl", "allocate_dio_ctrl_2_exp_ctrl_msg_buffer", "Created dio_ctrl_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
DioCtrl2ExpCtrlMsg* deallocate_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (DioCtrl2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2ExpCtrl", "deallocate_dio_ctrl_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

DioCtrl2ExpCtrlMsg* allocate_shm_server_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_dio_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_dio_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_DIO_CTRL_2_EXP_CTRL, sizeof(DioCtrl2ExpCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrl2ExpCtrl", "allocate_shm_server_dio_ctrl_2_exp_ctrl_msg_buffer", "Created shm_server_dio_ctrl_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
DioCtrl2ExpCtrlMsg* allocate_shm_client_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_dio_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_dio_ctrl_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_DIO_CTRL_2_EXP_CTRL, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrl2ExpCtrl", "allocate_shm_client_dio_ctrl_2_exp_ctrl_msg_buffer", "Created shm_client_dio_ctrl_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
DioCtrl2ExpCtrlMsg* deallocate_shm_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (DioCtrl2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2ExpCtrl", "deallocate_shm_dio_ctrl_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_DIO_CTRL_2_EXP_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, DioCtrl2ExpCtrlMsgType msg_type, DioCtrl2ExpCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	DioCtrl2ExpCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == DIO_CTRL_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2ExpCtrl", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_dio_ctrl_2_exp_ctrl_msg_buffer_item(DioCtrl2ExpCtrlMsg* msg_buffer, DioCtrl2ExpCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	DioCtrl2ExpCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == DIO_CTRL_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
