#include "DioCtrlComponentTypes.h"


bool get_dio_ctrl_input_component_type_string(DioCtrlInputCompType component_type, char *str)
{
	switch (component_type)
	{
		case DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE");
			return TRUE;	
		case DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER");
			return TRUE;	
		case DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER");
			return TRUE;	
		case DIO_CTRL_INPUT_COMPONENT_NOSE_RETRACT_IR:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_NOSE_RETRACT_IR");
			return TRUE;
		case DIO_CTRL_INPUT_COMPONENT_LEVER:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_LEVER");
			return TRUE;
		case DIO_CTRL_INPUT_COMPONENT_RESTRAIN_SWITCH:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_RESTRAIN_SWITCH");
			return TRUE;
		case DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER_RELEASE:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER_RELEASE");
			return TRUE;
		case DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER_RELEASE:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER_RELEASE");
			return TRUE;
/////////////////////////		
		default:
 			strcpy(str, "DIO_CTRL_INPUT_COMPONENT_INVALID");
			return FALSE;
	}
}

bool get_dio_ctrl_output_component_type_string(DioCtrlOutputCompType component_type, char *str)
{
	switch (component_type)
	{
		case DIO_CTRL_OUTPUT_COMPONENT_VALVE_CENTER:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_VALVE_CENTER");
			return TRUE;	
		case DIO_CTRL_OUTPUT_COMPONENT_BUZZER:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_BUZZER");
			return TRUE;	
		case DIO_CTRL_OUTPUT_COMPONENT_LEFT_TARGET_LED:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_LEFT_TARGET_LED");
			return TRUE;	
		case DIO_CTRL_OUTPUT_COMPONENT_RIGHT_TARGET_LED:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_RIGHT_TARGET_LED");
			return TRUE;	
		case DIO_CTRL_OUTPUT_COMPONENT_GUIDE_LED:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_GUIDE_LED");
			return TRUE;
		case DIO_CTRL_OUTPUT_COMPONENT_LEVER_SOLENOID:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_LEVER_SOLENOID");
			return TRUE;	
		case DIO_CTRL_OUTPUT_COMPONENT_TRIAL_AVAILABLE_LED:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_TRIAL_AVAILABLE_LED");
			return TRUE;	
		case DIO_CTRL_OUTPUT_COMPONENT_GET_READY_LED:
			if (str != NULL)
				strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_GET_READY_LED");
			return TRUE;	

/////////////////////////	
	
		default:
 			strcpy(str, "DIO_CTRL_OUTPUT_COMPONENT_INVALID");
			return FALSE;
	}
}
