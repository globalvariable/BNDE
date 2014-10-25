#include "Gui2ProstheticCtrl.h"

bool get_gui_2_prosthetic_ctrl_msg_type_string(Gui2ProstheticCtrlMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case GUI_2_PROSTHETIC_CTRL_MSG_SET_THRESHOLD:
			if (str != NULL)
 				strcpy(str, "GUI_2_PROSTHETIC_CTRL_MSG_SET_THRESHOLD");
			return TRUE;
/////////////////////////		
		case GUI_2_PROSTHETIC_CTRL_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "GUI_2_PROSTHETIC_CTRL_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "GUI_2_PROSTHETIC_CTRL_MSG_INVALID");
			return FALSE;
	}
}

Gui2ProstheticCtrlMsg* allocate_gui_2_prosthetic_ctrl_msg_buffer(Gui2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_gui_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		msg_buffer = allocate_gui_2_prosthetic_ctrl_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(Gui2ProstheticCtrlMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "Gui2ProstheticCtrl", "allocate_gui_2_prosthetic_ctrl_msg", "Created gui_2_prosthetic_ctrl_msg_buffer.");
	return msg_buffer;	
}
Gui2ProstheticCtrlMsg* deallocate_gui_2_prosthetic_ctrl_msg_buffer(Gui2ProstheticCtrlMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (Gui2ProstheticCtrlMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "Gui2ProstheticCtrl", "deallocate_gui_2_prosthetic_ctrl_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_gui_2_prosthetic_ctrl_msg_buffer(Gui2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, Gui2ProstheticCtrlMsgType msg_type, Gui2ProstheticCtrlMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	Gui2ProstheticCtrlMsgItem *item = &(msg_buffer->buff[*idx]);
	item->msg_time = msg_time;
	item->msg_type = msg_type;
	item->additional_data = additional_data;
	if (((*idx) + 1) == GUI_2_PROSTHETIC_CTRL_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "Gui2ProstheticCtrl", "write_to_gui_2_prosthetic_ctrl_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_gui_2_prosthetic_ctrl_msg_buffer_item(Gui2ProstheticCtrlMsg* msg_buffer, Gui2ProstheticCtrlMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	Gui2ProstheticCtrlMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == GUI_2_PROSTHETIC_CTRL_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
