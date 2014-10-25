#include "ProstheticCtrlDurHand2ProstheticCtrl.h"

bool get_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_type_string(ProstheticCtrlDurHand2ProstheticCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_TIMEOUT");
			return TRUE;
/////////////////////////		
		case PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_INVALID");
			return FALSE;
	}
}

ProstheticCtrlDurHand2ProstheticCtrlMsg* allocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ProstheticCtrlDurHand2ProstheticCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrlDurHand2ProstheticCtrl", "allocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer", "Created prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrlDurHand2ProstheticCtrlMsg* deallocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ProstheticCtrlDurHand2ProstheticCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrlDurHand2ProstheticCtrl", "deallocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrlDurHand2ProstheticCtrlMsgType msg_type, ProstheticCtrlDurHand2ProstheticCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ProstheticCtrlDurHand2ProstheticCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrlDurHand2ProstheticCtrl", "write_to_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer_item(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer, ProstheticCtrlDurHand2ProstheticCtrlMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	ProstheticCtrlDurHand2ProstheticCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
