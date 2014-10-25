#ifndef EXP_CTRL_2_DIO_CTRL_H
#define EXP_CTRL_2_DIO_CTRL_H

//  MESSAGES FROM TRIAL HANDLER TO EXP ENVI HANDLER

typedef struct __ExpCtrl2DioCtrlMsg ExpCtrl2DioCtrlMsg;
typedef struct __ExpCtrl2DioCtrlMsgItem ExpCtrl2DioCtrlMsgItem;
typedef unsigned int ExpCtrl2DioCtrlMsgType;
typedef unsigned int ExpCtrl2DioCtrlMsgAdditional;


#define EXP_CTRL_2_DIO_CTRL_MSG_STRING_LENGTH						100

#define EXP_CTRL_2_DIO_CTRL_MSG_NULL									0
#define EXP_CTRL_2_DIO_CTRL_MSG_ARE_YOU_ALIVE						1
#define EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL							2		// send trial type as additional
#define EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL							3
#define EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_REWARD					4	
#define EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_PUNISHMENT				5	
#define EXP_CTRL_2_DIO_CTRL_MSG_START_RECORDING					6
#define EXP_CTRL_2_DIO_CTRL_MSG_STOP_RECORDING					7
#define EXP_CTRL_2_DIO_CTRL_MSG_CANCEL_RECORDING					8    		// sent to cancel current recording
#define EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_NO_STATUS_RESET	9    		
#define EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_STATUS_RESET	10    		
#define EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_INPUT_COMPONENTS			11    		
#define EXP_CTRL_2_DIO_CTRL_MSG_GET_READY_TO_TRIAL_START			12    
#define EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_LEVERS						13
#define EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_LEVERS_W_STATUS_RESET	14
#define EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE_RETRACT		15
#define EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_NOSE_POKE_RETRACT		16
#define EXP_CTRL_2_DIO_CTRL_MSG_INVALID_START_TRIAL_REQUEST		17
#define EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL_AVAILABLE				18
#define EXP_CTRL_2_DIO_CTRL_MSG_CUE_LED_ON							19
#define EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL_WHEN_GET_READY		20
#define EXP_CTRL_2_DIO_CTRL_MSG_TURN_BUZZER_OFF					21
#define EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE					22

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ExpCtrl2DioCtrlMsgItem
{
	TimeStamp 								msg_time;		
	ExpCtrl2DioCtrlMsgType				msg_type;
	ExpCtrl2DioCtrlMsgAdditional			additional_data;
};

struct __ExpCtrl2DioCtrlMsg		// Requests to ExpControllers
{
	ExpCtrl2DioCtrlMsgItem		buff[EXP_CTRL_2_DIO_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_ctrl_2_dio_ctrl_msg_type_string(ExpCtrl2DioCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpCtrl2DioCtrlMsg* allocate_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer);
ExpCtrl2DioCtrlMsg* deallocate_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpCtrl2DioCtrlMsg* allocate_shm_server_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer);
ExpCtrl2DioCtrlMsg* allocate_shm_client_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer);
ExpCtrl2DioCtrlMsg* deallocate_shm_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer);
bool write_to_exp_ctrl_2_dio_ctrl_msg_buffer(ExpCtrl2DioCtrlMsg* msg_buffer, TimeStamp msg_time, ExpCtrl2DioCtrlMsgType msg_type, ExpCtrl2DioCtrlMsgAdditional additional_data);
bool get_next_exp_ctrl_2_dio_ctrl_msg_buffer_item(ExpCtrl2DioCtrlMsg* msg_buffer, ExpCtrl2DioCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
