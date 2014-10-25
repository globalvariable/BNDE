#ifndef TRIAL_STATUS_HISTORY_H
#define TRIAL_STATUS_HISTORY_H


typedef struct __ExpStatusHistoryItem ExpStatusHistoryItem;
typedef struct __ExpStatusHistory ExpStatusHistory;

#include "ExpStatus.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ExpStatusHistoryItem
{
	TimeStamp			time;
	ExpStatus			new_status;
};

struct __ExpStatusHistory
{
	ExpStatusHistoryItem 	*history;
	unsigned int 			buff_write_idx;  
	unsigned int 			buff_read_idx;  
	unsigned int 			buffer_size;
};

ExpStatusHistory* allocate_trial_status_history(ExpStatusHistory* hist, unsigned int buffer_size); 
ExpStatusHistory* deallocate_trial_status_history(ExpStatusHistory* hist); 
bool write_to_trial_status_history(ExpStatusHistory* hist, TimeStamp time, ExpStatus new_status);
bool get_next_trial_status_history_item(ExpStatusHistory* hist, ExpStatusHistoryItem *item);	



#endif
