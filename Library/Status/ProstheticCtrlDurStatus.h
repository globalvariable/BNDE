#ifndef PROSTHETIC_CTRL_DUR_STATUS_H
#define PROSTHETIC_CTRL_DUR_STATUS_H


#include <stdbool.h>
#include "../System/TimeStamp/TimeStamp.h"

#define	PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION		0
#define	PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH				1
#define	PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION				2
#define	PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION						3
#define	PROSTHETIC_CTRL_DUR_STATUS_NUM_OF_ITEMS							4


typedef struct 
{
	bool 		active;
	TimeStamp	schedule;
} ProstheticCtrlScheduleItem; 

typedef struct 
{
	ProstheticCtrlScheduleItem	items[PROSTHETIC_CTRL_DUR_STATUS_NUM_OF_ITEMS];
} ProstheticCtrlSchedule;


#endif
