#include "NeuralNet2Gui.h"

bool get_neural_net_2_gui_msg_type_string(NeuralNet2GuiMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEURAL_NET_2_GUI_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_START_RECORDING");
			return TRUE;
		case NEURAL_NET_2_GUI_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_STOP_RECORDING");
			return TRUE;
		case NEURAL_NET_2_GUI_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_CANCEL_RECORDING");
			return TRUE;
		case NEURAL_NET_2_GUI_MSG_UPDATE_SYNAPTIC_WEIGHTS:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_UPDATE_SYNAPTIC_WEIGHTS");
			return TRUE;
		case NEURAL_NET_2_GUI_MSG_UPDATE_SYNAPTIC_WEIGHTS_HISTORY:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_UPDATE_SYNAPTIC_WEIGHTS_HISTORY");
			return TRUE;
/////////////////////////		
		case NEURAL_NET_2_GUI_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_GUI_MSG_INVALID");
			return FALSE;
	}
}

NeuralNet2GuiMsg* allocate_neural_net_2_gui_msg_buffer(NeuralNet2GuiMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_neural_net_2_gui_msg_buffer(msg_buffer);
		msg_buffer = allocate_neural_net_2_gui_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(NeuralNet2GuiMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2Gui", "allocate_neural_net_2_gui_msg", "Created neural_net_2_gui_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2GuiMsg* deallocate_neural_net_2_gui_msg_buffer(NeuralNet2GuiMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2GuiMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2Gui", "deallocate_neural_net_2_gui_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_neural_net_2_gui_msg_buffer(NeuralNet2GuiMsg* msg_buffer, TimeStamp msg_time, NeuralNet2GuiMsgType msg_type, NeuralNet2GuiMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuralNet2GuiMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == NEURAL_NET_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2Gui", "write_to_neural_net_2_gui_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neural_net_2_gui_msg_buffer_item(NeuralNet2GuiMsg* msg_buffer, NeuralNet2GuiMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	NeuralNet2GuiMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == NEURAL_NET_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
