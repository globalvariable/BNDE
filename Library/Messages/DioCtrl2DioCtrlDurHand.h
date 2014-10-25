#ifndef DIO_CTRL_2_DIO_CTRL_DUR_HAND_H
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_H

//  MESSAGES FROM EXP ENVI HANDLER TO EXP ENVI DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "../DioCtrlData/DioCtrlComponentTypes.h"

typedef struct __DioCtrl2DioCtrlDurHandMsg DioCtrl2DioCtrlDurHandMsg;
typedef struct __DioCtrl2DioCtrlDurHandMsgItem DioCtrl2DioCtrlDurHandMsgItem;
typedef unsigned int DioCtrl2DioCtrlDurHandMsgType;
typedef TimeStamp DioCtrl2DioCtrlDurHandMsgAdditional;


#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_STRING_LENGTH					100

#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_NULL								0
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER				1
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER			2
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER			3
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER			4
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER				5     // "send current time" to cancel out the timer which is set before 
#define DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER				6


struct __DioCtrl2DioCtrlDurHandMsgItem
{
	TimeStamp 								msg_time;		
	DioCtrl2DioCtrlDurHandMsgType		msg_type;
	DioCtrlInputCompNum						comp_num;
	DioCtrl2DioCtrlDurHandMsgAdditional	additional_data;		// min time
};

struct __DioCtrl2DioCtrlDurHandMsg		
{
	DioCtrl2DioCtrlDurHandMsgItem		buff[DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_dio_ctrl_2_dio_ctrl_dur_hand_msg_type_string(DioCtrl2DioCtrlDurHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
DioCtrl2DioCtrlDurHandMsg* allocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(DioCtrl2DioCtrlDurHandMsg* msg_buffer);
DioCtrl2DioCtrlDurHandMsg* deallocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(DioCtrl2DioCtrlDurHandMsg* msg_buffer);
bool write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(DioCtrl2DioCtrlDurHandMsg* msg_buffer, TimeStamp msg_time, DioCtrl2DioCtrlDurHandMsgType msg_type, DioCtrlCompNum comp_num, DioCtrl2DioCtrlDurHandMsgAdditional additional_data);
bool get_next_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer_item(DioCtrl2DioCtrlDurHandMsg* msg_buffer, DioCtrl2DioCtrlDurHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
