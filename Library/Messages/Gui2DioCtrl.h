#ifndef GUI_2_DIO_CTRL_H
#define GUI_2_DIO_CTRL_H

//  MESSAGES FROM EXP ENVI HANDLER GUI TO EXP ENVI HANDLER

typedef struct __Gui2DioCtrlMsg Gui2DioCtrlMsg;
typedef struct __Gui2DioCtrlMsgItem Gui2DioCtrlMsgItem;
typedef unsigned int Gui2DioCtrlMsgType;
typedef unsigned int Gui2DioCtrlMsgAdditional;


#define GUI_2_DIO_CTRL_MSG_STRING_LENGTH		50

#define GUI_2_DIO_CTRL_MSG_NULL					0


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __Gui2DioCtrlMsgItem
{
	TimeStamp 								msg_time;		
	Gui2DioCtrlMsgType					msg_type;
	Gui2DioCtrlMsgAdditional				additional_data;
};

struct __Gui2DioCtrlMsg		// Requests to ExpControllers
{
	Gui2DioCtrlMsgItem		buff[GUI_2_DIO_CTRL_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

Gui2DioCtrlMsg* allocate_gui_2_dio_ctrl_msg_buffer(Gui2DioCtrlMsg* msg_buffer);
Gui2DioCtrlMsg* deallocate_gui_2_dio_ctrl_msg_buffer(Gui2DioCtrlMsg* msg_buffer);
bool get_gui_2_dio_ctrl_msg_type_string(Gui2DioCtrlMsgType msg_type, char *str);
bool write_to_gui_2_dio_ctrl_msg_buffer(Gui2DioCtrlMsg* msg_buffer, TimeStamp msg_time, Gui2DioCtrlMsgType msg_type, Gui2DioCtrlMsgAdditional additional_data);
bool get_next_gui_2_dio_ctrl_msg_buffer_item(Gui2DioCtrlMsg* msg_buffer, Gui2DioCtrlMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
