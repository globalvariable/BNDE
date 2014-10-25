#ifndef NEURAL_NET_2_GUI_H
#define NEURAL_NET_2_GUI_H

//  MESSAGES FROM NEURAL NET TO NEURAL NET GUI

typedef struct __NeuralNet2GuiMsg NeuralNet2GuiMsg;
typedef struct __NeuralNet2GuiMsgItem NeuralNet2GuiMsgItem;
typedef unsigned int NeuralNet2GuiMsgType;

typedef union 
{
	unsigned int recording_number;
	double reward;
} NeuralNet2GuiMsgAdditional;


#define NEURAL_NET_2_GUI_MSG_STRING_LENGTH		100

#define NEURAL_NET_2_GUI_MSG_NULL									0
#define NEURAL_NET_2_GUI_MSG_START_RECORDING						1
#define NEURAL_NET_2_GUI_MSG_STOP_RECORDING						2
#define NEURAL_NET_2_GUI_MSG_CANCEL_RECORDING						3
#define NEURAL_NET_2_GUI_MSG_UPDATE_SYNAPTIC_WEIGHTS				4
#define NEURAL_NET_2_GUI_MSG_UPDATE_SYNAPTIC_WEIGHTS_HISTORY	5

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __NeuralNet2GuiMsgItem
{
	TimeStamp 						msg_time;		
	NeuralNet2GuiMsgType			msg_type;
	NeuralNet2GuiMsgAdditional		additional_data;
};

struct __NeuralNet2GuiMsg		// Requests to ExpControllers
{
	NeuralNet2GuiMsgItem		buff[NEURAL_NET_2_GUI_MSG_BUFF_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

NeuralNet2GuiMsg* allocate_neural_net_2_gui_msg_buffer(NeuralNet2GuiMsg* msg_buffer);
NeuralNet2GuiMsg* deallocate_neural_net_2_gui_msg_buffer(NeuralNet2GuiMsg* msg_buffer);
bool get_neural_net_2_gui_msg_type_string(NeuralNet2GuiMsgType msg_type, char *str);
bool write_to_neural_net_2_gui_msg_buffer(NeuralNet2GuiMsg* msg_buffer, TimeStamp msg_time, NeuralNet2GuiMsgType msg_type, NeuralNet2GuiMsgAdditional additional_data);
bool get_next_neural_net_2_gui_msg_buffer_item(NeuralNet2GuiMsg* msg_buffer, NeuralNet2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses




#endif
