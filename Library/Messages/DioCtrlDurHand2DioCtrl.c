#include "DioCtrlDurHand2DioCtrl.h"

bool get_dio_ctrl_dur_hand_2_dio_ctrl_msg_type_string(DioCtrlDurHand2DioCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MIN:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MIN");
			return TRUE;
		case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MAX:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MAX");
			return TRUE;
		case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT");
			return TRUE;
/////////////////////////		
		case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INVALID");
			return FALSE;
	}
}

DioCtrlDurHand2DioCtrlMsg* allocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(DioCtrlDurHand2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(DioCtrlDurHand2DioCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrlDurHand2DioCtrl", "allocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer", "Created dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer.");
	return msg_buffer;	
}
DioCtrlDurHand2DioCtrlMsg* deallocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(DioCtrlDurHand2DioCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (DioCtrlDurHand2DioCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrlDurHand2DioCtrl", "deallocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(DioCtrlDurHand2DioCtrlMsg* msg_buffer, TimeStamp msg_time, DioCtrlDurHand2DioCtrlMsgType msg_type, DioCtrlCompNum comp_num, DioCtrlDurHand2DioCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	DioCtrlDurHand2DioCtrlMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].comp_num = comp_num;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrlDurHand2DioCtrl", "write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer_item(DioCtrlDurHand2DioCtrlMsg* msg_buffer, DioCtrlDurHand2DioCtrlMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	DioCtrlDurHand2DioCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->comp_num = buff_item->comp_num;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
