#ifndef SPIKE_GEN_2_EXP_CTRL_H
#define SPIKE_GEN_2_EXP_CTRL_H

//  MESSAGES FROM SPIKE GENERATOR TO TRIAL HANDLER

typedef struct __SpikeGen2ExpCtrlMsg SpikeGen2ExpCtrlMsg;
typedef struct __SpikeGen2ExpCtrlMsgItem SpikeGen2ExpCtrlMsgItem;
typedef unsigned int SpikeGen2ExpCtrlMsgType;
typedef unsigned int SpikeGen2ExpCtrlMsgAdditional;

#define SPIKE_GEN_2_EXP_CTRL_MSG_STRING_LENGTH					100

#define SPIKE_GEN_2_EXP_CTRL_MSG_NULL							0
#define SPIKE_GEN_2_EXP_CTRL_MSG_I_AM_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __SpikeGen2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	SpikeGen2ExpCtrlMsgType				msg_type;
	SpikeGen2ExpCtrlMsgAdditional			additional_data;
};

struct __SpikeGen2ExpCtrlMsg		// Requests to ExpControllers
{
	SpikeGen2ExpCtrlMsgItem		buff[SPIKE_GEN_2_EXP_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_spike_gen_2_exp_ctrl_msg_type_string(SpikeGen2ExpCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
SpikeGen2ExpCtrlMsg* allocate_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer);
SpikeGen2ExpCtrlMsg* deallocate_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
SpikeGen2ExpCtrlMsg* allocate_shm_server_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer);
SpikeGen2ExpCtrlMsg* allocate_shm_client_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer);
SpikeGen2ExpCtrlMsg* deallocate_shm_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer);
bool write_to_spike_gen_2_exp_ctrl_msg_buffer(SpikeGen2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, SpikeGen2ExpCtrlMsgType msg_type,  SpikeGen2ExpCtrlMsgAdditional additional_data);
bool get_next_spike_gen_2_exp_ctrl_msg_buffer_item(SpikeGen2ExpCtrlMsg* msg_buffer, SpikeGen2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
