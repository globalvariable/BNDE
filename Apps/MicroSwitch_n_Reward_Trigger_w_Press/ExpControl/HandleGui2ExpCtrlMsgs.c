#include "HandleGui2ExpCtrlMsgs.h"


static ExpStatus *trial_status = NULL;
static Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl = NULL;
static ExpCtrl2ExpCtrlDurMsg* msgs_exp_ctrl_2_trial_dur_hand = NULL;
static ExpCtrl2DioCtrlMsg *msgs_exp_ctrl_2_dio_ctrl = NULL;
static ExpCtrl2ProstheticCtrlMsg *msgs_exp_ctrl_2_prosthetic_ctrl = NULL;
static ExpCtrl2NeuralNetMsg *msgs_exp_ctrl_2_neural_net = NULL;

static ExpCtrlParadigmRobotReach *paradigm = NULL;
static ClassifiedExpHistory* classified_history = NULL;
static ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui = NULL;
static ExpStatusHistory *trial_status_history = NULL;



bool handle_gui_to_exp_control_msg(TimeStamp current_time)
{
	Gui2ExpCtrlMsgItem msg_item;
	char str_gui_msg[GUI_2_EXP_CTRL_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	ExpCtrl2NeuralNetMsgAdditional exp_ctrl_to_neural_net_msg_add;

	ExpCtrl2ProstheticCtrlMsgAdditional exp_ctrl_2_prosthetic_ctrl_add;
	unsigned int recording_number;
	ExpData *prev_trial_w_type;

	while (get_next_gui_2_exp_ctrl_msg_buffer_item(msgs_gui_2_exp_ctrl, &msg_item))
	{
		get_gui_2_exp_ctrl_msg_type_string(msg_item.msg_type, str_gui_msg);
//		print_message(INFO_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
		switch (msg_item.msg_type)
		{
			case GUI_2_EXP_CTRL_MSG_ENABLE_EXP_CTRLLING:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;
						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->trial_refractory))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");

						if (paradigm->current_trial_data.auto_target_select_mode_on)
							paradigm->current_trial_data.robot_target_position_idx = (unsigned int)(paradigm->num_of_robot_target_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						else
							paradigm->current_trial_data.robot_target_position_idx = paradigm->current_trial_data.gui_selected_target_position_idx;

						paradigm->current_trial_data.target_led_component_list_idx = paradigm->current_trial_data.robot_target_position_idx;

						if ((paradigm->current_trial_data.robot_target_position_idx) == 0)   /// LEFT TARGET
						{
							exp_ctrl_2_prosthetic_ctrl_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx; 
						}
						else		// RIGHT TARGET
						{
							exp_ctrl_2_prosthetic_ctrl_add.robot_start_position_idx = paradigm->num_of_robot_start_positions - 1 - paradigm->current_trial_data.robot_start_position_idx;
						}

						if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_ENABLED, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						exp_ctrl_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = 0;
/*						if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");

*/						if (!write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_trial_status_history()");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Enable is not possible when TRIAL_STATUS_IN_TRIAL. It must be Enabled already.");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Enable is not possible when TRIAL_STATUS_IN_REFRACTORY. It must be Enabled already.");
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Enable is not possible when TRIAL_STATUS_START_TRIAL_AVAILABLE. It must be Enabled already.");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Enable is not possible when TRIAL_STATUS_GET_READY_TO_START. It must be Enabled already.");
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_DISABLE_EXP_CTRLLING:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Disable is not possible when TRIAL_STATUS_TRIALS_DISABLED.");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Disable is not possible when TRIAL_STATUS_IN_TRIAL.");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.dummy = 0;
						if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_DISABLED, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
						print_message(INFO_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Successfully disabled trials.");
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						exp_ctrl_2_prosthetic_ctrl_add.dummy = 0;
						if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_DISABLED, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_DISABLE_NOSE_POKE, 0))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						print_message(INFO_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Successfully disabled trials.");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Exp Disable is not possible when TRIAL_STATUS_GET_READY_TO_START.");
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_QUIT:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;
					case TRIAL_STATUS_IN_TRIAL:
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_INCREASE_ROBOT_START_POSITION_IDX:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						if ((paradigm->current_trial_data.robot_start_position_idx +1 ) > (paradigm->num_of_robot_start_positions/2))
						{
//							print_message(WARNING_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Reached paradigm->num_of_robot_start_positions number. Cannot be increase  more.");
						}
						else
						{
							paradigm->current_trial_data.robot_start_position_idx++;
						}
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Increasing threshold cannot be done during trial");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Increasing threshold cannot be done during TRIAL_STATUS_GET_READY_TO_START");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						if ((paradigm->current_trial_data.robot_start_position_idx +1 ) > (paradigm->num_of_robot_start_positions/2))
						{
//							print_message(WARNING_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Reached paradigm->num_of_robot_start_positions number. Cannot be increase  more.");
						}
						else
						{
							paradigm->current_trial_data.robot_start_position_idx++;
						}
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						if ((paradigm->current_trial_data.robot_start_position_idx +1 ) > (paradigm->num_of_robot_start_positions/2))
						{
//							print_message(WARNING_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Reached paradigm->num_of_robot_start_positions number. Cannot be increase  more.");
						}
						else
						{
							paradigm->current_trial_data.robot_start_position_idx++;
						}
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_DECREASE_ROBOT_START_POSITION_IDX:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						if (paradigm->current_trial_data.robot_start_position_idx == 0 )
						{
//							print_message(WARNING_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Reached paradigm->current_trial_data.robot_start_position_idx == 1. Cannot  decrease  more.");
						}
						else
						{
							paradigm->current_trial_data.robot_start_position_idx--;
						}
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Decreasing threshold cannot be done during trial");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Decreasing threshold cannot be done during TRIAL_STATUS_GET_READY_TO_START");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						if (paradigm->current_trial_data.robot_start_position_idx == 0 )
						{
//							print_message(WARNING_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Reached paradigm->current_trial_data.robot_start_position_idx == 1. Cannot  decrease  more.");
						}
						else
						{
							paradigm->current_trial_data.robot_start_position_idx--;
						}
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						if (paradigm->current_trial_data.robot_start_position_idx == 0 )
						{
//							print_message(WARNING_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Reached paradigm->current_trial_data.robot_start_position_idx == 1. Cannot  decrease  more.");
						}
						else
						{
							paradigm->current_trial_data.robot_start_position_idx--;
						}
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_SELECT_TARGET:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_AUTO_TARGET_SELECTION_OFF:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_AUTO_TARGET_SELECTION_ON:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_BROADCAST_START_RECORDING:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot start recording when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot start recording when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot start recording when TRIAL_STATUS_GET_READY_TO_START");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						recording_number = classified_history->all_trials->buff_write_idx;  // delete previous 
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_START_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_RECORDING, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_START_RECORDING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (! write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						recording_number = classified_history->all_trials->buff_write_idx; 
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_START_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_RECORDING, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_START_RECORDING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (! write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						break;
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_BROADCAST_STOP_RECORDING:		
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot stop recording when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot stop recording when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot stop recording when TRIAL_STATUS_GET_READY_TO_START");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						if (classified_history->all_trials->buff_write_idx == 0)
						{
							print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "No trial finished to be saved");
							break;
						}
						recording_number = classified_history->all_trials->buff_write_idx-1;  // delete previous 
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_STOP_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STOP_RECORDING, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_STOP_RECORDING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (! write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						break;				
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						if (classified_history->all_trials->buff_write_idx == 0)
						{
							print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "No trial finished to be saved");
							break;
						}
						recording_number = classified_history->all_trials->buff_write_idx-1;  // delete previous 
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_STOP_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STOP_RECORDING, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_STOP_RECORDING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (! write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						break;			
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_BROADCAST_CANCEL_RECORDING:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot cancel recording when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot cancel recording when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot cancel recording when TRIAL_STATUS_GET_READY_TO_START");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						recording_number = classified_history->all_trials->buff_write_idx;  // delete the recording for current trial   //  history buffer write idx is inceremented when trial ends by ExpControl rt thread funcitons.
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_CANCEL_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CANCEL_RECORDING, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_CANCEL_RECORDING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (! write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						break;				
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						recording_number = classified_history->all_trials->buff_write_idx;  // delete the recording for current trial   //  history buffer write idx is inceremented when trial ends by ExpControl rt thread funcitons.
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_CANCEL_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_2_prosthetic_ctrl_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, current_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CANCEL_RECORDING, exp_ctrl_2_prosthetic_ctrl_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
						exp_ctrl_to_neural_net_msg_add.recording_number = recording_number;
						if (! write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_CANCEL_RECORDING, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						if (! write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						break;			
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}
				break;
			case GUI_2_EXP_CTRL_MSG_RELEASE_REWARD:
				if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_RELEASE_REWARD, 0))
					return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");
				break;

			case GUI_2_EXP_CTRL_MSG_START_TRIAL_REQUEST:    // used for simulaitons.

				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot START_TRIAL_REQUEST when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot START_TRIAL_REQUEST when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot START_TRIAL_REQUEST when TRIAL_STATUS_GET_READY_TO_START");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "Cannot START_TRIAL_REQUEST when TRIAL_STATUS_IN_REFRACTORY");
						break;		
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						*trial_status = TRIAL_STATUS_GET_READY_TO_START;
						paradigm->current_trial_data.trial_start_time = current_time;

						if (!write_to_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand, current_time, EXP_CTRL_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->get_ready_to_trial_start_length))
							return print_message(ERROR_MSG ,"ExpControl", "HandleDioCtrl2ExpCtrlMsgs", "handle_dio_control_to_exp_control_msg", "write_to_exp_ctrl_2_trial_dur_hand_msg_buffer()");
						if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, current_time, EXP_CTRL_2_DIO_CTRL_MSG_START_TRIAL, paradigm->current_trial_data.target_led_component_list_idx))
							return print_message(ERROR_MSG ,"ExpControl", "HandleExpCtrlDur2ExpCtrlMsgs", "handle_trial_dur_handler_to_exp_control_msg", "write_to_exp_ctrl_2_dio_ctrl_msg_buffer()");

						prev_trial_w_type = get_previous_trial_history_data_ptr(classified_history->trial_types[paradigm->current_trial_data.robot_target_position_idx], 1);

						if (prev_trial_w_type->binary_reward)
						{
							paradigm->current_trial_data.reward_prediction = ((1.0-(1.0/REWARD_PREDICTION_WINDOW) ) * prev_trial_w_type->reward_prediction) + (1.0/REWARD_PREDICTION_WINDOW);
							printf ("%f\t%f\t%f\n", paradigm->current_trial_data.reward_prediction, prev_trial_w_type->reward_prediction, averaging_struct_get_mean(paradigm->target_success_average_small[paradigm->current_trial_data.robot_target_position_idx]) );
						}
						else
						{
							if (averaging_struct_get_mean(paradigm->target_success_average_small[paradigm->current_trial_data.robot_target_position_idx]) < 0.5)  // if 3 out of last 4 trials failed
								paradigm->current_trial_data.reward_prediction = (1.0-(1.0/REWARD_PREDICTION_WINDOW) ) * prev_trial_w_type->reward_prediction;
							printf ("%f\t%f\t%f\n", paradigm->current_trial_data.reward_prediction, prev_trial_w_type->reward_prediction, averaging_struct_get_mean(paradigm->target_success_average_small[paradigm->current_trial_data.robot_target_position_idx]) );
						}

						exp_ctrl_to_neural_net_msg_add.difficulty_reward_predict_add.difficulty_level = paradigm->current_trial_data.difficulty_level;  // determined when trial ends according to robot start position
						exp_ctrl_to_neural_net_msg_add.difficulty_reward_predict_add.reward_prediction = paradigm->current_trial_data.reward_prediction;

						if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, current_time, EXP_CTRL_2_NEURAL_NET_MSG_TRIAL_START, exp_ctrl_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"ExpControl", "HandleDioCtrl2ExpCtrlMsgs", "handle_dio_control_to_exp_control_msg", "write_to_exp_ctrl_2_neural_net_msg_buffer()");

						if (!write_to_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui, current_time, EXP_CTRL_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_GET_READY_TO_START))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_exp_ctrl_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_GET_READY_TO_START))
							return print_message(ERROR_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", "write_to_trial_status_history()");
						break;			
					default:
						print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_status);
				}

				break;

			default:
				return print_message(BUG_MSG ,"ExpControl", "HandleGui2ExpCtrlMsgs", "handle_gui_to_exp_control_msg", str_gui_msg);	
		}
	}
	return TRUE;
}

