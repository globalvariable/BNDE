#include "HandleExpCtrl2DioCtrlMsgs.h"



bool handle_exp_control_to_dio_control_msg(DioCtrlData *dio_ctrl_data, TimeStamp current_time, ExpCtrl2DioCtrlMsg *msgs_exp_ctrl_2_dio_ctrl, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, DioCtrlParadigmRobotReach *dio_ctrl_paradigm, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui)
{
	ExpCtrl2DioCtrlMsgItem msg_item;
	char str_exp_ctrl_msg[EXP_CTRL_2_DIO_CTRL_MSG_STRING_LENGTH];
	unsigned int recording_number;
	bool cancellation_required_for_status_timers;
	bool timer_restart_reqiured_for_low_status_timers, timer_restart_reqiured_for_high_status_timers;
	while (get_next_exp_ctrl_2_dio_ctrl_msg_buffer_item(msgs_exp_ctrl_2_dio_ctrl, &msg_item))
	{
		get_exp_ctrl_2_dio_ctrl_msg_type_string(msg_item.msg_type, str_exp_ctrl_msg);
//		print_message(INFO_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", str_exp_ctrl_msg);
		switch (msg_item.msg_type)
		{
			case EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL:	


				dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, GUIDE_LED_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");

				dio_ctrl_paradigm->selected_target_led_component_list_idx = msg_item.additional_data;
				switch (dio_ctrl_paradigm->target_led_component_indexes_list[dio_ctrl_paradigm->selected_target_led_component_list_idx])
				{
					case  LEFT_LED_IDX_IN_DIO_CTRL_DATA:

						dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
						if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, LEFT_LED_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
							return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");

						break;
					case RIGHT_LED_IDX_IN_DIO_CTRL_DATA:

						dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
						if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, RIGHT_LED_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
							return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");

						break;
					default:
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL - switch (dio_ctrl_paradigm.target_led_comp_idx) -default");	
				}

				if (dio_ctrl_paradigm->restrain_on)
				{
					dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}

				if (! enable_dio_ctrl_input_with_no_status_reset(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &timer_restart_reqiured_for_low_status_timers, &timer_restart_reqiured_for_high_status_timers))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! enable_dio_ctrl_input_with_no_status_reset().");
				if (timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers)
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "(timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers).");
				if (timer_restart_reqiured_for_low_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}
				if (timer_restart_reqiured_for_high_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}
				
				disable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]),  &cancellation_required_for_status_timers) ;
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}


				if (! enable_dio_ctrl_input_with_no_status_reset(&(dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA]), &timer_restart_reqiured_for_low_status_timers, &timer_restart_reqiured_for_high_status_timers))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! enable_dio_ctrl_input_with_no_status_reset().");
				if (timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers)
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "(timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers).");
				if (timer_restart_reqiured_for_low_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}
				if (timer_restart_reqiured_for_high_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}


				if (! enable_dio_ctrl_input_with_no_status_reset(&(dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA]), &timer_restart_reqiured_for_low_status_timers, &timer_restart_reqiured_for_high_status_timers))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! enable_dio_ctrl_input_with_no_status_reset().");
				if (timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers)
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "(timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers).");
				if (timer_restart_reqiured_for_low_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}
				if (timer_restart_reqiured_for_high_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}


				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL:	

				switch (dio_ctrl_paradigm->target_led_component_indexes_list[dio_ctrl_paradigm->selected_target_led_component_list_idx])
				{
					case  LEFT_LED_IDX_IN_DIO_CTRL_DATA:
						dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
						if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER, LEFT_LED_IDX_IN_DIO_CTRL_DATA, 0))
							return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
						break;
					case  RIGHT_LED_IDX_IN_DIO_CTRL_DATA:
						dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
						if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER, RIGHT_LED_IDX_IN_DIO_CTRL_DATA, 0))
							return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
						break;
							default: 
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL - switch (dio_ctrl_paradigm.target_led_comp_idx) -default");	
				}	
						
				dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER, GUIDE_LED_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");


				dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER, GET_READY_LED_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");

				dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_LOW;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER, LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");

				disable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]),  &cancellation_required_for_status_timers) ;
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}


				disable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA]),  &cancellation_required_for_status_timers) ;
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}

				disable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA]),  &cancellation_required_for_status_timers) ;
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}



				break;

			case EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_REWARD:	// trial handler should send reward before ending trial.
				dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, VALVE_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_PUNISHMENT:	
				dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, BUZZER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_START_RECORDING:
				recording_number = msg_item.additional_data;
				if (! write_to_dio_ctrl_2_gui_msg_buffer(msgs_dio_ctrl_2_gui, current_time,  DIO_CTRL_2_GUI_MSG_START_RECORDING, recording_number))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! write_to_dio_ctrl_2_gui_msg_buffer(().");
				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_STOP_RECORDING:	
				recording_number = msg_item.additional_data;
				if (! write_to_dio_ctrl_2_gui_msg_buffer(msgs_dio_ctrl_2_gui, current_time,  DIO_CTRL_2_GUI_MSG_STOP_RECORDING, recording_number))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! write_to_dio_ctrl_2_gui_msg_buffer(().");
				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_CANCEL_RECORDING:	
				recording_number = msg_item.additional_data;
				if (! write_to_dio_ctrl_2_gui_msg_buffer(msgs_dio_ctrl_2_gui, current_time,  DIO_CTRL_2_GUI_MSG_CANCEL_RECORDING, recording_number))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! write_to_dio_ctrl_2_gui_msg_buffer(().");
				break;

			case EXP_CTRL_2_DIO_CTRL_MSG_GET_READY_TO_TRIAL_START:	
				dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, GET_READY_LED_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");


				if (dio_ctrl_paradigm->restrain_on)
				{
					dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status = DIO_CTRL_COMP_STATUS_HIGH;
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_OUTPUT_TIMER, LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}

				if (! enable_dio_ctrl_input_with_no_status_reset(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &timer_restart_reqiured_for_low_status_timers, &timer_restart_reqiured_for_high_status_timers))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "! enable_dio_ctrl_input_with_no_status_reset().");
				if (timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers)
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "write_to_dio_ctrl_2_gui_msg_buffer", "(timer_restart_reqiured_for_low_status_timers & timer_restart_reqiured_for_high_status_timers).");
				if (timer_restart_reqiured_for_low_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}
				if (timer_restart_reqiured_for_high_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", "! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				}
				
				disable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]),  &cancellation_required_for_status_timers) ;
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}

				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_STATUS_RESET:

				if (! enable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]), &cancellation_required_for_status_timers))
					return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "! enable_dio_ctrl_input_with_status_reset).");
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");					
				}

				break;
			case EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE:
				disable_dio_ctrl_input_with_status_reset(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]),  &cancellation_required_for_status_timers) ;
				if (cancellation_required_for_status_timers)
				{
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
					if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
						return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_dio_ctrl_interf_to_dio_control_msg", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				}
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleExpCtrl2DioCtrlMsgs", "handle_exp_control_to_dio_control_msg", str_exp_ctrl_msg);
		}
	}
	return TRUE;
}
