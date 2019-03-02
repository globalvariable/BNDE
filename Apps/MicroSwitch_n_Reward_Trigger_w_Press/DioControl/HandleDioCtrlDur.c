#include "HandleDioCtrlDur.h"


bool handle_dio_control_duration(DioCtrlDurationStatus *dio_ctrl_inputs_min_dur_status, DioCtrlDurationStatus *dio_ctrl_inputs_max_dur_status, TimeStamp current_time, TimeStamp *inputs_handling_end_time_min, TimeStamp *inputs_handling_end_time_max, unsigned int num_of_input_components, DioCtrlDurHand2DioCtrlMsg *msgs_dio_ctrl_dur_hand_2_dio_ctrl, unsigned int num_of_output_components, DioCtrlDurationStatus *dio_ctrl_outputs_dur_status, TimeStamp *outputs_handling_end_time)
{
	char str_dur_status[DIO_CTRL_DUR_STATUS_MAX_STRING_LENGTH];
	unsigned int i;
	for (i = 0; i < num_of_input_components; i ++)
	{
		switch (dio_ctrl_inputs_min_dur_status[i])
		{
			case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
				break;	// do nothing
			case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
				if (current_time >= inputs_handling_end_time_min[i])
				{
					dio_ctrl_inputs_min_dur_status[i] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF;	
					if (! write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(msgs_dio_ctrl_dur_hand_2_dio_ctrl, current_time, DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MIN, i, 0))
						return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDur", "handle_dio_control_duration", "! write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer()."); 
				}	
				break;	// do nothing
			default: 
				get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[i], str_dur_status);  
				return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDur", "handle_dio_control_duration", str_dur_status);		
		}
		switch (dio_ctrl_inputs_max_dur_status[i])
		{
			case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
				break;	// do nothing
			case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
				if (current_time >= inputs_handling_end_time_max[i])
				{
					dio_ctrl_inputs_max_dur_status[i] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF;	
					if (! write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(msgs_dio_ctrl_dur_hand_2_dio_ctrl, current_time, DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MAX, i, 0))
						return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDur", "handle_dio_control_duration", "! write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer()."); 
				}	
				break;	// do nothing
			default: 
				get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[i], str_dur_status);  
				return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDur", "handle_dio_control_duration", str_dur_status);
		}
	}

	for (i = 0; i < num_of_output_components; i ++)
	{
		switch (dio_ctrl_outputs_dur_status[i])
		{
			case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
				break;	// do nothing
			case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
				if (current_time >= outputs_handling_end_time[i])
				{
					dio_ctrl_outputs_dur_status[i] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;	
					if (! write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(msgs_dio_ctrl_dur_hand_2_dio_ctrl, current_time, DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT, i, 0))
						return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDur", "handle_dio_control_duration", "! write_to_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer()."); 
				}	
				break;	// do nothing
			default: 
				get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[i], str_dur_status);  
				return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDur", "handle_dio_control_duration", str_dur_status);		
		}
	}

	return TRUE;
}
