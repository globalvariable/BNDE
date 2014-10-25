#ifndef TRIAL_DUR_HAND_2_EXP_CTRL_H
#define TRIAL_DUR_HAND_2_EXP_CTRL_H

//  MESSAGES FROM TRIAL DURATION HANDLER TO TRIAL HANDLER

typedef struct __ExpCtrlDur2ExpCtrlMsg ExpCtrlDur2ExpCtrlMsg;
typedef struct __ExpCtrlDur2ExpCtrlMsgItem ExpCtrlDur2ExpCtrlMsgItem;
typedef unsigned int ExpCtrlDur2ExpCtrlMsgType;
typedef unsigned int ExpCtrlDur2ExpCtrlMsgAdditional;


#define TRIAL_DUR_HAND_2_EXP_CTRL_MSG_STRING_LENGTH					100

#define TRIAL_DUR_HAND_2_EXP_CTRL_MSG_NULL							0
#define TRIAL_DUR_HAND_2_EXP_CTRL_MSG_TIMEOUT						1
#define TRIAL_DUR_HAND_2_EXP_CTRL_MSG_EMERGENCY_EXIT				2




#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ExpCtrlDur2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrlDur2ExpCtrlMsgType				msg_type;
	ExpCtrlDur2ExpCtrlMsgAdditional			additional_data;
};

struct __ExpCtrlDur2ExpCtrlMsg		// Requests to ExpControllers
{
	ExpCtrlDur2ExpCtrlMsgItem		buff[TRIAL_DUR_HAND_2_EXP_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_dur_hand_2_exp_ctrl_msg_type_string(ExpCtrlDur2ExpCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrlDur2ExpCtrlMsg* allocate_trial_dur_hand_2_exp_ctrl_msg_buffer(ExpCtrlDur2ExpCtrlMsg* msg_buffer);
ExpCtrlDur2ExpCtrlMsg* deallocate_trial_dur_hand_2_exp_ctrl_msg_buffer(ExpCtrlDur2ExpCtrlMsg* msg_buffer);
bool write_to_trial_dur_hand_2_exp_ctrl_msg_buffer(ExpCtrlDur2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, ExpCtrlDur2ExpCtrlMsgType msg_type, ExpCtrlDur2ExpCtrlMsgAdditional additional_data);
bool get_next_trial_dur_hand_2_exp_ctrl_msg_buffer_item(ExpCtrlDur2ExpCtrlMsg* msg_buffer, ExpCtrlDur2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
