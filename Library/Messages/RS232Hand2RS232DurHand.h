#ifndef RS232_HAND_2_RS232_DUR_HAND_H
#define RS232_HAND_2_RS232_DUR_HAND_H

//  MESSAGES FROM RS232 HANDLER TO RS232 DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"


typedef struct __RS232Hand2RS232DurHandMsg RS232Hand2RS232DurHandMsg;
typedef struct __RS232Hand2RS232DurHandMsgItem RS232Hand2RS232DurHandMsgItem;
typedef unsigned int RS232Hand2RS232DurHandMsgType;
typedef TimeStamp RS232Hand2RS232DurHandMsgAdditional;


#define RS232_HAND_2_RS232_DUR_HAND_MSG_STRING_LENGTH					100

#define RS232_HAND_2_RS232_DUR_HAND_MSG_NULL							0
#define RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_TX_TIMER				1
#define RS232_HAND_2_RS232_DUR_HAND_MSG_DISABLE_TX_TIMER				2
#define RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_RX_TIMER				3
#define RS232_HAND_2_RS232_DUR_HAND_MSG_DISABLE_RX_TIMER				4

 




struct __RS232Hand2RS232DurHandMsgItem
{
	TimeStamp 								msg_time;		
	RS232Hand2RS232DurHandMsgType			msg_type;
	unsigned int 								component_num;
	RS232Hand2RS232DurHandMsgAdditional		additional_data;
};

struct __RS232Hand2RS232DurHandMsg		// Requests to RS232Controllers
{
	RS232Hand2RS232DurHandMsgItem		buff[RS232_HAND_2_RS232_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_rs232_hand_2_rs232_dur_hand_msg_type_string(RS232Hand2RS232DurHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
RS232Hand2RS232DurHandMsg* allocate_rs232_hand_2_rs232_dur_hand_msg_buffer(RS232Hand2RS232DurHandMsg* msg_buffer);
RS232Hand2RS232DurHandMsg* deallocate_rs232_hand_2_rs232_dur_hand_msg_buffer(RS232Hand2RS232DurHandMsg* msg_buffer);
bool write_to_rs232_hand_2_rs232_dur_hand_msg_buffer(RS232Hand2RS232DurHandMsg* msg_buffer, TimeStamp msg_time, RS232Hand2RS232DurHandMsgType msg_type, unsigned int component_num, RS232Hand2RS232DurHandMsgAdditional additional_data);
bool get_next_rs232_hand_2_rs232_dur_hand_msg_buffer_item(RS232Hand2RS232DurHandMsg* msg_buffer, RS232Hand2RS232DurHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
