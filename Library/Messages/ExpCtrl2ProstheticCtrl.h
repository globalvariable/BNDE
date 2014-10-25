#ifndef EXP_CTRL_2_PROSTHETIC_CTRL_H
#define EXP_CTRL_2_PROSTHETIC_CTRL_H

//  MESSAGES FROM TRIAL HANDLER TO MOV OBJ HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "../Robot/ThreeDofRobot.h"

typedef struct __ExpCtrl2ProstheticCtrlMsg ExpCtrl2ProstheticCtrlMsg;
typedef struct __ExpCtrl2ProstheticCtrlMsgItem ExpCtrl2ProstheticCtrlMsgItem;
typedef unsigned int ExpCtrl2ProstheticCtrlMsgType;

typedef union __ExpCtrl2ProstheticCtrlMsgAdditional ExpCtrl2ProstheticCtrlMsgAdditional;

#include "../Thresholding/Thresholding.h"

union __ExpCtrl2ProstheticCtrlMsgAdditional
{
	EllipsoidThreshold	threshold;
	unsigned int		robot_start_position_idx;
	unsigned int		robot_target_position_idx;
	unsigned int		recording_number;
	bool			dummy;
};


#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH					100

#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_NULL							0
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ARE_YOU_ALIVE				1
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_TRIAL					2		// send trial type as additional
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIAL_TIMEOUT				3		
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_TRIAL					4
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ELLIPSOID_THRESHOLD		5
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_ENABLED				6
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_DISABLED				7
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_RECORDING			8
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STOP_RECORDING				9
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CANCEL_RECORDING			10		// sent to cancel current recording
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_LEVER_PRESS_TIMEOUT		11
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_BY_NOSE_RETRACT		12
#define EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CHANGE_TARGET				13

struct __ExpCtrl2ProstheticCtrlMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2ProstheticCtrlMsgType				msg_type;
	ExpCtrl2ProstheticCtrlMsgAdditional			additional_data;
};

struct __ExpCtrl2ProstheticCtrlMsg		// Requests to ExpControllers
{
	ExpCtrl2ProstheticCtrlMsgItem		buff[EXP_CTRL_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_ctrl_2_prosthetic_ctrl_msg_type_string(ExpCtrl2ProstheticCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrl2ProstheticCtrlMsg* allocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer);
ExpCtrl2ProstheticCtrlMsg* deallocate_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpCtrl2ProstheticCtrlMsg* allocate_shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer);
ExpCtrl2ProstheticCtrlMsg* allocate_shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer);
ExpCtrl2ProstheticCtrlMsg* deallocate_shm_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer);
bool write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(ExpCtrl2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2ProstheticCtrlMsgType msg_type, ExpCtrl2ProstheticCtrlMsgAdditional additional_data);
bool get_next_exp_ctrl_2_prosthetic_ctrl_msg_buffer_item(ExpCtrl2ProstheticCtrlMsg* msg_buffer, ExpCtrl2ProstheticCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
