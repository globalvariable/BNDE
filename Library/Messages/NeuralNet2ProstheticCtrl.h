#ifndef NEURAL_NET_2_PROSTHETIC_CTRL_H
#define NEURAL_NET_2_PROSTHETIC_CTRL_H


//  MESSAGES FROM NEURAL NET TO MOV OBJ HANDLER

typedef struct __NeuralNet2ProstheticCtrlMsg NeuralNet2ProstheticCtrlMsg;
typedef struct __NeuralNet2ProstheticCtrlMsgItem NeuralNet2ProstheticCtrlMsgItem;
typedef unsigned int NeuralNet2ProstheticCtrlMsgType;
#include "../System/RtTasksData/RtTasksData.h"
#include "../System/ShmSemNum/ShmSemNum.h"




#define NEURAL_NET_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH					100

#define NEURAL_NET_2_PROSTHETIC_CTRL_MSG_NULL							0
#define NEURAL_NET_2_PROSTHETIC_CTRL_MSG_I_AM_ALIVE						1
#define NEURAL_NET_2_PROSTHETIC_CTRL_MSG_SPIKE_OUTPUT					2

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "../ProstheticCtrlData/ProstheticCtrlComponentTypes.h"
#include "../ProstheticCtrlData/ProstheticCtrlDirectionTypes.h"
#include "../ProstheticCtrlData/ProstheticCtrlSpeedType.h"
#include "../ProstheticCtrlData/ProstheticCtrlLocationType.h"

struct __NeuralNet2ProstheticCtrlMsgItem
{
	TimeStamp 					msg_time;		
	NeuralNet2ProstheticCtrlMsgType	msg_type;
	unsigned int					layer_num;
	unsigned int					nrn_grp_num;
	unsigned int					neuron_num;
	TimeStamp 					spike_time;		
};

struct __NeuralNet2ProstheticCtrlMsg		// Requests to ExpControllers
{
	NeuralNet2ProstheticCtrlMsgItem	buff[NEURAL_NET_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
	TimeStamp					event_scheduling_delay;
};

bool get_neural_net_2_prosthetic_ctrl_msg_type_string(NeuralNet2ProstheticCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuralNet2ProstheticCtrlMsg* allocate_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer);
NeuralNet2ProstheticCtrlMsg* deallocate_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
NeuralNet2ProstheticCtrlMsg* allocate_shm_server_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer);
NeuralNet2ProstheticCtrlMsg* allocate_shm_client_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
NeuralNet2ProstheticCtrlMsg* deallocate_shm_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer);
bool write_to_neural_net_2_prosthetic_ctrl_msg_buffer(NeuralNet2ProstheticCtrlMsg* msg_buffer, TimeStamp msg_time, NeuralNet2ProstheticCtrlMsgType msg_type, unsigned int layer_num, unsigned int nrn_grp_num, unsigned int neuron_num, TimeStamp spike_time);
bool get_next_neural_net_2_prosthetic_ctrl_msg_buffer_item(NeuralNet2ProstheticCtrlMsg* msg_buffer, NeuralNet2ProstheticCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

NeuralNet2ProstheticCtrlMsg** allocate_shm_server_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(NeuralNet2ProstheticCtrlMsg** msg_buffers,  unsigned int num_of_threads);
NeuralNet2ProstheticCtrlMsg* allocate_shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer_item(NeuralNet2ProstheticCtrlMsg** msg_buffers, unsigned int msg_buffer_num, TimeStamp event_scheduling_delay,  TimeStamp HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
NeuralNet2ProstheticCtrlMsg** deallocate_shm_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(NeuralNet2ProstheticCtrlMsg** msg_buffers,  unsigned int num_of_threads);


#endif
