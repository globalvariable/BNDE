#ifndef EXP_CTRL_2_NEU_REC_HAND_H
#define EXP_CTRL_2_NEU_REC_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO NEURAL RECORDING HANDLER

typedef struct __ExpCtrl2NeuRecHandMsg ExpCtrl2NeuRecHandMsg;
typedef struct __ExpCtrl2NeuRecHandMsgItem ExpCtrl2NeuRecHandMsgItem;
typedef unsigned int ExpCtrl2NeuRecHandMsgType;
typedef unsigned int ExpCtrl2NeuRecHandMsgAdditional;


#define EXP_CTRL_2_NEU_REC_HAND_MSG_STRING_LENGTH						100

#define EXP_CTRL_2_NEU_REC_HAND_MSG_NULL									0
#define EXP_CTRL_2_NEU_REC_HAND_MSG_ARE_YOU_ALIVE						1
#define EXP_CTRL_2_NEU_REC_HAND_MSG_START_RECORDING					2
#define EXP_CTRL_2_NEU_REC_HAND_MSG_STOP_RECORDING					3
#define EXP_CTRL_2_NEU_REC_HAND_MSG_CANCEL_RECORDING					4    		// sent to cancel current recording
	

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ExpCtrl2NeuRecHandMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2NeuRecHandMsgType				msg_type;
	ExpCtrl2NeuRecHandMsgAdditional			additional_data;
};

struct __ExpCtrl2NeuRecHandMsg		// Requests to ExpControllers
{
	ExpCtrl2NeuRecHandMsgItem		buff[EXP_CTRL_2_NEU_REC_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_ctrl_2_neu_rec_hand_msg_type_string(ExpCtrl2NeuRecHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrl2NeuRecHandMsg* allocate_exp_ctrl_2_neu_rec_hand_msg_buffer(ExpCtrl2NeuRecHandMsg* msg_buffer);
ExpCtrl2NeuRecHandMsg* deallocate_exp_ctrl_2_neu_rec_hand_msg_buffer(ExpCtrl2NeuRecHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpCtrl2NeuRecHandMsg* allocate_shm_server_exp_ctrl_2_neu_rec_hand_msg_buffer(ExpCtrl2NeuRecHandMsg* msg_buffer);
ExpCtrl2NeuRecHandMsg* allocate_shm_client_exp_ctrl_2_neu_rec_hand_msg_buffer(ExpCtrl2NeuRecHandMsg* msg_buffer);
ExpCtrl2NeuRecHandMsg* deallocate_shm_exp_ctrl_2_neu_rec_hand_msg_buffer(ExpCtrl2NeuRecHandMsg* msg_buffer);
bool write_to_exp_ctrl_2_neu_rec_hand_msg_buffer(ExpCtrl2NeuRecHandMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2NeuRecHandMsgType msg_type, ExpCtrl2NeuRecHandMsgAdditional additional_data);
bool get_next_exp_ctrl_2_neu_rec_hand_msg_buffer_item(ExpCtrl2NeuRecHandMsg* msg_buffer, ExpCtrl2NeuRecHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif


