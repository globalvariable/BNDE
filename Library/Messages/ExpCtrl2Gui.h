#ifndef EXP_CTRL_2_GUI_H
#define EXP_CTRL_2_GUI_H

//  MESSAGES FROM TRIAL HANDLER TO TRIAL HANDLER GUI

typedef struct __ExpCtrl2GuiMsg ExpCtrl2GuiMsg;
typedef struct __ExpCtrl2GuiMsgItem ExpCtrl2GuiMsgItem;
typedef unsigned int ExpCtrl2GuiMsgType;
typedef unsigned int ExpCtrl2GuiMsgAdditional;


#define EXP_CTRL_2_GUI_MSG_STRING_LENGTH		60

#define EXP_CTRL_2_GUI_MSG_NULL									0
#define EXP_CTRL_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK			1   // acknowledge
#define EXP_CTRL_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK			2   // acknowledge
#define EXP_CTRL_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK		3   // acknowledge  // sent to cancel current recording
#define EXP_CTRL_2_GUI_MSG_TRIAL_STATUS_CHANGE				4

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ExpCtrl2GuiMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2GuiMsgType						msg_type;
	ExpCtrl2GuiMsgAdditional					additional_data;
};

struct __ExpCtrl2GuiMsg		// Requests to ExpControllers
{
	ExpCtrl2GuiMsgItem		buff[EXP_CTRL_2_GUI_MSG_BUFF_SIZE];
	unsigned int				buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int				buff_read_idx;	// only one request handler can edit this read index
};

ExpCtrl2GuiMsg* allocate_exp_ctrl_2_gui_msg_buffer(ExpCtrl2GuiMsg* msg_buffer);
ExpCtrl2GuiMsg* deallocate_exp_ctrl_2_gui_msg_buffer(ExpCtrl2GuiMsg* msg_buffer);
bool get_exp_ctrl_2_gui_msg_type_string(ExpCtrl2GuiMsgType msg_type, char *str);
bool write_to_exp_ctrl_2_gui_msg_buffer(ExpCtrl2GuiMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2GuiMsgType msg_type, ExpCtrl2GuiMsgAdditional additional_data);
bool get_next_exp_ctrl_2_gui_msg_buffer_item(ExpCtrl2GuiMsg* msg_buffer, ExpCtrl2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
