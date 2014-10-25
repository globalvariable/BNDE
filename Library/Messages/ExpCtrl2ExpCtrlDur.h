#ifndef EXP_CTRL_2_TRIAL_DUR_HAND_H
#define EXP_CTRL_2_TRIAL_DUR_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO TRIAL DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"


typedef struct __ExpCtrl2ExpCtrlDurMsg ExpCtrl2ExpCtrlDurMsg;
typedef struct __ExpCtrl2ExpCtrlDurMsgItem ExpCtrl2ExpCtrlDurMsgItem;
typedef unsigned int ExpCtrl2ExpCtrlDurMsgType;
typedef TimeStamp ExpCtrl2ExpCtrlDurMsgAdditional;


#define EXP_CTRL_2_TRIAL_DUR_HAND_MSG_STRING_LENGTH					100

#define EXP_CTRL_2_TRIAL_DUR_HAND_MSG_NULL							0
#define EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING	1
#define EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING	2  // When a phase of trial is complete, trial handler sends this to trial duration handler to cancel timer.
 




struct __ExpCtrl2ExpCtrlDurMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2ExpCtrlDurMsgType				msg_type;
	ExpCtrl2ExpCtrlDurMsgAdditional			additional_data;
};

struct __ExpCtrl2ExpCtrlDurMsg		// Requests to ExpControllers
{
	ExpCtrl2ExpCtrlDurMsgItem		buff[EXP_CTRL_2_TRIAL_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_ctrl_2_trial_dur_hand_msg_type_string(ExpCtrl2ExpCtrlDurMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrl2ExpCtrlDurMsg* allocate_exp_ctrl_2_trial_dur_hand_msg_buffer(ExpCtrl2ExpCtrlDurMsg* msg_buffer);
ExpCtrl2ExpCtrlDurMsg* deallocate_exp_ctrl_2_trial_dur_hand_msg_buffer(ExpCtrl2ExpCtrlDurMsg* msg_buffer);
bool write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(ExpCtrl2ExpCtrlDurMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2ExpCtrlDurMsgType msg_type, ExpCtrl2ExpCtrlDurMsgAdditional additional_data);
bool get_next_exp_ctrl_2_trial_dur_hand_msg_buffer_item(ExpCtrl2ExpCtrlDurMsg* msg_buffer, ExpCtrl2ExpCtrlDurMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
