#ifndef EXP_CTRL_2_SPIKE_GEN_H
#define EXP_CTRL_2_SPIKE_GEN_H

//  MESSAGES FROM TRIAL HANDLER TO SPIKE GENERATOR

typedef struct __ExpCtrl2SpikeGenMsg ExpCtrl2SpikeGenMsg;
typedef struct __ExpCtrl2SpikeGenMsgItem ExpCtrl2SpikeGenMsgItem;
typedef unsigned int ExpCtrl2SpikeGenMsgType;

#include "ExpCtrl2NeuralNet.h"

typedef ExpCtrl2NeuralNetExpStatusMsgAdd ExpCtrl2SpikeGenExpStatusMsgAdd;

typedef ExpCtrl2NeuralNetMsgAdditional ExpCtrl2SpikeGenMsgAdditional;



#define EXP_CTRL_2_SPIKE_GEN_MSG_STRING_LENGTH						100

#define EXP_CTRL_2_SPIKE_GEN_MSG_NULL									0
#define EXP_CTRL_2_SPIKE_GEN_MSG_ARE_YOU_ALIVE						1
#define EXP_CTRL_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED				2
#define EXP_CTRL_2_SPIKE_GEN_MSG_START_RECORDING					3
#define EXP_CTRL_2_SPIKE_GEN_MSG_STOP_RECORDING						4
#define EXP_CTRL_2_SPIKE_GEN_MSG_CANCEL_RECORDING					5   // sent to cancel current recording



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ExpCtrl2SpikeGenMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2SpikeGenMsgType				msg_type;
	ExpCtrl2SpikeGenMsgAdditional			additional_data;
};

struct __ExpCtrl2SpikeGenMsg		// Requests to ExpControllers
{
	ExpCtrl2SpikeGenMsgItem		buff[EXP_CTRL_2_SPIKE_GEN_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_ctrl_2_spike_gen_msg_type_string(ExpCtrl2SpikeGenMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrl2SpikeGenMsg* allocate_exp_ctrl_2_spike_gen_msg_buffer(ExpCtrl2SpikeGenMsg* msg_buffer);
ExpCtrl2SpikeGenMsg* deallocate_exp_ctrl_2_spike_gen_msg_buffer(ExpCtrl2SpikeGenMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpCtrl2SpikeGenMsg* allocate_shm_server_exp_ctrl_2_spike_gen_msg_buffer(ExpCtrl2SpikeGenMsg* msg_buffer);
ExpCtrl2SpikeGenMsg* allocate_shm_client_exp_ctrl_2_spike_gen_msg_buffer(ExpCtrl2SpikeGenMsg* msg_buffer);
ExpCtrl2SpikeGenMsg* deallocate_shm_exp_ctrl_2_spike_gen_msg_buffer(ExpCtrl2SpikeGenMsg* msg_buffer);
bool write_to_exp_ctrl_2_spike_gen_msg_buffer(ExpCtrl2SpikeGenMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2SpikeGenMsgType msg_type, ExpCtrl2SpikeGenMsgAdditional additional_data);
bool get_next_exp_ctrl_2_spike_gen_msg_buffer_item(ExpCtrl2SpikeGenMsg* msg_buffer, ExpCtrl2SpikeGenMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
