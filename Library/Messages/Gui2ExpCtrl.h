#ifndef GUI_2_EXP_CTRL_H
#define GUI_2_EXP_CTRL_H

//  MESSAGES FROM TRIAL HANDLER GUI TO TRIAL HANDLER

typedef struct __Gui2ExpCtrlMsg Gui2ExpCtrlMsg;
typedef struct __Gui2ExpCtrlMsgItem Gui2ExpCtrlMsgItem;
typedef unsigned int Gui2ExpCtrlMsgType;
typedef unsigned int Gui2ExpCtrlMsgAdditional;


#define GUI_2_EXP_CTRL_MSG_STRING_LENGTH		50

#define GUI_2_EXP_CTRL_MSG_NULL								0
#define GUI_2_EXP_CTRL_MSG_ENABLE_EXP_CTRLLING			1
#define GUI_2_EXP_CTRL_MSG_DISABLE_EXP_CTRLLING			2
#define GUI_2_EXP_CTRL_MSG_QUIT								3
#define GUI_2_EXP_CTRL_MSG_INCREASE_THRESHOLD			4
#define GUI_2_EXP_CTRL_MSG_DECREASE_THRESHOLD			5
#define GUI_2_EXP_CTRL_MSG_SELECT_TARGET					6
#define GUI_2_EXP_CTRL_MSG_AUTO_TARGET_SELECTION_ON		7
#define GUI_2_EXP_CTRL_MSG_AUTO_TARGET_SELECTION_OFF	8 
#define GUI_2_EXP_CTRL_MSG_BROADCAST_START_RECORDING	9 
#define GUI_2_EXP_CTRL_MSG_BROADCAST_STOP_RECORDING	10 
#define GUI_2_EXP_CTRL_MSG_BROADCAST_CANCEL_RECORDING	11 
#define GUI_2_EXP_CTRL_MSG_RELEASE_REWARD				12 
#define GUI_2_EXP_CTRL_MSG_INCREASE_ROBOT_START_POSITION_IDX	13
#define GUI_2_EXP_CTRL_MSG_DECREASE_ROBOT_START_POSITION_IDX	14
#define GUI_2_EXP_CTRL_MSG_CATCH_TRIAL_MODE_ON					15
#define GUI_2_EXP_CTRL_MSG_CATCH_TRIAL_MODE_OFF					16
#define GUI_2_EXP_CTRL_MSG_LEVER_PRESS_MODE_ON					17
#define GUI_2_EXP_CTRL_MSG_LEVER_PRESS_MODE_OFF					18
#define GUI_2_EXP_CTRL_MSG_TURN_LEVER_PRESS_MODE_ON			19
#define GUI_2_EXP_CTRL_MSG_TURN_LEVER_PRESS_MODE_OFF			20
#define GUI_2_EXP_CTRL_MSG_TURN_NOSE_RETRACT_MODE_ON			21
#define GUI_2_EXP_CTRL_MSG_TURN_NOSE_RETRACT_MODE_OFF			22
#define GUI_2_EXP_CTRL_MSG_END_TRIAL								23
#define GUI_2_EXP_CTRL_MSG_FULL_CATCH_TRIAL_MODE_ON				24
#define GUI_2_EXP_CTRL_MSG_FULL_CATCH_TRIAL_MODE_OFF			25
#define GUI_2_EXP_CTRL_MSG_START_TRIAL_REQUEST					26

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __Gui2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	Gui2ExpCtrlMsgType						msg_type;
	Gui2ExpCtrlMsgAdditional					additional_data;
};

struct __Gui2ExpCtrlMsg		// Requests to ExpControllers
{
	Gui2ExpCtrlMsgItem		buff[GUI_2_EXP_CTRL_MSG_BUFFER_SIZE];
	unsigned int				buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int				buff_read_idx;	// only one request handler can edit this read index
};

Gui2ExpCtrlMsg* allocate_gui_2_exp_ctrl_msg_buffer(Gui2ExpCtrlMsg* msg_buffer);
Gui2ExpCtrlMsg* deallocate_gui_2_exp_ctrl_msg_buffer(Gui2ExpCtrlMsg* msg_buffer);
bool get_gui_2_exp_ctrl_msg_type_string(Gui2ExpCtrlMsgType msg_type, char *str);
bool write_to_gui_2_exp_ctrl_msg_buffer(Gui2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, Gui2ExpCtrlMsgType msg_type, Gui2ExpCtrlMsgAdditional additional_data);
bool get_next_gui_2_exp_ctrl_msg_buffer_item(Gui2ExpCtrlMsg* msg_buffer, Gui2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
