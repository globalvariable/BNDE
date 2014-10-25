#ifndef DIO_CTRL_DUR_STATUS_H
#define DIO_CTRL_DUR_STATUS_H

typedef unsigned int DioCtrlDurationStatus;

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	DIO_CTRL_DUR_STATUS_MAX_STRING_LENGTH			100
#define	DIO_CTRL_DUR_STATUS_NULL							0
#define	DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON			1
#define	DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF			2
#define	DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON			3
#define	DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF			4
#define	DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON				5
#define	DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF			6


bool get_dio_ctrl_dur_status_type_string(DioCtrlDurationStatus dio_ctrl_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

#endif
