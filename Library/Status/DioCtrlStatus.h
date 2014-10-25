#ifndef DIO_CTRL_STATUS_H
#define DIO_CTRL_STATUS_H


typedef unsigned int DioCtrlStatus;   // !!!ONLY!!! dio_ctrl_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	DIO_CTRL_STATUS_MAX_STRING_LENGTH			100

#define	DIO_CTRL_STATUS_NULL							0
#define	DIO_CTRL_STATUS_COMPONENTS_UNAVAILABLE	1
#define	DIO_CTRL_STATUS_COMPONENTS_AVAILABLE		2



bool get_dio_ctrl_status_type_string(DioCtrlStatus dio_ctrl_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
