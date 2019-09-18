#include "ProstheticCtrl2Gui.h"

bool get_prosthetic_ctrl_2_gui_msg_type_string(ProstheticCtrl2GuiMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING");
			return TRUE;
		case PROSTHETIC_CTRL_2_GUI_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_GUI_MSG_STOP_RECORDING");
			return TRUE;
		case PROSTHETIC_CTRL_2_GUI_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_GUI_MSG_CANCEL_RECORDING");
			return TRUE;
		case PROSTHETIC_CTRL_2_GUI_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_GUI_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED");
			return TRUE;
/////////////////////////		
		case PROSTHETIC_CTRL_2_GUI_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_GUI_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "PROSTHETIC_CTRL_2_GUI_MSG_INVALID");
			return FALSE;
	}
}

ProstheticCtrl2GuiMsg* allocate_prosthetic_ctrl_2_gui_msg_buffer(ProstheticCtrl2GuiMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_prosthetic_ctrl_2_gui_msg_buffer(msg_buffer);
		msg_buffer = allocate_prosthetic_ctrl_2_gui_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ProstheticCtrl2GuiMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrl2Gui", "allocate_prosthetic_ctrl_2_gui_msg", "Created prosthetic_ctrl_2_gui_msg_buffer.");
	return msg_buffer;	
}
ProstheticCtrl2GuiMsg* deallocate_prosthetic_ctrl_2_gui_msg_buffer(ProstheticCtrl2GuiMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ProstheticCtrl2GuiMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2Gui", "deallocate_prosthetic_ctrl_2_gui_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_prosthetic_ctrl_2_gui_msg_buffer(ProstheticCtrl2GuiMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2GuiMsgType msg_type, ProstheticCtrl2GuiMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ProstheticCtrl2GuiMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == PROSTHETIC_CTRL_2_GUI_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrl2Gui", "write_to_prosthetic_ctrl_2_gui_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_prosthetic_ctrl_2_gui_msg_buffer_item(ProstheticCtrl2GuiMsg* msg_buffer, ProstheticCtrl2GuiMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	ProstheticCtrl2GuiMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == PROSTHETIC_CTRL_2_GUI_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
