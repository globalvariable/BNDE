#include "DioCtrl2Gui.h"

bool get_dio_ctrl_2_gui_msg_type_string(DioCtrl2GuiMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case DIO_CTRL_2_GUI_MSG_START_RECORDING:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_2_GUI_MSG_START_RECORDING");
			return TRUE;	
		case DIO_CTRL_2_GUI_MSG_STOP_RECORDING:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_2_GUI_MSG_STOP_RECORDING");
			return TRUE;	
		case DIO_CTRL_2_GUI_MSG_CANCEL_RECORDING:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_2_GUI_MSG_CANCEL_RECORDING");
			return TRUE;	
/////////////////////////		
		case DIO_CTRL_2_GUI_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_GUI_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "DIO_CTRL_2_GUI_MSG_INVALID");
			return FALSE;
	}
}

DioCtrl2GuiMsg* allocate_dio_ctrl_2_gui_msg_buffer(DioCtrl2GuiMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_dio_ctrl_2_gui_msg_buffer(msg_buffer);
		msg_buffer = allocate_dio_ctrl_2_gui_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(DioCtrl2GuiMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrl2Gui", "allocate_dio_ctrl_2_gui_msg", "Created dio_ctrl_2_gui_msg_buffer.");
	return msg_buffer;	
}
DioCtrl2GuiMsg* deallocate_dio_ctrl_2_gui_msg_buffer(DioCtrl2GuiMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (DioCtrl2GuiMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2Gui", "deallocate_dio_ctrl_2_gui_msg", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_dio_ctrl_2_gui_msg_buffer(DioCtrl2GuiMsg* msg_buffer, TimeStamp msg_time, DioCtrl2GuiMsgType msg_type, DioCtrl2GuiMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	DioCtrl2GuiMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == DIO_CTRL_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrl2Gui", "write_to_dio_ctrl_2_gui_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_dio_ctrl_2_gui_msg_buffer_item(DioCtrl2GuiMsg* msg_buffer, DioCtrl2GuiMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	DioCtrl2GuiMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == DIO_CTRL_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
