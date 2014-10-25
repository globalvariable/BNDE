#include "ExpCtrl2DioCtrl.h"


bool get_exp_ctrl_2_dio_ctrl_msg_type_string(ExpCtrl2DioCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_CTRL_2_DIO_CTRL_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_REWARD:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_REWARD");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_PUNISHMENT:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_PUNISHMENT");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_START_RECORDING");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_STOP_RECORDING");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_CANCEL_RECORDING");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_NO_STATUS_RESET:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_NO_STATUS_RESET");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_STATUS_RESET:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_STATUS_RESET");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_INPUT_COMPONENTS:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_INPUT_COMPONENTS");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_GET_READY_TO_TRIAL_START:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_GET_READY_TO_TRIAL_START");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_LEVERS:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_LEVERS");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_LEVERS_W_STATUS_RESET:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_LEVERS_W_STATUS_RESET");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE_RETRACT:	
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE_RETRACT");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_NOSE_POKE_RETRACT:	
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_NOSE_POKE_RETRACT");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_INVALID_START_TRIAL_REQUEST:	
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_INVALID_START_TRIAL_REQUEST");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL_AVAILABLE:	
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL_AVAILABLE");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_CUE_LED_ON:	
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_CUE_LED_ON");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL_WHEN_GET_READY:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL_WHEN_GET_READY");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_TURN_BUZZER_OFF:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_TURN_BUZZER_OFF");
			return TRUE;
		case EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE");
			return TRUE;
/////////////////////////		
		case EXP_CTRL_2_DIO_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_DIO_CTRL_MSG_INVALID");
			return FALSE;
	}
}


ExpCtrl2DioCtrlMsg* allocate_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_ctrl_2_dio_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_ctrl_2_dio_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpCtrl2DioCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "allocate_exp_ctrl_2_dio_ctrl_msg_buffer", "Created exp_ctrl_2_dio_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2DioCtrlMsg* deallocate_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2DioCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "deallocate_exp_ctrl_2_dio_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

ExpCtrl2DioCtrlMsg* allocate_shm_server_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_ctrl_2_dio_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_ctrl_2_dio_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_EXP_CTRL_2_DIO_CTRL, sizeof(ExpCtrl2DioCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "allocate_shm_server_exp_ctrl_2_dio_ctrl_msg_buffer", "Created shm_server_exp_ctrl_2_dio_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2DioCtrlMsg* allocate_shm_client_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_ctrl_2_dio_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_ctrl_2_dio_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_EXP_CTRL_2_DIO_CTRL, 0);
	if (msg_buffer == NULL)
		print_message(ERROR_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "allocate_shm_client_exp_ctrl_2_dio_ctrl_msg_buffer", "Could not create shm_client_exp_ctrl_2_dio_ctrl_msg_buffer.");		
	else
		print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "allocate_shm_client_exp_ctrl_2_dio_ctrl_msg_buffer", "Created shm_client_exp_ctrl_2_dio_ctrl_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2DioCtrlMsg* deallocate_shm_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2DioCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "deallocate_shm_exp_ctrl_2_dio_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_EXP_CTRL_2_DIO_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2DioCtrlMsgType msg_type, ExpCtrl2DioCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpCtrl2DioCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_CTRL_2_DIO_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2DioCtrl", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_ctrl_2_dio_ctrl_msg_buffer_item(ExpCtrl2DioCtrlMsg* msg_buffer, ExpCtrl2DioCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	ExpCtrl2DioCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == EXP_CTRL_2_DIO_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
