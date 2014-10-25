#ifndef RS232_DUR_HAND_2_RS232_HAND_H
#define RS232_DUR_HAND_2_RS232_HAND_H

//  MESSAGES FROM RS232 DURATION HANDLER TO RS232 HANDLER

typedef struct __RS232DurHand2RS232HandMsg RS232DurHand2RS232HandMsg;
typedef struct __RS232DurHand2RS232HandMsgItem RS232DurHand2RS232HandMsgItem;
typedef unsigned int RS232DurHand2RS232HandMsgType;
typedef unsigned int RS232DurHand2RS232HandMsgAdditional;


#define RS232_DUR_HAND_2_RS232_HAND_MSG_STRING_LENGTH					100

#define RS232_DUR_HAND_2_RS232_HAND_MSG_NULL							0
#define RS232_DUR_HAND_2_RS232_HAND_MSG_TX_TIMEOUT					1
#define RS232_DUR_HAND_2_RS232_HAND_MSG_RX_TIMEOUT					2
#define RS232_DUR_HAND_2_RS232_HAND_MSG_EMERGENCY_EXIT				3




#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __RS232DurHand2RS232HandMsgItem
{
	TimeStamp 								msg_time;		
	RS232DurHand2RS232HandMsgType				msg_type;
	unsigned int 								component_num;
	RS232DurHand2RS232HandMsgAdditional			additional_data;
};

struct __RS232DurHand2RS232HandMsg		// Requests to RS232Controllers
{
	RS232DurHand2RS232HandMsgItem		buff[RS232_DUR_HAND_2_RS232_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_rs232_dur_hand_2_rs232_hand_msg_type_string(RS232DurHand2RS232HandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
RS232DurHand2RS232HandMsg* allocate_rs232_dur_hand_2_rs232_hand_msg_buffer(RS232DurHand2RS232HandMsg* msg_buffer);
RS232DurHand2RS232HandMsg* deallocate_rs232_dur_hand_2_rs232_hand_msg_buffer(RS232DurHand2RS232HandMsg* msg_buffer);
bool write_to_rs232_dur_hand_2_rs232_hand_msg_buffer(RS232DurHand2RS232HandMsg* msg_buffer, TimeStamp msg_time, RS232DurHand2RS232HandMsgType msg_type, unsigned int component_num, RS232DurHand2RS232HandMsgAdditional additional_data);
bool get_next_rs232_dur_hand_2_rs232_hand_msg_buffer_item(RS232DurHand2RS232HandMsg* msg_buffer, RS232DurHand2RS232HandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