void initialize_gui_to_exp_control_msg_params(ExpStatus *arg_trial_status, Gui2ExpCtrlMsg *arg_msgs_gui_2_exp_ctrl, ExpCtrl2ExpCtrlDurMsg* arg_msgs_exp_ctrl_2_trial_dur_hand, ExpCtrl2DioCtrlMsg *arg_msgs_exp_ctrl_2_dio_ctrl, ExpCtrl2ProstheticCtrlMsg *arg_msgs_exp_ctrl_2_prosthetic_ctrl, ExpCtrl2NeuralNetMsg *arg_msgs_exp_ctrl_2_neural_net, ExpCtrlParadigmRobotReach *arg_paradigm, ClassifiedExpHistory* arg_classified_history, ExpCtrl2GuiMsg *arg_msgs_exp_ctrl_2_gui, ExpStatusHistory *arg_trial_status_history)

{
	trial_status = arg_trial_status;
	msgs_gui_2_exp_ctrl = arg_msgs_gui_2_exp_ctrl;
	msgs_exp_ctrl_2_trial_dur_hand = arg_msgs_exp_ctrl_2_trial_dur_hand;
	msgs_exp_ctrl_2_dio_ctrl = arg_msgs_exp_ctrl_2_dio_ctrl;
	msgs_exp_ctrl_2_prosthetic_ctrl = arg_msgs_exp_ctrl_2_prosthetic_ctrl;
	msgs_exp_ctrl_2_neural_net = arg_msgs_exp_ctrl_2_neural_net;

	paradigm = arg_paradigm;
	classified_history = arg_classified_history;
	msgs_exp_ctrl_2_gui = arg_msgs_exp_ctrl_2_gui;
	trial_status_history = arg_trial_status_history;
}
