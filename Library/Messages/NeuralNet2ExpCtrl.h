#ifndef NEURAL_NET_2_EXP_CTRL_H
#define NEURAL_NET_2_EXP_CTRL_H

//  MESSAGES FROM NEURAL NET TO TRIAL HANDLER

typedef struct __NeuralNet2ExpCtrlMsg NeuralNet2ExpCtrlMsg;
typedef struct __NeuralNet2ExpCtrlMsgItem NeuralNet2ExpCtrlMsgItem;
typedef unsigned int NeuralNet2ExpCtrlMsgType;
typedef unsigned int NeuralNet2ExpCtrlMsgAdditional;

#define NEURAL_NET_2_EXP_CTRL_MSG_STRING_LENGTH					100

#define NEURAL_NET_2_EXP_CTRL_MSG_NULL							0
#define NEURAL_NET_2_EXP_CTRL_MSG_I_AM_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __NeuralNet2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	NeuralNet2ExpCtrlMsgType				msg_type;
	NeuralNet2ExpCtrlMsgAdditional			additional_data;
};

struct __NeuralNet2ExpCtrlMsg		// Requests to ExpControllers
{
	NeuralNet2ExpCtrlMsgItem		buff[NEURAL_NET_2_EXP_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_neural_net_2_exp_ctrl_msg_type_string(NeuralNet2ExpCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuralNet2ExpCtrlMsg* allocate_neural_net_2_exp_ctrl_msg_buffer(NeuralNet2ExpCtrlMsg* msg_buffer);
NeuralNet2ExpCtrlMsg* deallocate_neural_net_2_exp_ctrl_msg_buffer(NeuralNet2ExpCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
NeuralNet2ExpCtrlMsg* allocate_shm_server_neural_net_2_exp_ctrl_msg_buffer(NeuralNet2ExpCtrlMsg* msg_buffer);
NeuralNet2ExpCtrlMsg* allocate_shm_client_neural_net_2_exp_ctrl_msg_buffer(NeuralNet2ExpCtrlMsg* msg_buffer);
NeuralNet2ExpCtrlMsg* deallocate_shm_neural_net_2_exp_ctrl_msg_buffer(NeuralNet2ExpCtrlMsg* msg_buffer);
bool write_to_neural_net_2_exp_ctrl_msg_buffer(NeuralNet2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, NeuralNet2ExpCtrlMsgType msg_type,  NeuralNet2ExpCtrlMsgAdditional additional_data);
bool get_next_neural_net_2_exp_ctrl_msg_buffer_item(NeuralNet2ExpCtrlMsg* msg_buffer, NeuralNet2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
