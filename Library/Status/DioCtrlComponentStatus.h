
#ifndef DIO_CTRL_COMPONENT_STATUS_H
#define DIO_CTRL_COMPONENT_STATUS_H


typedef unsigned int DioCtrlCompStatus;   

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	DIO_CTRL_COMP_STATUS_MAX_STRING_LENGTH			100

#define	DIO_CTRL_COMP_STATUS_NULL						0
#define	DIO_CTRL_COMP_STATUS_LOW						1
#define	DIO_CTRL_COMP_STATUS_LOW_SUCCESS				2
#define	DIO_CTRL_COMP_STATUS_HIGH						3
#define	DIO_CTRL_COMP_STATUS_HIGH_SUCCESS			4
#define	DIO_CTRL_COMP_STATUS_READY_FOR_SWITCHING	5


bool get_dio_ctrl_comp_status_type_string(DioCtrlCompStatus dio_ctrl_comp_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

#endif
