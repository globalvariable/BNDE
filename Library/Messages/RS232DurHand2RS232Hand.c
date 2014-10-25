#include "RS232DurHand2RS232Hand.h"

bool get_rs232_dur_hand_2_rs232_hand_msg_type_string(RS232DurHand2RS232HandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case RS232_DUR_HAND_2_RS232_HAND_MSG_TX_TIMEOUT:
			if (str != NULL)
				strcpy(str, "RS232_DUR_HAND_2_RS232_HAND_MSG_TX_TIMEOUT");
			return TRUE;	
		case RS232_DUR_HAND_2_RS232_HAND_MSG_RX_TIMEOUT:
			if (str != NULL)
				strcpy(str, "RS232_DUR_HAND_2_RS232_HAND_MSG_RX_TIMEOUT");
			return TRUE;	
		case RS232_DUR_HAND_2_RS232_HAND_MSG_EMERGENCY_EXIT:
			if (str != NULL)
				strcpy(str, "RS232_DUR_HAND_2_RS232_HAND_MSG_EMERGENCY_EXIT");
			return TRUE;	
/////////////////////////		
		case RS232_DUR_HAND_2_RS232_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "RS232_DUR_HAND_2_RS232_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "RS232_DUR_HAND_2_RS232_HAND_MSG_INVALID");
			return FALSE;
	}
}

RS232DurHand2RS232HandMsg* allocate_rs232_dur_hand_2_rs232_hand_msg_buffer(RS232DurHand2RS232HandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_rs232_dur_hand_2_rs232_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_rs232_dur_hand_2_rs232_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(RS232DurHand2RS232HandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "RS232DurHand2RS232Hand", "allocate_rs232_dur_hand_2_rs232_hand_msg_buffer", "Created rs232_dur_hand_2_rs232_hand_msg_buffer.");
	return msg_buffer;	
}
RS232DurHand2RS232HandMsg* deallocate_rs232_dur_hand_2_rs232_hand_msg_buffer(RS232DurHand2RS232HandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (RS232DurHand2RS232HandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "RS232DurHand2RS232Hand", "deallocate_rs232_dur_hand_2_rs232_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_rs232_dur_hand_2_rs232_hand_msg_buffer(RS232DurHand2RS232HandMsg* msg_buffer, TimeStamp msg_time, RS232DurHand2RS232HandMsgType msg_type, unsigned int component_num, RS232DurHand2RS232HandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	RS232DurHand2RS232HandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].component_num = component_num;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == RS232_DUR_HAND_2_RS232_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "RS232DurHand2RS232Hand", "write_to_rs232_dur_hand_2_rs232_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_rs232_dur_hand_2_rs232_hand_msg_buffer_item(RS232DurHand2RS232HandMsg* msg_buffer, RS232DurHand2RS232HandMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	RS232DurHand2RS232HandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->component_num = buff_item->component_num;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == RS232_DUR_HAND_2_RS232_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
