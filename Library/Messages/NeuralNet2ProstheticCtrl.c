#include "NeuralNet2ProstheticCtrl.h"

bool get_neural_net_2_prosthetic_ctrl_msg_type_string(NeuralNet2ProstheticCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEURAL_NET_2_PROSTHETIC_CTRL_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_PROSTHETIC_CTRL_MSG_I_AM_ALIVE");
			return TRUE;
		case NEURAL_NET_2_PROSTHETIC_CTRL_MSG_SPIKE_OUTPUT:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_PROSTHETIC_CTRL_MSG_SPIKE_OUTPUT");
			return TRUE;
/////////////////////////		
		case NEURAL_NET_2_PROSTHETIC_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_PROSTHETIC_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_PROSTHETIC_CTRL_MSG_INVALID");
			return FALSE;
	}

}

NeuralNet2ProstheticCtrlMsg* allocate_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(NeuralNet2ProstheticCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_neural_net_2_prosthetic_ctrl_msg_buffer", "Created neural_net_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2ProstheticCtrlMsg* deallocate_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2ProstheticCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "deallocate_neural_net_2_prosthetic_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


NeuralNet2ProstheticCtrlMsg* allocate_shm_server_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_NEURAL_NET_2_PROSTHETIC_CTRL, sizeof(NeuralNet2ProstheticCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_server_neural_net_2_prosthetic_ctrl_msg_buffer", "Created shm_server_neural_net_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2ProstheticCtrlMsg* allocate_shm_client_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
{
	if (event_scheduling_delay < HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
		return (NeuralNet2ProstheticCtrlMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_client_neural_net_2_prosthetic_ctrl_msg_buffer", "event_scheduling_delay < MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY."); 
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffer, event_scheduling_delay, HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_NEURAL_NET_2_PROSTHETIC_CTRL, 0);
	msg_buffer->event_scheduling_delay = event_scheduling_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_client_neural_net_2_prosthetic_ctrl_msg_buffer", "Created shm_client_neural_net_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;
}
NeuralNet2ProstheticCtrlMsg* deallocate_shm_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2ProstheticCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "deallocate_shm_neural_net_2_prosthetic_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_NEURAL_NET_2_PROSTHETIC_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, NeuralNet2ProstheticCtrlMsgType msg_type, unsigned int layer_num, unsigned int nrn_grp_num, unsigned int neuron_num, TimeStamp spike_time)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuralNet2ProstheticCtrlMsgItem *buff = msg_buffer->buff;

	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].layer_num = layer_num;
	buff[*idx].nrn_grp_num = nrn_grp_num;
	buff[*idx].neuron_num = neuron_num;
	buff[*idx].spike_time = spike_time + msg_buffer->event_scheduling_delay; 
	if ((*idx + 1) == NEURAL_NET_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "write_to_neural_net_2_prosthetic_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neural_net_2_prosthetic_ctrl_msg_buffer_item(NeuralNet2ProstheticCtrlMsg* msg_buffer, NeuralNet2ProstheticCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	NeuralNet2ProstheticCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->layer_num = buff_item->layer_num;	
	msg_item->nrn_grp_num = buff_item->nrn_grp_num;	
	msg_item->neuron_num = buff_item->neuron_num;	
	msg_item->spike_time = buff_item->spike_time;	
	if ((*idx + 1) == NEURAL_NET_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}


NeuralNet2ProstheticCtrlMsg** allocate_shm_server_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(NeuralNet2ProstheticCtrlMsg** msg_buffers, unsigned int num_of_threads)
{
	unsigned int i;

	if (msg_buffers != NULL)
	{
		msg_buffers = deallocate_shm_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(msg_buffers, num_of_threads);
		msg_buffers = allocate_shm_server_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(msg_buffers, num_of_threads);
		return msg_buffers;
	}
	msg_buffers = g_new0(NeuralNet2ProstheticCtrlMsg*, num_of_threads);  
	for (i = 0; i < num_of_threads; i++)
	{
		msg_buffers[i] = rtai_malloc(SHM_NUM_NEURAL_NET_2_PROSTHETIC_CTRL+i, sizeof(NeuralNet2ProstheticCtrlMsg));
//		memset((*msg_buffers)[i], 0, sizeof(NeuralNet2ProstheticCtrlMsg));  // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
		msg_buffers[i]->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
		msg_buffers[i]->buff_read_idx = 0;  // instead of memset, clear buffer pointers.		
	}
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_server_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer", "Created shm_server_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer.");
	return msg_buffers;
}

NeuralNet2ProstheticCtrlMsg* allocate_shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer_item(NeuralNet2ProstheticCtrlMsg** msg_buffers, unsigned int msg_buffer_num, TimeStamp event_scheduling_delay,  TimeStamp HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
{
	if (event_scheduling_delay < HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
		return (NeuralNet2ProstheticCtrlMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer_item", "event_scheduling_delay < MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY."); 
	msg_buffers[msg_buffer_num]  = rtai_malloc(SHM_NUM_NEURAL_NET_2_PROSTHETIC_CTRL+msg_buffer_num, 0);
	if (msg_buffers[msg_buffer_num] == NULL)
		return (NeuralNet2ProstheticCtrlMsg*) print_message(ERROR_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer", "First allocate_shm_SERVER_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer_item via running Mov Obj Handler.");
	msg_buffers[msg_buffer_num]->event_scheduling_delay = event_scheduling_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "allocate_shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer", "Created shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer_item.");
	return msg_buffers[msg_buffer_num] ;
}


NeuralNet2ProstheticCtrlMsg** deallocate_shm_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(NeuralNet2ProstheticCtrlMsg** msg_buffers,  unsigned int num_of_threads)
{
	unsigned int i;
	if (msg_buffers == NULL)
		return (NeuralNet2ProstheticCtrlMsg**)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2ProstheticCtrl", "deallocate_shm_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer", "msg_buffers == NULL.");
	for (i = 0; i < num_of_threads; i++)
	{
		msg_buffers[i] = deallocate_shm_neural_net_2_prosthetic_ctrl_msg_buffer(msg_buffers[i]);
	}
	g_free(msg_buffers);	
	return NULL;
}

