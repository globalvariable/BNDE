#include "HandleDioCtrl2DioCtrlDurHandMsgs.h"

bool handle_dio_control_to_dio_ctrl_dur_handler_msg(DioCtrlDurationStatus *dio_ctrl_inputs_min_dur_status, DioCtrlDurationStatus *dio_ctrl_inputs_max_dur_status, TimeStamp current_time, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, TimeStamp *inputs_handling_end_time_min, TimeStamp *inputs_handling_end_time_max, DioCtrlDurationStatus *dio_ctrl_outputs_dur_status, TimeStamp *outputs_handling_end_time)
{
	DioCtrl2DioCtrlDurHandMsgItem msg_item;
	char str_dio_ctrl_msg[DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_STRING_LENGTH];
	char str_dio_ctrl_dur_status[DIO_CTRL_DUR_STATUS_MAX_STRING_LENGTH];
	while (get_next_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer_item(msgs_dio_ctrl_2_dio_ctrl_dur_hand, &msg_item))
	{
		get_dio_ctrl_2_dio_ctrl_dur_hand_msg_type_string(msg_item.msg_type, str_dio_ctrl_msg);
//		print_message(INFO_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_msg);
		switch (msg_item.msg_type)
		{
			case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER:	
				switch (msg_item.comp_num)
				{
					case IR_BEAM_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "IR_BEAM_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[IR_BEAM_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			
					case RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case LEFT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	


					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER:	
				switch (msg_item.comp_num)
				{
					case IR_BEAM_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			
					case RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case LEFT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_min_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
		
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER:	
				switch (msg_item.comp_num)
				{
					case IR_BEAM_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "IR_BEAM_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[IR_BEAM_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			

					case RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	

					case LEFT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;		
					case RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);   
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
			
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER:	
				switch (msg_item.comp_num)
				{
					case IR_BEAM_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[IR_BEAM_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			

					case RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case LEFT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	

					case RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_inputs_max_dur_status[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	

	
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER:	 // "send current time" to cancel out the timer which is set before 
				switch (msg_item.comp_num)
				{
					case VALVE_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "VALVE_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[VALVE_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								printf("VALVE_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			
					case BUZZER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "BUZZER_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[BUZZER_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								printf("BUZZER_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case LEFT_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "LEFT_LED_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[LEFT_LED_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								printf("LEFT_LED_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case RIGHT_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "RIGHT_LED_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[RIGHT_LED_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								printf("RIGHT_LED_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case GUIDE_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "GUIDE_LED_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[GUIDE_LED_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								printf("GUIDE_LED_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			
					case LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case GET_READY_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "GET_READY_LED_IDX_IN_DIO_CTRL_DATA");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
								outputs_handling_end_time[GET_READY_LED_IDX_IN_DIO_CTRL_DATA] = msg_item.additional_data;
								dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status); 
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER:	
				switch (msg_item.comp_num)
				{
					case VALVE_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for VALVE_IDX_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								printf("VALVE_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[VALVE_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;			
					case BUZZER_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for BUZZER_IDX_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								printf("BUZZER_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[BUZZER_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
					case LEFT_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for LEFT_LED_IDX_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								printf("LEFT_LED_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[LEFT_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;		
					case RIGHT_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for RIGHT_LED_IDX_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								printf("RIGHT_LED_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[RIGHT_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;		
					case GUIDE_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for GUIDE_LED_IDX_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								printf("GUIDE_LED_IDX_IN_DIO_CTRL_DATA\n");
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[GUIDE_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for LEVER_SOLENOID_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					case GET_READY_LED_IDX_IN_DIO_CTRL_DATA:
						switch (dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA])
						{
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_ON:
								dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA] = DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF;
								break;			
							case DIO_CTRL_OUTPUTS_DUR_STATUS_TIMER_OFF:
//								print_message(WARNING_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "Unnecessary Cancel Output Timer for GET_READY_LED_IDX_IN_DIO_CTRL_DATA");
								break; // do nothing
							default:
								get_dio_ctrl_dur_status_type_string(dio_ctrl_outputs_dur_status[GET_READY_LED_IDX_IN_DIO_CTRL_DATA], str_dio_ctrl_dur_status);  
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_dur_status);
						}
						 break;	
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleDioCtrl2DioCtrlDurHandMsgs", "handle_dio_control_to_dio_ctrl_dur_handler_msg", str_dio_ctrl_msg);
		}
	}
	return TRUE;
}
