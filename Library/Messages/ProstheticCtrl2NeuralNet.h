#ifndef PROSTHETIC_CTRL_2_NEURAL_NET_H
#define PROSTHETIC_CTRL_2_NEURAL_NET_H

typedef struct __ProstheticCtrl2NeuralNetMsg ProstheticCtrl2NeuralNetMsg;
typedef struct __ProstheticCtrl2NeuralNetMsgItem ProstheticCtrl2NeuralNetMsgItem;
typedef unsigned int ProstheticCtrl2NeuralNetMsgType;
typedef struct __ProstheticCtrl2NeuralNetMsgAddBinaryReward ProstheticCtrl2NeuralNetMsgAddBinaryReward;

#include "../Robot/ThreeDofRobot.h"

struct __ProstheticCtrl2NeuralNetMsgAddBinaryReward
{
	int 			reward;
	unsigned int	target_idx;
};

typedef union 
{
	double three_dof_robot_joint_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double three_dof_robot_min_joint_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double three_dof_robot_max_joint_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double momentary_reward;
	bool dummy;
	ProstheticCtrl2NeuralNetMsgAddBinaryReward	binary_reward_add;
} ProstheticCtrl2NeuralNetMsgAdditional;

#include "../System/RtTasksData/RtTasksData.h"
#include "../System/ShmSemNum/ShmSemNum.h"


#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_STRING_LENGTH						100

#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_NULL								0
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE						1
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_3_DOF_JOINT_ANGLE					2
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN					3
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX					4
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_REINFORCEMENT						5
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_END_TRIAL_W_REWARD				6
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_END_TRIAL_W_PUNISH				7
#define PROSTHETIC_CTRL_2_NEURAL_NET_MSG_START_TRIAL							8

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ProstheticCtrl2NeuralNetMsgItem
{
	TimeStamp 								msg_time;
	ProstheticCtrl2NeuralNetMsgType				msg_type;
	TimeStamp 								scheduled_time;  // for handling by the message buffer handler.
	ProstheticCtrl2NeuralNetMsgAdditional			additional_data;
};

struct __ProstheticCtrl2NeuralNetMsg		// Requests to ExpControllers
{
	ProstheticCtrl2NeuralNetMsgItem		buff[PROSTHETIC_CTRL_2_NEURAL_NET_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
	TimeStamp						event_scheduling_delay;
};

bool get_prosthetic_ctrl_2_neural_net_msg_type_string(ProstheticCtrl2NeuralNetMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ProstheticCtrl2NeuralNetMsg* allocate_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer);
ProstheticCtrl2NeuralNetMsg* deallocate_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ProstheticCtrl2NeuralNetMsg* allocate_shm_server_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer);
ProstheticCtrl2NeuralNetMsg* allocate_shm_client_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY) ;
ProstheticCtrl2NeuralNetMsg* deallocate_shm_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer);
bool write_to_prosthetic_ctrl_2_neural_net_msg_buffer(ProstheticCtrl2NeuralNetMsg* msg_buffer, TimeStamp msg_time, ProstheticCtrl2NeuralNetMsgType msg_type, ProstheticCtrl2NeuralNetMsgAdditional additional_data);
bool get_next_prosthetic_ctrl_2_neural_net_msg_buffer_item(ProstheticCtrl2NeuralNetMsg* msg_buffer, ProstheticCtrl2NeuralNetMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

ProstheticCtrl2NeuralNetMsg** allocate_shm_server_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(ProstheticCtrl2NeuralNetMsg** msg_buffers, unsigned int num_of_threads);
ProstheticCtrl2NeuralNetMsg* allocate_shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item(ProstheticCtrl2NeuralNetMsg** msg_buffers, unsigned int msg_buffer_num, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY);
ProstheticCtrl2NeuralNetMsg** deallocate_shm_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(ProstheticCtrl2NeuralNetMsg** msg_buffers,  unsigned int num_of_threads);

#endif
