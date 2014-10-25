#ifndef PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_H
#define PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_H

//  MESSAGES FROM MOV OBJ DURATION HANDLER TO MOV OBJ HANDLER

typedef struct __ProstheticCtrlDurHand2ProstheticCtrlMsg ProstheticCtrlDurHand2ProstheticCtrlMsg;
typedef struct __ProstheticCtrlDurHand2ProstheticCtrlMsgItem ProstheticCtrlDurHand2ProstheticCtrlMsgItem;
typedef unsigned int ProstheticCtrlDurHand2ProstheticCtrlMsgType;
typedef unsigned int ProstheticCtrlDurHand2ProstheticCtrlMsgAdditional;


#define PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH					100

#define PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_NULL							0
#define PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_TIMEOUT						1




#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ProstheticCtrlDurHand2ProstheticCtrlMsgItem
{
	TimeStamp 								msg_time;		
	ProstheticCtrlDurHand2ProstheticCtrlMsgType				msg_type;
	ProstheticCtrlDurHand2ProstheticCtrlMsgAdditional			additional_data;
};

struct __ProstheticCtrlDurHand2ProstheticCtrlMsg	
{
	ProstheticCtrlDurHand2ProstheticCtrlMsgItem		buff[PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_type_string(ProstheticCtrlDurHand2ProstheticCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ProstheticCtrlDurHand2ProstheticCtrlMsg* allocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer);
ProstheticCtrlDurHand2ProstheticCtrlMsg* deallocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer);
bool write_to_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrlDurHand2ProstheticCtrlMsgType msg_type, ProstheticCtrlDurHand2ProstheticCtrlMsgAdditional additional_data);
bool get_next_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer_item(ProstheticCtrlDurHand2ProstheticCtrlMsg* msg_buffer, ProstheticCtrlDurHand2ProstheticCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
