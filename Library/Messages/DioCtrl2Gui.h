#ifndef DIO_CTRL_2_GUI_H
#define DIO_CTRL_2_GUI_H

//  MESSAGES FROM TRIAL HANDLER TO TRIAL HANDLER GUI

typedef struct __DioCtrl2GuiMsg DioCtrl2GuiMsg;
typedef struct __DioCtrl2GuiMsgItem DioCtrl2GuiMsgItem;
typedef unsigned int DioCtrl2GuiMsgType;
typedef unsigned int DioCtrl2GuiMsgAdditional;


#define DIO_CTRL_2_GUI_MSG_STRING_LENGTH		60

#define DIO_CTRL_2_GUI_MSG_NULL									0
#define DIO_CTRL_2_GUI_MSG_START_RECORDING					1   
#define DIO_CTRL_2_GUI_MSG_STOP_RECORDING					2   
#define DIO_CTRL_2_GUI_MSG_CANCEL_RECORDING					3   


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __DioCtrl2GuiMsgItem
{
	TimeStamp 								msg_time;		
	DioCtrl2GuiMsgType						msg_type;
	DioCtrl2GuiMsgAdditional					additional_data;
};

struct __DioCtrl2GuiMsg		// Requests to ExpControllers
{
	DioCtrl2GuiMsgItem		buff[DIO_CTRL_2_GUI_MSG_BUFF_SIZE];
	unsigned int				buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int				buff_read_idx;	// only one request handler can edit this read index
};

DioCtrl2GuiMsg* allocate_dio_ctrl_2_gui_msg_buffer(DioCtrl2GuiMsg* msg_buffer);
DioCtrl2GuiMsg* deallocate_dio_ctrl_2_gui_msg_buffer(DioCtrl2GuiMsg* msg_buffer);
bool get_dio_ctrl_2_gui_msg_type_string(DioCtrl2GuiMsgType msg_type, char *str);
bool write_to_dio_ctrl_2_gui_msg_buffer(DioCtrl2GuiMsg* msg_buffer, TimeStamp msg_time, DioCtrl2GuiMsgType msg_type, DioCtrl2GuiMsgAdditional additional_data);
bool get_next_dio_ctrl_2_gui_msg_buffer_item(DioCtrl2GuiMsg* msg_buffer, DioCtrl2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
