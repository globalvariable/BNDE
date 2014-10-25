#ifndef TRIAL_DUR_STATUS_H
#define TRIAL_DUR_STATUS_H


typedef unsigned int ExpDurationStatus;   // !!!ONLY!!! trial_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	TRIAL_DUR_STATUS_MAX_STRING_LENGTH			50

#define	TRIAL_DUR_STATUS_NULL							0
#define	TRIAL_DUR_STATUS_HANDLING_ENABLED				1	// FOR IN_TRIAL OR IN_REFRACOTRY STATUS OF TRIAL_STATUS
#define	TRIAL_DUR_STATUS_HANDLING_DISABLED			2	// FOR TRIALS_DISABLED OR TRIALS_AVAILABLE STATUS OF TRIAL_STATUS


bool get_trial_dur_status_type_string(ExpDurationStatus trial_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
