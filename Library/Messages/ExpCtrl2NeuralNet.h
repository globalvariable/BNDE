#ifndef EXP_CTRL_2_NEURAL_NET_H
#define EXP_CTRL_2_NEURAL_NET_H

//  MESSAGES FROM TRIAL HANDLER TO NEURAL NET

typedef struct __ExpCtrl2NeuralNetMsg ExpCtrl2NeuralNetMsg;
typedef struct __ExpCtrl2NeuralNetMsgItem ExpCtrl2NeuralNetMsgItem;
typedef unsigned int ExpCtrl2NeuralNetMsgType;

typedef struct __ExpCtrl2NeuralNetExpStatusMsgAdd ExpCtrl2NeuralNetExpStatusMsgAdd;
typedef struct __ExpCtrl2NeuralNetDifficultyRewardAdd ExpCtrl2NeuralNetDifficultyRewardAdd;


typedef union __ExpCtrl2NeuralNetMsgAdditional ExpCtrl2NeuralNetMsgAdditional;

#include "../Status/ExpStatus.h"

struct __ExpCtrl2NeuralNetExpStatusMsgAdd
{
	ExpStatus 	new_trial_status;
	unsigned int	new_robot_start_position_idx;   // in ExpCtrlParadigm
	unsigned int	new_robot_target_position_idx;   // in ExpCtrlParadigm
};

struct __ExpCtrl2NeuralNetDifficultyRewardAdd
{
	unsigned int	difficulty_level;
	double		reward_prediction;
};

union __ExpCtrl2NeuralNetMsgAdditional
{
	ExpCtrl2NeuralNetExpStatusMsgAdd trial_status_change_msg_add;
	ExpCtrl2NeuralNetDifficultyRewardAdd difficulty_reward_predict_add;
	double reward;
	unsigned int recording_number;
	bool dummy;
};





#define EXP_CTRL_2_NEURAL_NET_MSG_STRING_LENGTH						100

#define EXP_CTRL_2_NEURAL_NET_MSG_NULL								0
#define EXP_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE						1
#define EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED				2
#define EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_START						3
#define EXP_CTRL_2_NEURAL_NET_MSG_REWARD_GIVEN						4
#define EXP_CTRL_2_NEURAL_NET_MSG_PUNISHMENT_GIVEN					5
#define EXP_CTRL_2_NEURAL_NET_MSG_START_RECORDING					6
#define EXP_CTRL_2_NEURAL_NET_MSG_STOP_RECORDING					7
#define EXP_CTRL_2_NEURAL_NET_MSG_CANCEL_RECORDING					8   // sent to cancel current recording
#define EXP_CTRL_2_NEURAL_NET_MSG_END_TRIAL_WITH_NOTHING			9   // sent to cancel current recording

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"


struct __ExpCtrl2NeuralNetMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2NeuralNetMsgType				msg_type;
	ExpCtrl2NeuralNetMsgAdditional			additional_data;
};

struct __ExpCtrl2NeuralNetMsg		// Requests to ExpControllers
{
	ExpCtrl2NeuralNetMsgItem		buff[EXP_CTRL_2_NEURAL_NET_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};



bool get_exp_ctrl_2_neural_net_msg_type_string(ExpCtrl2NeuralNetMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrl2NeuralNetMsg* allocate_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer);
ExpCtrl2NeuralNetMsg* deallocate_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpCtrl2NeuralNetMsg* allocate_shm_server_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer);
ExpCtrl2NeuralNetMsg* allocate_shm_client_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer);
ExpCtrl2NeuralNetMsg* deallocate_shm_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer);
bool write_to_exp_ctrl_2_neural_net_msg_buffer(ExpCtrl2NeuralNetMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2NeuralNetMsgType msg_type, ExpCtrl2NeuralNetMsgAdditional additional_data);
bool get_next_exp_ctrl_2_neural_net_msg_buffer_item(ExpCtrl2NeuralNetMsg* msg_buffer, ExpCtrl2NeuralNetMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
