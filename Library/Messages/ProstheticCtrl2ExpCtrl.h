#ifndef PROSTHETIC_CTRL_2_EXP_CTRL_H
#define PROSTHETIC_CTRL_2_EXP_CTRL_H

//  MESSAGES FROM EXP ENVI HANDLER TO TRIAL HANDLER

typedef struct __ProstheticCtrl2ExpCtrlMsg ProstheticCtrl2ExpCtrlMsg;
typedef struct __ProstheticCtrl2ExpCtrlMsgItem ProstheticCtrl2ExpCtrlMsgItem;
typedef unsigned int ProstheticCtrl2ExpCtrlMsgType;
typedef double ProstheticCtrl2ExpCtrlMsgAdditional;


#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_STRING_LENGTH					100

#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_NULL								0
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE						1
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST				2		// sends it out when the robot reached the threshold point.
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST			3		// sends it out when the robot reached the threshold point.
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_END_TRIAL_REQUEST				4		// sends it out when the timeout after reaching to target appears
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED		5		// sends it out when the timeout after staying at start point appears.
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_INITIAL_DIST_2_TARGET	6		// sends it out when the timeout after staying at start point appears.
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_TARGET				7		// sends it out by the time mov obj reaches the target
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_OUT_OF_ROBOT_SPACE			8
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_LEVER_PRESS		9		// sends it out by the time mov obj reaches the target
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_REWARD_THRES		10
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_THRESHOLD			11
#define PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REACHED_2_THRESHOLD_2		12

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ProstheticCtrl2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	ProstheticCtrl2ExpCtrlMsgType				msg_type;
	ProstheticCtrl2ExpCtrlMsgAdditional			additional_data;
};

struct __ProstheticCtrl2ExpCtrlMsg		// Requests to ExpControllers
{
	ProstheticCtrl2ExpCtrlMsgItem		buff[PROSTHETIC_CTRL_2_EXP_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_prosthetic_ctrl_2_exp_ctrl_msg_type_string(ProstheticCtrl2ExpCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ProstheticCtrl2ExpCtrlMsg* allocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer);
ProstheticCtrl2ExpCtrlMsg* deallocate_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ProstheticCtrl2ExpCtrlMsg* allocate_shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer);
ProstheticCtrl2ExpCtrlMsg* allocate_shm_client_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer);
ProstheticCtrl2ExpCtrlMsg* deallocate_shm_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer);
bool write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(ProstheticCtrl2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2ExpCtrlMsgType msg_type, ProstheticCtrl2ExpCtrlMsgAdditional additional_data);
bool get_next_prosthetic_ctrl_2_exp_ctrl_msg_buffer_item(ProstheticCtrl2ExpCtrlMsg* msg_buffer, ProstheticCtrl2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
