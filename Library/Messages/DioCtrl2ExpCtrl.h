#ifndef DIO_CTRL_2_EXP_CTRL_H
#define DIO_CTRL_2_EXP_CTRL_H

//  MESSAGES FROM EXP ENVI HANDLER TO TRIAL HANDLER

typedef struct __DioCtrl2ExpCtrlMsg DioCtrl2ExpCtrlMsg;
typedef struct __DioCtrl2ExpCtrlMsgItem DioCtrl2ExpCtrlMsgItem;
typedef unsigned int DioCtrl2ExpCtrlMsgType;
typedef unsigned int DioCtrl2ExpCtrlMsgAdditional;


#define DIO_CTRL_2_EXP_CTRL_MSG_STRING_LENGTH					100

#define DIO_CTRL_2_EXP_CTRL_MSG_NULL								0
#define DIO_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE						1
#define DIO_CTRL_2_EXP_CTRL_MSG_START_TRIAL_REQUEST			2
#define DIO_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST				3		
#define DIO_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST			4		
#define DIO_CTRL_2_EXP_CTRL_MSG_END_TRIAL_REQUEST				5
#define DIO_CTRL_2_EXP_CTRL_MSG_NOSE_POKE_EVENT				6
#define DIO_CTRL_2_EXP_CTRL_MSG_NOSE_RETRACT_EVENT			7
#define DIO_CTRL_2_EXP_CTRL_MSG_RESTRAIN_RELEASE_REQ			8
#define DIO_CTRL_2_EXP_CTRL_MSG_LEVER_RELEASE				9

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __DioCtrl2ExpCtrlMsgItem
{
	TimeStamp 								msg_time;		
	DioCtrl2ExpCtrlMsgType				msg_type;
	DioCtrl2ExpCtrlMsgAdditional			additional_data;
};

struct __DioCtrl2ExpCtrlMsg		// Requests to ExpControllers
{
	DioCtrl2ExpCtrlMsgItem		buff[DIO_CTRL_2_EXP_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_dio_ctrl_2_exp_ctrl_msg_type_string(DioCtrl2ExpCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
DioCtrl2ExpCtrlMsg* allocate_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer);
DioCtrl2ExpCtrlMsg* deallocate_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
DioCtrl2ExpCtrlMsg* allocate_shm_server_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer);
DioCtrl2ExpCtrlMsg* allocate_shm_client_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer);
DioCtrl2ExpCtrlMsg* deallocate_shm_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer);
bool write_to_dio_ctrl_2_exp_ctrl_msg_buffer(DioCtrl2ExpCtrlMsg* msg_buffer, TimeStamp msg_time, DioCtrl2ExpCtrlMsgType msg_type, DioCtrl2ExpCtrlMsgAdditional additional_data);
bool get_next_dio_ctrl_2_exp_ctrl_msg_buffer_item(DioCtrl2ExpCtrlMsg* msg_buffer, DioCtrl2ExpCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses



#endif
