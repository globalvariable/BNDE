#include "ProstheticCtrl2NeuralNet.h"


bool get_prosthetic_ctrl_2_neural_net_msg_type_string(ProstheticCtrl2NeuralNetMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_3_DOF_JOINT_ANGLE:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_3_DOF_JOINT_ANGLE");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_REINFORCEMENT:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_REINFORCEMENT");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_END_TRIAL_W_REWARD:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_END_TRIAL_W_REWARD");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_END_TRIAL_W_PUNISH:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_END_TRIAL_W_PUNISH");
			return TRUE;
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_START_TRIAL:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_START_TRIAL");
			return TRUE;
/////////////////////////		
		case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_NEURAL_NET_MSG_INVALID");
			return FALSE;
	}

}


ProstheticCtrl2NeuralNetMsg* allocate_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ProstheticCtrl2NeuralNetMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_prosthetic_ctrl_2_neural_net_msg_buffer", "Created prosthetic_ctrl_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2NeuralNetMsg* deallocate_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ProstheticCtrl2NeuralNetMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "deallocate_prosthetic_ctrl_2_neural_net_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

ProstheticCtrl2NeuralNetMsg* allocate_shm_server_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_PROSTHETIC_CTRL_2_NEURAL_NET, sizeof(ProstheticCtrl2NeuralNetMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_server_prosthetic_ctrl_2_neural_net_msg_buffer", "Created shm_server_prosthetic_ctrl_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2NeuralNetMsg* allocate_shm_client_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY) // since client is the writer to the buffer, it shoud schedule events. server does not need to know the event scheduling delay
{
	if (event_scheduling_delay < HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY)
		return (ProstheticCtrl2NeuralNetMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_client_prosthetic_ctrl_2_neural_net_msg_buffer", "event_scheduling_delay < MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY."); 
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_PROSTHETIC_CTRL_2_NEURAL_NET, 0);
	msg_buffer->event_scheduling_delay = event_scheduling_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_client_prosthetic_ctrl_2_neural_net_msg_buffer", "Created shm_client_prosthetic_ctrl_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2NeuralNetMsg* deallocate_shm_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ProstheticCtrl2NeuralNetMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "deallocate_shm_prosthetic_ctrl_2_neural_net_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_PROSTHETIC_CTRL_2_NEURAL_NET, msg_buffer);	
	return NULL;
}
bool write_to_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2NeuralNetMsgType msg_type, ProstheticCtrl2NeuralNetMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ProstheticCtrl2NeuralNetMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].scheduled_time = msg_time + msg_buffer->event_scheduling_delay; 
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == PROSTHETIC_CTRL_2_NEURAL_NET_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "write_to_prosthetic_ctrl_2_neural_net_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_prosthetic_ctrl_2_neural_net_msg_buffer_item(ProstheticCtrl2NeuralNetMsg* msg_buffer, ProstheticCtrl2NeuralNetMsgItem *msg_item)
{
	unsigned int *idx;
	ProstheticCtrl2NeuralNetMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == PROSTHETIC_CTRL_2_NEURAL_NET_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}

ProstheticCtrl2NeuralNetMsg** allocate_shm_server_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(ProstheticCtrl2NeuralNetMsg** msg_buffers, unsigned int num_of_threads)
{
	unsigned int i;
	if (msg_buffers != NULL)
	{
		msg_buffers = deallocate_shm_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(msg_buffers, num_of_threads);
		msg_buffers = allocate_shm_server_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(msg_buffers, num_of_threads);
		return msg_buffers;
	}
	msg_buffers = g_new0(ProstheticCtrl2NeuralNetMsg*, num_of_threads);  
	for (i = 0; i < num_of_threads; i++)
	{
		msg_buffers[i] = rtai_malloc(SHM_NUM_PROSTHETIC_CTRL_2_NEURAL_NET+i, sizeof(ProstheticCtrl2NeuralNetMsg));
//		memset((*msg_buffers)[i], 0, sizeof(ProstheticCtrl2NeuralNetMsg));	 // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
		msg_buffers[i]->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
		msg_buffers[i]->buff_read_idx = 0;  // instead of memset, clear buffer pointers.		
	}
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_server_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer", "Created shm_server_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer.");
	return msg_buffers;
}

ProstheticCtrl2NeuralNetMsg* allocate_shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item(ProstheticCtrl2NeuralNetMsg** msg_buffers, unsigned int msg_buffer_num, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY)
{
	if (event_scheduling_delay < HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY)
		return (ProstheticCtrl2NeuralNetMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item", "event_scheduling_delay < HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY."); 

	msg_buffers[msg_buffer_num]  = rtai_malloc(SHM_NUM_PROSTHETIC_CTRL_2_NEURAL_NET+msg_buffer_num, 0);
	if (msg_buffers[msg_buffer_num] == NULL)
		return (ProstheticCtrl2NeuralNetMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item", "First allocate_shm_SERVER_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item via running Neural Net."); 
	msg_buffers[msg_buffer_num]->event_scheduling_delay = event_scheduling_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "allocate_shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer", "Created shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item.");
	return msg_buffers[msg_buffer_num] ;
}

ProstheticCtrl2NeuralNetMsg** deallocate_shm_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(ProstheticCtrl2NeuralNetMsg** msg_buffers,  unsigned int num_of_threads)
{
	unsigned int i;
	if (msg_buffers == NULL)
		return (ProstheticCtrl2NeuralNetMsg**)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2NeuralNet", "deallocate_shm_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer", "msg_buffers == NULL.");
	for (i = 0; i < num_of_threads; i++)
	{
		msg_buffers[i] = deallocate_shm_prosthetic_ctrl_2_neural_net_msg_buffer(msg_buffers[i]);
	}
	g_free(msg_buffers);	
	return NULL;
}
