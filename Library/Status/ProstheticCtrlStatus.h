#ifndef PROSTHETIC_CTRL_STATUS_H
#define PROSTHETIC_CTRL_STATUS_H


typedef unsigned int ProstheticCtrlStatus;   // !!!ONLY!!! prosthetic_ctrl_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	PROSTHETIC_CTRL_STATUS_MAX_STRING_LENGTH							100

#define	PROSTHETIC_CTRL_STATUS_NULL											0
#define	PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL								1
#define	PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT						2
#define	PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL						3
#define	PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT					4
#define	PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT						5
#define	PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT					6
#define	PROSTHETIC_CTRL_STATUS_DISABLED										7

bool get_prosthetic_ctrl_status_type_string(ProstheticCtrlStatus prosthetic_ctrl_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
