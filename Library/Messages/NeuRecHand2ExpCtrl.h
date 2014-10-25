#ifndef NEU_REC_HAND_2_EXP_CTRL_H
#define NEU_REC_HAND_2_EXP_CTRL_H

//  MESSAGES FROM NEURAL RECORDING HANDLER TO TRIAL HANDLER

typedef struct __NeuRecHand2ExpCtrlMsg NeuRecHand2ExpCtrlMsg;
typedef struct __NeuRecHand2ExpCtrlMsgItem NeuRecHand2ExpCtrlMsgItem;
typedef unsigned int NeuRecHand2ExpCtrlMsgType;
typedef unsigned int NeuRecHand2ExpCtrlMsgAdditional;


#define NEU_REC_HAND_2_EXP_CTRL_MSG_STRING_LENGTH					100

#define NEU_REC_HAND_2_EXP_CTRL_MSG_NULL								0
#define NEU_REC_HAND_2_EXP_CTRL_MSG_I_AM_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __NeuRecHand2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	NeuRecHand2ExpCtrlMsgType				msg_type;
	NeuRecHand2ExpCtrlMsgAdditional			additional_data;
};

struct __NeuRecHand2ExpCtrlMsg		// Requests to ExpControllers
{
	NeuRecHand2ExpCtrlMsgItem		buff[NEU_REC_HAND_2_EXP_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_neu_rec_hand_2_exp_ctrl_msg_type_string(NeuRecHand2ExpCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuRecHand2ExpCtrlMsg* allocate_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer);
NeuRecHand2ExpCtrlMsg* deallocate_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
NeuRecHand2ExpCtrlMsg* allocate_shm_server_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer);
NeuRecHand2ExpCtrlMsg* allocate_shm_client_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer);
NeuRecHand2ExpCtrlMsg* deallocate_shm_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer);
bool write_to_neu_rec_hand_2_exp_ctrl_msg_buffer(NeuRecHand2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, NeuRecHand2ExpCtrlMsgType msg_type, NeuRecHand2ExpCtrlMsgAdditional additional_data);
bool get_next_neu_rec_hand_2_exp_ctrl_msg_buffer_item(NeuRecHand2ExpCtrlMsg* msg_buffer, NeuRecHand2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses



#endif
