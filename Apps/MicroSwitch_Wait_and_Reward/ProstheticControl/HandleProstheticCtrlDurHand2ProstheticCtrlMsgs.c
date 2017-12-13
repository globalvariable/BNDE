#include "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs.h"


bool handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, TimeStamp current_time, ProstheticCtrlStatus *prosthetic_ctrl_status, ProstheticCtrlDurHand2ProstheticCtrlMsg *msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl, ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MessageLogBuffer *message_log, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, ThreeDofRobotPulseHistory *robot_pulse_history, ThreeDofRobotAngleHistory *robot_angle_history, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history)
{
	ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data;
	ProstheticCtrlDurHand2ProstheticCtrlMsgItem msg_item;
	char str_prosthetic_ctrl_dur_msg[PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH];
	ProstheticCtrl2NeuralNetMsgAdditional	prosthetic_ctrl_2_neural_net_msg_add;
	static double prev_distance_to_target = 0;
	double distance_to_target;
	CartesianCoordinates	*target_coordinates;
	ThreeDofRobotPosition	*tip_position;
	unsigned int i;
	while (get_next_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer_item(msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_TIMEOUT:
				switch (msg_item.additional_data)
				{
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION:
						get_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_type_string(msg_item.msg_type, str_prosthetic_ctrl_dur_msg);
						if (! write_to_message_log_buffer(message_log, INFO_MSG, current_time, "ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", str_prosthetic_ctrl_dur_msg))
							print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_message_log_buffer()");
						switch (*prosthetic_ctrl_status)
						{
							case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
								return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION & *prosthetic_ctrl_status - PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL");									
							case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:
								*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL;
								if (! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl, current_time,  PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED, 0))
									return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer()");
								if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL))
									return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_status_history()");
								break;
							case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL:
								return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION & *prosthetic_ctrl_status - PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL");									
							case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT:
								return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION & *prosthetic_ctrl_status - PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT");
							case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
								*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL;
								if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL))
									return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_status_history()");
								break;
							case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
								return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION & *prosthetic_ctrl_status - PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT");
							default: 
								return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION & *prosthetic_ctrl_status - switch- default");							
						}
						break;	
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH:
						if (! handle_dio_ctrl_tx_shm_and_send_rs232_pulse_width_command(current_time, robot_pulse_history, prosthetic_ctrl_paradigm->max_servo_angle_change,  prosthetic_ctrl_paradigm->spike_count_threshold ))
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! handle_dio_ctrl_tx_shm_and_send_rs232_pulse_width_command");
						// Schedule adc conversion results reading and pulse width sending again.
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time + prosthetic_ctrl_paradigm->send_pw_command_wait_period;
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH;
						if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) 
							print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer().");
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time + prosthetic_ctrl_paradigm->receive_position_wait_period;
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION;
						if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) 
							print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer().");
						break;	
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION:
						if (! handle_dio_ctrl_tx_shm_and_send_rs232_adc_command(current_time))
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! handle_dio_ctrl_tx_shm_and_send_rs232_adc_command()"); 
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time + prosthetic_ctrl_paradigm->send_pw_command_wait_period;
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH;
						if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) 
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer()"); 
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time + prosthetic_ctrl_paradigm->receive_position_wait_period;
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION;
						if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) 
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer()"); 
						break;
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION:
						if (! handle_rs232_rx_buffer_and_write_to_dio_ctrl_rx_shm())
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! ! handle_rs232_rx_buffer_and_write_to_dio_ctrl_rx_shm()");
						calculate_forward_kinematics_with_averaging(robot_arm);	
						if (! handle_robot_arm_position_threshold(robot_arm, prosthetic_ctrl_paradigm, prosthetic_ctrl_status, current_time, msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, msgs_prosthetic_ctrl_2_exp_ctrl, prosthetic_ctrl_status_history, msgs_prosthetic_ctrl_2_neural_net_multi_thread))
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! handle_robot_arm_position_threshold()");
						if (! write_to_three_dof_robot_angle_history(robot_angle_history, current_time, robot_arm->servos[BASE_SERVO].current_angle, robot_arm->servos[SHOULDER_SERVO].current_angle, robot_arm->servos[ELBOW_SERVO].current_angle))
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_three_dof_robot_angle_history()");

						target_coordinates = &(prosthetic_ctrl_paradigm->target_info.cart_coordinates[prosthetic_ctrl_paradigm->target_info.selected_position_idx]);
						tip_position = &(robot_arm->tip_position);
						distance_to_target = distance_btwn_two_points(&(robot_arm->tip_position), &(prosthetic_ctrl_paradigm->target_info.cart_coordinates[prosthetic_ctrl_paradigm->target_info.selected_position_idx]));
						if ((*prosthetic_ctrl_status) == PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL)  // to be faster using, if instead of switch.
						{
							prosthetic_ctrl_2_neural_net_msg_add.binary_reward_add.target_idx = prosthetic_ctrl_paradigm->target_info.selected_position_idx;
							if (distance_to_target < prev_distance_to_target)
								prosthetic_ctrl_2_neural_net_msg_add.binary_reward_add.reward = 1;
							else if (distance_to_target > prev_distance_to_target)
								prosthetic_ctrl_2_neural_net_msg_add.binary_reward_add.reward = -1;
							else
								prosthetic_ctrl_2_neural_net_msg_add.binary_reward_add.reward = 0;
/*							for (i = 0; i < SNN_SIM_NUM_OF_DEDICATED_CPUS; i++)
							{
								if (! write_to_prosthetic_ctrl_2_neural_net_msg_buffer(msgs_prosthetic_ctrl_2_neural_net_multi_thread[i], current_time, PROSTHETIC_CTRL_2_NEURAL_NET_MSG_REINFORCEMENT, prosthetic_ctrl_2_neural_net_msg_add))
									return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_2_neural_net_msg_buffer()");   
							}   */
						}
						prev_distance_to_target = distance_to_target;
						break;	
					default:
						return FALSE;
				}
				break;
			default:
				return FALSE;
		}
	}

	return TRUE;
}
