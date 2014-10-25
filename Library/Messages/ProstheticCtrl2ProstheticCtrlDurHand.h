#ifndef PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_H
#define PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_H

//  MESSAGES FROM MOV OBJ HANDLER TO MOV OBJ DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

typedef struct __ProstheticCtrl2ProstheticCtrlDurHandMsg ProstheticCtrl2ProstheticCtrlDurHandMsg;
typedef struct __ProstheticCtrl2ProstheticCtrlDurHandMsgItem ProstheticCtrl2ProstheticCtrlDurHandMsgItem;
typedef unsigned int ProstheticCtrl2ProstheticCtrlDurHandMsgType;

typedef struct 
{ 
	unsigned int	item_idx;
	TimeStamp	schedule;
} ScheduleAdditionalData;

typedef union 
{
	ScheduleAdditionalData	schedule;
	bool				dummy;
}
ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional;


#define PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_STRING_LENGTH					100

#define PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_NULL							0
#define PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE					1
#define PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_CANCEL_SCHEDULE				2


struct __ProstheticCtrl2ProstheticCtrlDurHandMsgItem
{
	TimeStamp 								msg_time;		
	ProstheticCtrl2ProstheticCtrlDurHandMsgType				msg_type;
	ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional			additional_data;
};

struct __ProstheticCtrl2ProstheticCtrlDurHandMsg		
{
	ProstheticCtrl2ProstheticCtrlDurHandMsgItem		buff[PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_type_string(ProstheticCtrl2ProstheticCtrlDurHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ProstheticCtrl2ProstheticCtrlDurHandMsg* allocate_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(ProstheticCtrl2ProstheticCtrlDurHandMsg* msg_buffer);
ProstheticCtrl2ProstheticCtrlDurHandMsg* deallocate_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(ProstheticCtrl2ProstheticCtrlDurHandMsg* msg_buffer);
bool write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(ProstheticCtrl2ProstheticCtrlDurHandMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2ProstheticCtrlDurHandMsgType msg_type, ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional additional_data);
bool get_next_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer_item(ProstheticCtrl2ProstheticCtrlDurHandMsg* msg_buffer, ProstheticCtrl2ProstheticCtrlDurHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
