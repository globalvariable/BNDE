#ifndef RS232_DUR_STATUS_H
#define RS232_DUR_STATUS_H


typedef unsigned int RS232DurationStatus;   // !!!ONLY!!! trial_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	RS232_DUR_STATUS_MAX_STRING_LENGTH			50

#define	RS232_DUR_STATUS_NULL			0
#define	RS232_DUR_STATUS_TIMER_ON		1	
#define	RS232_DUR_STATUS_TIMER_OFF		2	


bool get_rs232_dur_status_type_string(RS232DurationStatus rs232_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
