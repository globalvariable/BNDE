#include "HandleExpCtrlDur2ExpCtrlMsgs.h"


static ExpStatus *trial_status = NULL;
static ExpCtrlDur2ExpCtrlMsg *msgs_trial_dur_hand_2_exp_ctrl = NULL;
static ExpCtrl2ExpCtrlDurMsg *msgs_exp_ctrl_2_trial_dur_hand = NULL;
static ExpCtrl2DioCtrlMsg *msgs_exp_ctrl_2_dio_ctrl = NULL;
static ExpCtrl2ProstheticCtrlMsg *msgs_exp_ctrl_2_prosthetic_ctrl = NULL;
static ExpCtrl2NeuralNetMsg *msgs_exp_ctrl_2_neural_net = NULL;

static ClassifiedExpHistory *classified_history = NULL;
static ExpCtrlParadigmRobotReach *paradigm = NULL;
static ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui = NULL;
static ExpStatusHistory *trial_status_history = NULL;


bool handle_trial_dur_handler_to_exp_control_msg(TimeStamp current_time)
{
	ExpCtrlDur2ExpCtrlMsgItem msg_item;
	char str_trial_dur_msg[TRIAL_DUR_HAND_2_EXP_CTRL_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	ExpCtrl2NeuralNetMsgAdditional exp_ctrl_to_neural_net_msg_add;
	ExpCtrl2ProstheticCtrlMsgAdditional  exp_ctrl_2_prosthetic_ctrl_add;
	double remained_distance_to_target;

	unsigned int trial_types_sum;

	TimeStamp trial_length;
	ExpCtrl2ProstheticCtrlMsgAdditional  exp_ctrl_to_prosthetic_ctrl_msg_add;

	while (get_next_trial_dur_hand_2_exp_ctrl_msg_buffer_item(msgs_trial_dur_hand_2_exp_ctrl, &msg_item))
	{
		get_trial_dur_hand_2_exp_ctrl_msg_type_string(msg_item.msg_type, str_trial_dur_msg);
//		print_message(INFO_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", str_trial_dur_msg);
		switch (msg_item.msg_type)
		{
			case TRIAL_DUR_HAND_2_EXP_CTRL_MSG_TIMEOUT:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_GET_READY_TO_START:
						*trial_status = TRIAL_STATUS_IN_TRIAL;
						paradigm->current_trial_data.trial_start_time = current_time;

 ///                   paradigm->current_trial_data.difficulty_level  determined when trial ends according to robot start position
						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->max_trial_length[paradigm->current_trial_data.difficulty_level]))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");

						exp_ctrl_to_prosthetic_ctrl_msg_add.robot_target_position_idx = paradigm->current_trial_data.robot_target_position_idx;
						if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_TRIAL, exp_ctrl_to_prosthetic_ctrl_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer()");
						if (!write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_TRIAL))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_TRIAL))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_trial_status_history()");

						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_TRIAL;
						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = paradigm->current_trial_data.robot_target_position_idx;
