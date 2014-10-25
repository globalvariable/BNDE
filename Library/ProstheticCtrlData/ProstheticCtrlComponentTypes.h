#ifndef PROSTHETIC_CTRL_COMPONENT_TYPES_H
#define PROSTHETIC_CTRL_COMPONENT_TYPES_H


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>


typedef unsigned int ProstheticCtrlCompNum;

#define	PROSTHETIC_CTRL_COMPONENT_NUM_NULL						0xFFFFFFFF			


typedef unsigned int ProstheticCtrlCompType;					

#define	PROSTHETIC_CTRL_COMPONENT_TYPE_MAX_STRING_LENGTH		100

#define	PROSTHETIC_CTRL_COMPONENT_NULL								0
#define	PROSTHETIC_CTRL_COMPONENT_1D_ACTUATOR					1	
#define	PROSTHETIC_CTRL_COMPONENT_2D_ACTUATOR					2	
#define	PROSTHETIC_CTRL_COMPONENT_3D_ACTUATOR					3	


#define	PROSTHETIC_CTRL_COMPONENT_SHOULDER_FLEXOR				31
#define	PROSTHETIC_CTRL_COMPONENT_SHOULDER_ROTATOR				32
#define	PROSTHETIC_CTRL_COMPONENT_ELBOW_FLEXOR					33
#define	PROSTHETIC_CTRL_COMPONENT_WRIST_ROTATOR					34
#define	PROSTHETIC_CTRL_COMPONENT_WRIST_FLEXOR					35


bool get_prosthetic_ctrl_component_type_string(ProstheticCtrlCompType prosthetic_ctrl_comp_type, char *str);

#endif
