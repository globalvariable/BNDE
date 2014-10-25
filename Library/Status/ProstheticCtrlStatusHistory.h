#ifndef PROSTHETIC_CTRL_STATUS_HISTORY_H
#define PROSTHETIC_CTRL_STATUS_HISTORY_H


typedef struct __ProstheticCtrlStatusHistoryItem ProstheticCtrlStatusHistoryItem;
typedef struct __ProstheticCtrlStatusHistory ProstheticCtrlStatusHistory;

#include "ProstheticCtrlStatus.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ProstheticCtrlStatusHistoryItem
{
	TimeStamp			time;
	ProstheticCtrlStatus			new_status;
};

struct __ProstheticCtrlStatusHistory
{
	ProstheticCtrlStatusHistoryItem 	*history;
	unsigned int 			buff_write_idx;  
	unsigned int 			buff_read_idx;  
	unsigned int 			buffer_size;
};

ProstheticCtrlStatusHistory* allocate_prosthetic_ctrl_status_history(ProstheticCtrlStatusHistory* hist, unsigned int buffer_size); 
ProstheticCtrlStatusHistory* deallocate_prosthetic_ctrl_status_history(ProstheticCtrlStatusHistory* hist); 
bool write_to_prosthetic_ctrl_status_history(ProstheticCtrlStatusHistory* hist, TimeStamp time, ProstheticCtrlStatus new_status);
bool get_next_prosthetic_ctrl_status_history_item(ProstheticCtrlStatusHistory* hist, ProstheticCtrlStatusHistoryItem *item);	



#endif
