#ifndef GUI_2_PROSTHETIC_CTRL_H
#define GUI_2_PROSTHETIC_CTRL_H

//  MESSAGES FROM MOV OBJ HANDLER GUI TO MOV OBJ HANDLER

typedef struct __Gui2ProstheticCtrlMsg Gui2ProstheticCtrlMsg;
typedef struct __Gui2ProstheticCtrlMsgItem Gui2ProstheticCtrlMsgItem;
typedef unsigned int Gui2ProstheticCtrlMsgType;
typedef double Gui2ProstheticCtrlMsgAdditional;


#define GUI_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH		50

#define GUI_2_PROSTHETIC_CTRL_MSG_NULL					0
#define GUI_2_PROSTHETIC_CTRL_MSG_SET_THRESHOLD		1

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __Gui2ProstheticCtrlMsgItem
{
	TimeStamp 								msg_time;		
	Gui2ProstheticCtrlMsgType					msg_type;
	Gui2ProstheticCtrlMsgAdditional				additional_data;
};

struct __Gui2ProstheticCtrlMsg		// Requests to ExpControllers
{
	Gui2ProstheticCtrlMsgItem		buff[GUI_2_PROSTHETIC_CTRL_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

Gui2ProstheticCtrlMsg* allocate_gui_2_prosthetic_ctrl_msg_buffer(Gui2ProstheticCtrlMsg* msg_buffer);
Gui2ProstheticCtrlMsg* deallocate_gui_2_prosthetic_ctrl_msg_buffer(Gui2ProstheticCtrlMsg* msg_buffer);
bool get_gui_2_prosthetic_ctrl_msg_type_string(Gui2ProstheticCtrlMsgType msg_type, char *str);
bool write_to_gui_2_prosthetic_ctrl_msg_buffer(Gui2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, Gui2ProstheticCtrlMsgType msg_type, Gui2ProstheticCtrlMsgAdditional additional_data);
bool get_next_gui_2_prosthetic_ctrl_msg_buffer_item(Gui2ProstheticCtrlMsg* msg_buffer, Gui2ProstheticCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
