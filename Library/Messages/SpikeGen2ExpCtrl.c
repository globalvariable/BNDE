#include "SpikeGen2ExpCtrl.h"

bool get_spike_gen_2_exp_ctrl_msg_type_string(SpikeGen2ExpCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case SPIKE_GEN_2_EXP_CTRL_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "SPIKE_GEN_2_EXP_CTRL_MSG_I_AM_ALIVE");
			return TRUE;
/////////////////////////		
		case SPIKE_GEN_2_EXP_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "SPIKE_GEN_2_EXP_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "SPIKE_GEN_2_EXP_CTRL_MSG_INVALID");
			return FALSE;
	}

}

SpikeGen2ExpCtrlMsg* allocate_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_spike_gen_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_spike_gen_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(SpikeGen2ExpCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "SpikeGen2ExpCtrl", "allocate_spike_gen_2_exp_ctrl_msg_buffer", "Created spike_gen_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
SpikeGen2ExpCtrlMsg* deallocate_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (SpikeGen2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "SpikeGen2ExpCtrl", "deallocate_spike_gen_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


SpikeGen2ExpCtrlMsg* allocate_shm_server_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_spike_gen_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_spike_gen_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_SPIKE_GEN_2_EXP_CTRL, sizeof(SpikeGen2ExpCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "SpikeGen2ExpCtrl", "allocate_shm_server_spike_gen_2_exp_ctrl_msg_buffer", "Created shm_server_spike_gen_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
SpikeGen2ExpCtrlMsg* allocate_shm_client_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_spike_gen_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_spike_gen_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_SPIKE_GEN_2_EXP_CTRL, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "SpikeGen2ExpCtrl", "allocate_shm_client_spike_gen_2_exp_ctrl_msg_buffer", "Created shm_client_spike_gen_2_exp_ctrl_msg_buffer.");
	return msg_buffer;
}
SpikeGen2ExpCtrlMsg* deallocate_shm_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (SpikeGen2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "SpikeGen2ExpCtrl", "deallocate_shm_spike_gen_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_SPIKE_GEN_2_EXP_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, SpikeGen2ExpCtrlMsgType msg_type,  SpikeGen2ExpCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	SpikeGen2ExpCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == SPIKE_GEN_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "SpikeGen2ExpCtrl", "write_to_spike_gen_2_exp_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_spike_gen_2_exp_ctrl_msg_buffer_item(SpikeGen2ExpCtrlMsg* msg_buffer, SpikeGen2ExpCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	SpikeGen2ExpCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == SPIKE_GEN_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
