#include "NeuRecHand2ExpCtrl.h"


bool get_neu_rec_hand_2_exp_ctrl_msg_type_string(NeuRecHand2ExpCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEU_REC_HAND_2_EXP_CTRL_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "NEU_REC_HAND_2_EXP_CTRL_MSG_I_AM_ALIVE");
			return TRUE;
/////////////////////////		
		case NEU_REC_HAND_2_EXP_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "NEU_REC_HAND_2_EXP_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "NEU_REC_HAND_2_EXP_CTRL_MSG_INVALID");
			return FALSE;
	}

}


NeuRecHand2ExpCtrlMsg* allocate_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_neu_rec_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_neu_rec_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(NeuRecHand2ExpCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuRecHand2ExpCtrl", "allocate_neu_rec_hand_2_exp_ctrl_msg_buffer", "Created neu_rec_hand_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
NeuRecHand2ExpCtrlMsg* deallocate_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuRecHand2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuRecHand2ExpCtrl", "deallocate_neu_rec_hand_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

NeuRecHand2ExpCtrlMsg* allocate_shm_server_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neu_rec_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_neu_rec_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_NEU_REC_HAND_2_EXP_CTRL, sizeof(NeuRecHand2ExpCtrlMsg));
//	memset(msg_buffer, 0, sizeof(ProstheticCtrl2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuRecHand2ExpCtrl", "allocate_shm_server_neu_rec_hand_2_exp_ctrl_msg_buffer", "Created shm_server_neu_rec_hand_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
NeuRecHand2ExpCtrlMsg* allocate_shm_client_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neu_rec_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_neu_rec_hand_2_exp_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_NEU_REC_HAND_2_EXP_CTRL, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuRecHand2ExpCtrl", "allocate_shm_client_neu_rec_hand_2_exp_ctrl_msg_buffer", "Created shm_client_neu_rec_hand_2_exp_ctrl_msg_buffer.");
	return msg_buffer;	
}
NeuRecHand2ExpCtrlMsg* deallocate_shm_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuRecHand2ExpCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuRecHand2ExpCtrl", "deallocate_shm_neu_rec_hand_2_exp_ctrl_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_NEU_REC_HAND_2_EXP_CTRL, msg_buffer);	
	return NULL;
}
bool write_to_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, NeuRecHand2ExpCtrlMsgType msg_type, NeuRecHand2ExpCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuRecHand2ExpCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == NEU_REC_HAND_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuRecHand2ExpCtrl", "write_to_neu_rec_hand_2_exp_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neu_rec_hand_2_exp_ctrl_msg_buffer_item(NeuRecHand2ExpCtrlMsg* msg_buffer, NeuRecHand2ExpCtrlMsgItem *msg_item)
{
	unsigned int *idx;
	NeuRecHand2ExpCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == NEU_REC_HAND_2_EXP_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
