#include "ExpCtrl2NeuralNet.h"


bool get_exp_ctrl_2_neural_net_msg_type_string(ExpCtrl2NeuralNetMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_START:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_START");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_REWARD_GIVEN:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_REWARD_GIVEN");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_PUNISHMENT_GIVEN:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_PUNISHMENT_GIVEN");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_START_RECORDING");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_STOP_RECORDING");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_CANCEL_RECORDING");
			return TRUE;
		case EXP_CTRL_2_NEURAL_NET_MSG_END_TRIAL_WITH_NOTHING:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_END_TRIAL_WITH_NOTHING");
			return TRUE;
/////////////////////////		
		case EXP_CTRL_2_NEURAL_NET_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_CTRL_2_NEURAL_NET_MSG_INVALID");
			return FALSE;
	}

}


ExpCtrl2NeuralNetMsg* allocate_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_ctrl_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_ctrl_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpCtrl2NeuralNetMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2NeuralNet", "allocate_exp_ctrl_2_neural_net_msg_buffer", "Created exp_ctrl_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2NeuralNetMsg* deallocate_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2NeuralNetMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2NeuralNet", "deallocate_exp_ctrl_2_neural_net_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

ExpCtrl2NeuralNetMsg* allocate_shm_server_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_ctrl_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_ctrl_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_EXP_CTRL_2_NEURAL_NET, sizeof(ExpCtrl2NeuralNetMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2NeuralNet", "allocate_shm_server_exp_ctrl_2_neural_net_msg_buffer", "Created shm_server_exp_ctrl_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2NeuralNetMsg* allocate_shm_client_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_ctrl_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_ctrl_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_EXP_CTRL_2_NEURAL_NET, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpCtrl2NeuralNet", "allocate_shm_client_exp_ctrl_2_neural_net_msg_buffer", "Created shm_client_exp_ctrl_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
ExpCtrl2NeuralNetMsg* deallocate_shm_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpCtrl2NeuralNetMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2NeuralNet", "deallocate_shm_exp_ctrl_2_neural_net_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_EXP_CTRL_2_NEURAL_NET, msg_buffer);	
	return NULL;
}
bool write_to_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2NeuralNetMsgType msg_type, ExpCtrl2NeuralNetMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpCtrl2NeuralNetMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_CTRL_2_NEURAL_NET_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpCtrl2NeuralNet", "write_to_exp_ctrl_2_neural_net_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_ctrl_2_neural_net_msg_buffer_item(ExpCtrl2NeuralNetMsg* msg_buffer, ExpCtrl2NeuralNetMsgItem *msg_item)
{
	unsigned int *idx;
	ExpCtrl2NeuralNetMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == EXP_CTRL_2_NEURAL_NET_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
