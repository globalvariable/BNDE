#include "DioCtrl2DioCtrlDurHand.h"

bool get_dio_ctrl_2_dio_ctrl_dur_hand_msg_type_string(DioCtrl2DioCtrlDurHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER");
			return TRUE;
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER");
			return TRUE;
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER");
			return TRUE;
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER");
			return TRUE;
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER");
			return TRUE;
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER");
			return TRUE;

/////////////////////////		
		case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_INVALID");
			return FALSE;
	}
}

DioCtrl2DioCtrlDurHandMsg* allocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(DioCtrl2DioCtrlDurHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(DioCtrl2DioCtrlDurHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrl2DioCtrlDurHand", "allocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer", "Created dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer.");
	return msg_buffer;	
}
DioCtrl2DioCtrlDurHandMsg* deallocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(DioCtrl2DioCtrlDurHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (DioCtrl2DioCtrlDurHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2DioCtrlDurHand", "deallocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(DioCtrl2DioCtrlDurHandMsg* msg_buffer, TimeStamp msg_time, DioCtrl2DioCtrlDurHandMsgType msg_type, DioCtrlCompNum comp_num, DioCtrl2DioCtrlDurHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	DioCtrl2DioCtrlDurHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].comp_num = comp_num;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2DioCtrlDurHand", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer_item(DioCtrl2DioCtrlDurHandMsg* msg_buffer, DioCtrl2DioCtrlDurHandMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	DioCtrl2DioCtrlDurHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->comp_num = buff_item->comp_num;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
