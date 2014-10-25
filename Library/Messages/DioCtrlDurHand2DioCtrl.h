#ifndef DIO_CTRL_DUR_HAND_2_DIO_CTRL_H
#define DIO_CTRL_DUR_HAND_2_DIO_CTRL_H

//  MESSAGES FROM EXP ENVI DURATION HANDLER TO EXP ENVI HANDLER

typedef struct __DioCtrlDurHand2DioCtrlMsg DioCtrlDurHand2DioCtrlMsg;
typedef struct __DioCtrlDurHand2DioCtrlMsgItem DioCtrlDurHand2DioCtrlMsgItem;
typedef unsigned int DioCtrlDurHand2DioCtrlMsgType;
typedef unsigned int DioCtrlDurHand2DioCtrlMsgAdditional;


#define DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_STRING_LENGTH					100

#define DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_NULL							0
#define DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MIN		1
#define DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MAX		2
#define DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT				3



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "../DioCtrlData/DioCtrlComponentTypes.h"

struct __DioCtrlDurHand2DioCtrlMsgItem
{
	TimeStamp 								msg_time;		
	DioCtrlDurHand2DioCtrlMsgType		msg_type;
	DioCtrlInputCompNum						comp_num;
	DioCtrlDurHand2DioCtrlMsgAdditional	additional_data;
};

struct __DioCtrlDurHand2DioCtrlMsg		
{
	DioCtrlDurHand2DioCtrlMsgItem		buff[DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_dio_ctrl_dur_hand_2_dio_ctrl_msg_type_string(DioCtrlDurHand2DioCtrlMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
DioCtrlDurHand2DioCtrlMsg* allocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(DioCtrlDurHand2DioCtrlMsg* msg_buffer);
DioCtrlDurHand2DioCtrlMsg* deallocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(DioCtrlDurHand2DioCtrlMsg* msg_buffer);
bool write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(DioCtrlDurHand2DioCtrlMsg* msg_buffer, TimeStamp msg_time, DioCtrlDurHand2DioCtrlMsgType msg_type, DioCtrlCompNum comp_num, DioCtrlDurHand2DioCtrlMsgAdditional additional_data);
bool get_next_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer_item(DioCtrlDurHand2DioCtrlMsg* msg_buffer, DioCtrlDurHand2DioCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
