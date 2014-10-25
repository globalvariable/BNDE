#include "ProstheticCtrlComponentTypes.h"


bool get_prosthetic_ctrl_component_type_string(ProstheticCtrlCompType prosthetic_ctrl_comp_type, char *str)
{
	switch (prosthetic_ctrl_comp_type)
	{
		case PROSTHETIC_CTRL_COMPONENT_1D_ACTUATOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_1D_ACTUATOR");
			return TRUE;	
		case PROSTHETIC_CTRL_COMPONENT_2D_ACTUATOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_2D_ACTUATOR");
			return TRUE;	
		case PROSTHETIC_CTRL_COMPONENT_3D_ACTUATOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_3D_ACTUATOR");
			return TRUE;		

//////////////
		case PROSTHETIC_CTRL_COMPONENT_SHOULDER_FLEXOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_SHOULDER_FLEXOR");
			return TRUE;	
		case PROSTHETIC_CTRL_COMPONENT_SHOULDER_ROTATOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_SHOULDER_ROTATOR");
			return TRUE;		
		case PROSTHETIC_CTRL_COMPONENT_ELBOW_FLEXOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_ELBOW_FLEXOR");
			return TRUE;	
		case PROSTHETIC_CTRL_COMPONENT_WRIST_ROTATOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_WRIST_ROTATOR");
			return TRUE;	
		case PROSTHETIC_CTRL_COMPONENT_WRIST_FLEXOR:
			if (str != NULL)
				strcpy(str, "PROSTHETIC_CTRL_COMPONENT_WRIST_FLEXOR");
			return TRUE;	
/////////////////////////		
		case PROSTHETIC_CTRL_COMPONENT_NULL:
 			strcpy(str, "PROSTHETIC_CTRL_COMPONENT_NULL");
			return FALSE;
		default:
 			strcpy(str, "PROSTHETIC_CTRL_COMPONENT_INVALID");
			return FALSE;
	}
}
