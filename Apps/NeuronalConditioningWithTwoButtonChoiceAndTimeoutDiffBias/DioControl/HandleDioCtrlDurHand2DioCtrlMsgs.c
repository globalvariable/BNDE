#include "HandleDioCtrlDurHand2DioCtrlMsgs.h"


bool handle_dio_ctrl_dur_handler_to_dio_control_msg(DioCtrlData *dio_ctrl_data, TimeStamp current_time, DioCtrlDurHand2DioCtrlMsg *msgs_dio_ctrl_dur_hand_2_dio_ctrl, DioCtrl2ExpCtrlMsg *msgs_dio_ctrl_2_exp_ctrl, DioCtrlParadigmRobotReach *dio_ctrl_paradigm)
{
	bool has_response;
	DioCtrlDurHand2DioCtrlMsgItem msg_item;
	char str_dio_ctrl_dur_msg[DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_STRING_LENGTH];
	bool timer_cancellation_required;
	while (get_next_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer_item(msgs_dio_ctrl_dur_hand_2_dio_ctrl, &msg_item))
	{
		get_dio_ctrl_dur_hand_2_dio_ctrl_msg_type_string(msg_item.msg_type, str_dio_ctrl_dur_msg);
//		print_message(INFO_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", str_dio_ctrl_dur_msg);
		switch (msg_item.msg_type)
		{
			case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MIN:	
				switch (msg_item.comp_num)
				{
					case IR_BEAM_IDX_IN_DIO_CTRL_DATA:
						if (! time_out_success_for_input_comp(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]), &has_response))
							return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "time_out_success_for_input_comp().");
						if (has_response)
						{
//							print_message(INFO_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "IR_BEAM_IDX_IN_DIO_CTRL_DATA RESPONSE");
							if (! write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, current_time, DIO_CTRL_2_EXP_CTRL_MSG_START_TRIAL_REQUEST, 0))
								return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");
						} 
						break;			
					case RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA:
						if (! time_out_success_for_input_comp(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &has_response))
							return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "min_time_out_for_input_comp().");
						if (has_response)
						{
//							print_message(INFO_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA RESPONSE");
							if (! write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, current_time, DIO_CTRL_2_EXP_CTRL_MSG_RESTRAIN_RELEASE_REQ, 0))
								return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");

						} 
						 break;	
					case LEFT_LEVER_IDX_IN_DIO_CTRL_DATA:
						if (! time_out_success_for_input_comp(&(dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA]), &has_response))
							return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "min_time_out_for_input_comp().");
						if (has_response)
						{
//							print_message(INFO_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "LEFT_LEVER_IDX_IN_DIO_CTRL_DATA RESPONSE");

							if (dio_ctrl_paradigm->selected_target_led_component_list_idx == 0)
							{
								if (! write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, current_time, DIO_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST, 0))
									return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");

							}
							else
							{
								if (! write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, current_time, DIO_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST, 0))
									return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");					

							}
						} 

						 break;	

					case RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA:
						if (! time_out_success_for_input_comp(&(dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA]), &has_response))
							return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "min_time_out_for_input_comp().");
						if (has_response)
						{
//							print_message(INFO_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA RESPONSE");

							if (dio_ctrl_paradigm->selected_target_led_component_list_idx == 1)
							{
								if (! write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, current_time, DIO_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST, 0))
									return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");

							}
							else
							{
								if (! write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, current_time, DIO_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST, 0))
									return print_message(ERROR_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");					

							}
						} 
						break;	
				
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "switch (msg_item.inp_comp_num)");	
				}
				break;
			case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_INPUT_TIMEOUT_FOR_MAX:	
				switch (msg_item.comp_num)
				{
					case IR_BEAM_IDX_IN_DIO_CTRL_DATA:
						reset_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]), &timer_cancellation_required);
						if (timer_cancellation_required)
						{
							// not required to cancel timer here. it cancels itself when there is a timeout.	
						}
						break;			
					case RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA:
						reset_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &timer_cancellation_required);
						{
							// not required to cancel timer here. it cancels itself when there is a timeout.	
						}
						break;
					case LEFT_LEVER_IDX_IN_DIO_CTRL_DATA:
						reset_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]), &timer_cancellation_required);
						if (timer_cancellation_required)
						{
							// not required to cancel timer here. it cancels itself when there is a timeout.	
						}
						break;			
					case RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA:
						reset_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &timer_cancellation_required);
						{
							// not required to cancel timer here. it cancels itself when there is a timeout.	
						}
						break;							
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "switch (msg_item.inp_comp_num)");
				}
				break;
			case DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT:
				switch (msg_item.comp_num)
				{
					case VALVE_IDX_IN_DIO_CTRL_DATA:
						switch(dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status)
						{
							case DIO_CTRL_COMP_STATUS_LOW:
								break;  // do nothing, it is already set low before (maybe by handle_exp_ctrl_2_dio_ctrl)
							case DIO_CTRL_COMP_STATUS_HIGH:
								dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
								break;
							default:
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT & switch(dio_ctrl_data->outp_comps[VALVE_IDX_IN_DIO_CTRL_DATA].status) - default");
						}
						break;			
					case BUZZER_IDX_IN_DIO_CTRL_DATA:
						switch(dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status)
						{
							case DIO_CTRL_COMP_STATUS_LOW:
								break;  // do nothing, it is already set low before (maybe by handle_exp_ctrl_2_dio_ctrl)
							case DIO_CTRL_COMP_STATUS_HIGH:
								dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
								break;
							default:
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT & switch(dio_ctrl_data->outp_comps[BUZZER_IDX_IN_DIO_CTRL_DATA].status) - default");
						}
						break;	
					case LEFT_LED_IDX_IN_DIO_CTRL_DATA:
						switch(dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status)
						{
							case DIO_CTRL_COMP_STATUS_LOW:
								break;  // do nothing, it is already set low before (maybe by handle_exp_ctrl_2_dio_ctrl)
							case DIO_CTRL_COMP_STATUS_HIGH:
								dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
								break;
							default:
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT & switch(dio_ctrl_data->outp_comps[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
						}
						break;	
					case RIGHT_LED_IDX_IN_DIO_CTRL_DATA:
						switch(dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status)
						{
							case DIO_CTRL_COMP_STATUS_LOW:
								break;  // do nothing, it is already set low before (maybe by handle_exp_ctrl_2_dio_ctrl)
							case DIO_CTRL_COMP_STATUS_HIGH:
								dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
								break;
							default:
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT & switch(dio_ctrl_data->outp_comps[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
						}
						break;	
					case GUIDE_LED_IDX_IN_DIO_CTRL_DATA:
						switch(dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status)
						{
							case DIO_CTRL_COMP_STATUS_LOW:
								break;  // do nothing, it is already set low before (maybe by handle_exp_ctrl_2_dio_ctrl)
							case DIO_CTRL_COMP_STATUS_HIGH:
								dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
								break;
							default:
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT & switch(dio_ctrl_data->outp_comps[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
						}
						break;	
					case LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA:
						switch(dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status)
						{
							case DIO_CTRL_COMP_STATUS_LOW:
								break;  // do nothing, it is already set low before (maybe by handle_exp_ctrl_2_dio_ctrl)
							case DIO_CTRL_COMP_STATUS_HIGH:
								dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
								break;
							default:
								return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSG_OUTPUT_TIMEOUT & switch(dio_ctrl_data->outp_comps[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status) - default");
						}
						break;	
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", "switch (msg_item.inp_comp_num)");
				}
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleDioCtrlDurHand2DioCtrlMsgs", "handle_dio_ctrl_dur_handler_to_dio_control_msg", str_dio_ctrl_dur_msg);
		}
	}
	return TRUE;
}
