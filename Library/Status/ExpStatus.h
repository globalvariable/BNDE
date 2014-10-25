#ifndef TRIAL_STATUS_H
#define TRIAL_STATUS_H


typedef unsigned int ExpStatus;   // !!!ONLY!!! exp_control can change this. Do not change this without MUTEX if there is multi threading for handling the messages of mov obj, exp envi etc. handlers
typedef struct __ExpStatusEventItem ExpStatusEventItem;
typedef struct __ExpStatusEvents ExpStatusEvents;

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "../Messages/ExpCtrl2NeuralNet.h"

#define	TRIAL_STATUS_MAX_STRING_LENGTH			50

#define	TRIAL_STATUS_NULL							0
#define	TRIAL_STATUS_TRIALS_DISABLED				1
#define	TRIAL_STATUS_IN_TRIAL						2
#define	TRIAL_STATUS_IN_REFRACTORY				3
#define	TRIAL_STATUS_START_TRIAL_AVAILABLE		4
#define	TRIAL_STATUS_GET_READY_TO_START		5
#define	TRIAL_STATUS_WAIT_FOR_LEVER_PRESS		6
#define	TRIAL_STATUS_WAIT_FOR_NOSE_RETRACT	7
#define	TRIAL_STATUS_CUE_LED_ON					8
#define	TRIAL_STATUS_REWARD_AVAILABLE			9
#define	TRIAL_STATUS_ESCAPING					10
#define	TRIAL_STATUS_AFTER_ESCAPING				11

struct __ExpStatusEventItem
{
	TimeStamp	status_start_time;   
	ExpStatus	trial_status;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	unsigned int	selected_robot_target_idx_in_exp_ctrl_paradigm;
};

struct __ExpStatusEvents  // IT IS ESPECIALLY FOR GRAPHS TO INDICATE THE TRIAL STATUS CHANGE TIMES
{
	ExpStatusEventItem	*buff;   
	unsigned int 		buff_write_idx;
	unsigned int 		buffer_size;
	TimeStamp		status_change_latency;   
};

bool get_trial_status_type_string(ExpStatus trial_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

ExpStatusEvents* allocate_trial_status_events_buffer(ExpStatusEvents* trial_status_events, unsigned int buffer_size, TimeStamp status_change_latency);
ExpStatusEvents* deallocate_trial_status_events_buffer(ExpStatusEvents* trial_status_events);
void schedule_trial_status_event(ExpStatusEvents* trial_status_events, TimeStamp trial_status_start_time, ExpCtrl2NeuralNetExpStatusMsgAdd trial_status_change_msg_add);   // it can have multiple readers. so no read_idx defined.
bool get_next_trial_status_events_buffer_item(ExpStatusEvents* trial_status_events, unsigned int *read_idx, ExpStatusEventItem *event_item);
ExpStatusEventItem get_last_trial_status_events_buffer_item(ExpStatusEvents* trial_status_events);
#endif