/*						if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleDioCtrl2ExpCtrlMsgs", "handle_dio_control_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
*/
						break; 

					case TRIAL_STATUS_IN_TRIAL:

						remained_distance_to_target = msg_item.additional_data;
						trial_length = current_time - paradigm->current_trial_data.trial_start_time;
						paradigm->current_trial_data.trial_end_time = current_time;
						paradigm->current_trial_data.trial_length = trial_length;

						paradigm->current_trial_data.binary_reward = FALSE;
						paradigm->current_trial_data.trial_incomplete = TRUE;

						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;

						if (! write_trial_data_to_classified_trial_history(classified_history, &(paradigm->current_trial_data)))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_trial_data_to_classified_trial_history()");

						write_to_averaging_struct(paradigm->target_success_average[paradigm->current_trial_data.robot_target_position_idx], 0.0);
						write_to_averaging_struct(paradigm->target_success_average_small[paradigm->current_trial_data.robot_target_position_idx], 0.0);
						write_to_averaging_struct(paradigm->all_success_average, 0.0);

						paradigm->current_trial_data.trial_start_time = 0;
						paradigm->current_trial_data.trial_end_time = 0;
						paradigm->current_trial_data.trial_length = 0;

	// BELOW LINE IS SET BY THE USER.
	//						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.

						if (paradigm->current_trial_data.auto_target_select_mode_on)
						{
							paradigm->current_trial_data.robot_target_position_idx = (unsigned int)(paradigm->num_of_robot_target_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
							trial_types_sum = 0;
							trial_types_sum += get_previous_trial_history_data_ptr(classified_history->all_trials, 1)->robot_target_position_idx;
							trial_types_sum += get_previous_trial_history_data_ptr(classified_history->all_trials, 2)->robot_target_position_idx;
							trial_types_sum += get_previous_trial_history_data_ptr(classified_history->all_trials, 3)->robot_target_position_idx;
							trial_types_sum += paradigm->current_trial_data.robot_target_position_idx;
							if (trial_types_sum > 3)	// do not allow 4 consecutive right trials
								paradigm->current_trial_data.robot_target_position_idx = 0;
							if (trial_types_sum == 0)	// do not allow 4 consecutive left trials
								paradigm->current_trial_data.robot_target_position_idx = 1;
						}
						else
						{
							paradigm->current_trial_data.robot_target_position_idx = paradigm->current_trial_data.gui_selected_target_position_idx;
						}

						paradigm->current_trial_data.target_led_component_list_idx = paradigm->current_trial_data.robot_target_position_idx;

						
						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");
						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->trial_refractory))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.dummy = 0;	// send this message before EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_TRIAL since mov obj handler handles this msg according to target idx
						if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIAL_TIMEOUT, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer()");

						if ((paradigm->current_trial_data.robot_target_position_idx) == 0)   /// LEFT TARGET
						{
							exp_ctrl_2_prosthetic_ctrl_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx; 
						}
						else		// RIGHT TARGET
						{
							exp_ctrl_2_prosthetic_ctrl_add.robot_start_position_idx = paradigm->num_of_robot_start_positions - 1 - paradigm->current_trial_data.robot_start_position_idx;
						}

						paradigm->current_trial_data.difficulty_level = paradigm->current_trial_data.robot_start_position_idx;  ///   paradigm->current_trial_data.robot_start_position_idx is minimum 1

						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_REWARD, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
		
						if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_TRIAL, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer()");

						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
/*						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_PUNISHMENT, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");  */

						if (!write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_trial_status_history()");

						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
/*						if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
*/
						exp_ctrl_to_neural_net_msg_add.dummy = 0;
/*						if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_END_TRIAL_WITH_NOTHING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleProstheticCtrl2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
*/
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = 0;
/*						if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
*/
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_ENABLE_INP_COMPS_W_STATUS_RESET, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (!write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_START_TRIAL_AVAILABLE))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_START_TRIAL_AVAILABLE))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", "write_to_trial_status_history()");

						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						print_message(BUG_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", str_trial_dur_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", str_status);
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", str_trial_dur_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", str_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgss", "handle_trial_dur_handler_to_exp_control_msg", str_trial_dur_msg);	
		}
	}
	return TRUE;
}



void initialize_trial_dur_handler_to_exp_control_msg_params(ExpStatus *arg_trial_status, ExpCtrlDur2ExpCtrlMsg *arg_msgs_trial_dur_hand_2_exp_ctrl, ExpCtrl2ExpCtrlDurMsg *arg_msgs_exp_ctrl_2_trial_dur_hand, ExpCtrl2DioCtrlMsg *arg_msgs_exp_ctrl_2_dio_ctrl, ExpCtrl2ProstheticCtrlMsg *arg_msgs_exp_ctrl_2_prosthetic_ctrl, ExpCtrl2NeuralNetMsg *arg_msgs_exp_ctrl_2_neural_net, ClassifiedExpHistory *arg_classified_history, ExpCtrlParadigmRobotReach *arg_paradigm, ExpCtrl2GuiMsg *arg_msgs_exp_ctrl_2_gui, ExpStatusHistory *arg_trial_status_history)
{
	trial_status = arg_trial_status;
	msgs_trial_dur_hand_2_exp_ctrl = arg_msgs_trial_dur_hand_2_exp_ctrl;
	msgs_exp_ctrl_2_trial_dur_hand = arg_msgs_exp_ctrl_2_trial_dur_hand;
	msgs_exp_ctrl_2_dio_ctrl = arg_msgs_exp_ctrl_2_dio_ctrl;
	msgs_exp_ctrl_2_prosthetic_ctrl = arg_msgs_exp_ctrl_2_prosthetic_ctrl;
	msgs_exp_ctrl_2_neural_net = arg_msgs_exp_ctrl_2_neural_net;
	classified_history = arg_classified_history; 
	paradigm = arg_paradigm;
	msgs_exp_ctrl_2_gui = arg_msgs_exp_ctrl_2_gui;
	trial_status_history = arg_trial_status_history;
}


