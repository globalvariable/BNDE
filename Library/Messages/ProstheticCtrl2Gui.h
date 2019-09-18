#ifndef PROSTHETIC_CTRL_2_GUI_H
#define PROSTHETIC_CTRL_2_GUI_H

//  MESSAGES FROM MOV OBJ HANDLER TO MOV OBJ HANDLER GUI

typedef struct __ProstheticCtrl2GuiMsg ProstheticCtrl2GuiMsg;
typedef struct __ProstheticCtrl2GuiMsgItem ProstheticCtrl2GuiMsgItem;
typedef unsigned int ProstheticCtrl2GuiMsgType;
typedef unsigned int ProstheticCtrl2GuiMsgAdditional;


#define PROSTHETIC_CTRL_2_GUI_MSG_STRING_LENGTH		50

#define PROSTHETIC_CTRL_2_GUI_MSG_NULL					0
#define PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING	1
#define PROSTHETIC_CTRL_2_GUI_MSG_STOP_RECORDING		2
#define PROSTHETIC_CTRL_2_GUI_MSG_CANCEL_RECORDING	3
#define PROSTHETIC_CTRL_2_GUI_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED 4

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../ProstheticCtrlData/ProstheticCtrlComponentTypes.h"
#include "../Misc/Misc.h"

struct __ProstheticCtrl2GuiMsgItem
{
	TimeStamp 						msg_time;		
	ProstheticCtrl2GuiMsgType			msg_type;
	ProstheticCtrl2GuiMsgAdditional		additional_data;
};

struct __ProstheticCtrl2GuiMsg		// Requests to ExpControllers
{
	ProstheticCtrl2GuiMsgItem		buff[PROSTHETIC_CTRL_2_GUI_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

ProstheticCtrl2GuiMsg* allocate_prosthetic_ctrl_2_gui_msg_buffer(ProstheticCtrl2GuiMsg* msg_buffer);
ProstheticCtrl2GuiMsg* deallocate_prosthetic_ctrl_2_gui_msg_buffer(ProstheticCtrl2GuiMsg* msg_buffer);
bool get_prosthetic_ctrl_2_gui_msg_type_string(ProstheticCtrl2GuiMsgType msg_type, char *str);
bool write_to_prosthetic_ctrl_2_gui_msg_buffer(ProstheticCtrl2GuiMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2GuiMsgType msg_type, ProstheticCtrl2GuiMsgAdditional additional_data);
bool get_next_prosthetic_ctrl_2_gui_msg_buffer_item(ProstheticCtrl2GuiMsg* msg_buffer, ProstheticCtrl2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses




#endif
