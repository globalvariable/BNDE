#include "HandleExpCtrl2ProstheticCtrlMsgs.h"



bool handle_exp_control_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, ProstheticCtrlStatus *prosthetic_ctrl_status, TimeStamp current_time, ExpCtrl2ProstheticCtrlMsg *msgs_exp_ctrl_2_prosthetic_ctrl, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, MessageLogBuffer *message_log, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread)
{
	ExpCtrl2ProstheticCtrlMsgItem msg_item;
	char str_exp_ctrl_msg[EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH];
	char str_prosthetic_ctrl_status[PROSTHETIC_CTRL_STATUS_MAX_STRING_LENGTH];
	unsigned int recording_number, i;
	ProstheticCtrl2NeuralNetMsgAdditional	prosthetic_ctrl_2_neural_net_msg_add;
	ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data;

	while (get_next_exp_ctrl_2_prosthetic_ctrl_msg_buffer_item(msgs_exp_ctrl_2_prosthetic_ctrl, &msg_item))
	{
		get_exp_ctrl_2_prosthetic_ctrl_msg_type_string(msg_item.msg_type, str_exp_ctrl_msg);
		if (! write_to_message_log_buffer(message_log, INFO_MSG, current_time, "ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg))
			print_message(ERROR_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", "! write_to_message_log_buffer()");
		switch (msg_item.msg_type)
		{
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_TRIAL:	
				switch (*prosthetic_ctrl_status)
				{
					case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT;
						prosthetic_ctrl_paradigm->target_info.selected_position_idx = msg_item.additional_data.robot_target_position_idx;  
						if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT))
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_status_history()");
						prosthetic_ctrl_2_neural_net_msg_add.dummy = 0;
						for (i = 0; i < SNN_SIM_NUM_OF_DEDICATED_CPUS; i++)
						{
							if (! write_to_prosthetic_ctrl_2_neural_net_msg_buffer(msgs_prosthetic_ctrl_2_neural_net_multi_thread[i], current_time, PROSTHETIC_CTRL_2_NEURAL_NET_MSG_START_TRIAL, prosthetic_ctrl_2_neural_net_msg_add))
								return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_2_neural_net_msg_buffer()");
						}

						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time + prosthetic_ctrl_paradigm->stay_at_start_duration;  
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION;
						if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) 
							return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer()."); 


/*						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL;

						prosthetic_ctrl_paradigm->robot_speed = (unsigned int)(get_rand_number()*3+2);
						printf ("Speed: %u\n", prosthetic_ctrl_paradigm->robot_speed);
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[prosthetic_ctrl_paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_MOVING_TO_TARGET*prosthetic_ctrl_paradigm->robot_speed);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[prosthetic_ctrl_paradigm->target_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_MOVING_TO_TARGET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[prosthetic_ctrl_paradigm->target_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_MOVING_TO_TARGET);

*/
						break;

				case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);	
					case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);	
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					default:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
				}
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_END_TRIAL:	
				switch (*prosthetic_ctrl_status)
				{
					case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						break;
					case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:  // should have gone to target already to receive such message
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL; 
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);

						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time;  
						prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION;
						if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_CANCEL_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) 
							return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer()."); 

						break;
					case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL: // should have gone to target already to receive such message
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL; 
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						break;
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT: // should have gone to target already to receive such message
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL; 
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						break;
					case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL; 
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						break;
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL; 
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						break;
					default:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
				}
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ELLIPSOID_THRESHOLD:	
				switch (*prosthetic_ctrl_status)
				{
					case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
//						prosthetic_ctrl_paradigm->threshold.selected_target_reach_threshold = msg_item.additional_data.threshold;
						break;
					case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:  // should have gone to target already to receive such message
//						prosthetic_ctrl_paradigm->threshold.selected_target_reach_threshold = msg_item.additional_data.threshold;
						break;
					case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL: // should have gone to target already to receive such message
//						prosthetic_ctrl_paradigm->threshold.selected_target_reach_threshold = msg_item.additional_data.threshold;
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT: // should have gone to target already to receive such message
//						prosthetic_ctrl_paradigm->threshold.selected_target_reach_threshold = msg_item.additional_data.threshold;
						break;
					case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
//						prosthetic_ctrl_paradigm->threshold.selected_target_reach_threshold = msg_item.additional_data.threshold;
						break;
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
//						prosthetic_ctrl_paradigm->threshold.selected_target_reach_threshold = msg_item.additional_data.threshold;
						break;
					default:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
				}
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_ENABLED:	
				switch (*prosthetic_ctrl_status)
				{
					case PROSTHETIC_CTRL_STATUS_DISABLED:
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL;
						prosthetic_ctrl_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[prosthetic_ctrl_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
						if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL))
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_ctrl_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_status_history()");		
						break;
					case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:  // should have gone to target already to receive such message
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					default:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
				}
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIALS_DISABLED:
				switch (*prosthetic_ctrl_status)
				{
					case PROSTHETIC_CTRL_STATUS_DISABLED:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);	
					case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
						*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_DISABLED;
						print_message(INFO_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_ctrl_to_prosthetic_control_msg", "PROSTHETIC_CTRL_STATUS_DISABLED");			
						break;
					case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:  // should have gone to target already to receive such message
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);	
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
					default:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
				}
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_START_RECORDING:	
				recording_number = msg_item.additional_data.recording_number;
				if (! write_to_prosthetic_ctrl_2_gui_msg_buffer(msgs_prosthetic_ctrl_2_gui, current_time, PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING, recording_number))
					return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "write_to_prosthetic_ctrl_2_gui_msg_buffer", "! write_to_prosthetic_ctrl_2_gui_msg_buffer(().");
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STOP_RECORDING:	
				recording_number = msg_item.additional_data.recording_number;
				if (! write_to_prosthetic_ctrl_2_gui_msg_buffer(msgs_prosthetic_ctrl_2_gui, current_time, PROSTHETIC_CTRL_2_GUI_MSG_STOP_RECORDING, recording_number))
					return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "write_to_prosthetic_ctrl_2_gui_msg_buffer", "! write_to_prosthetic_ctrl_2_gui_msg_buffer(().");
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_CANCEL_RECORDING:	
				recording_number = msg_item.additional_data.recording_number;
				if (! write_to_prosthetic_ctrl_2_gui_msg_buffer(msgs_prosthetic_ctrl_2_gui, current_time, PROSTHETIC_CTRL_2_GUI_MSG_CANCEL_RECORDING, recording_number))
					return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "write_to_prosthetic_ctrl_2_gui_msg_buffer", "! write_to_prosthetic_ctrl_2_gui_msg_buffer(().");
				break;
			case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_TRIAL_TIMEOUT:	//  target idx is determined when starting the trial. so that sending current target idx to neural net now does not lead to any trouble.
				switch (*prosthetic_ctrl_status)
				{
					case PROSTHETIC_CTRL_STATUS_DISABLED:
						break;
					case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT: 
						break;
					case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL: 
						break;
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT: 		
						break;
					case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
						break;   // do nothing
					case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:		
						break;
					default:
						print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
						get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
						return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_prosthetic_ctrl_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"ProstheticControl", "HandleExpCtrl2ProstheticCtrlMsgs", "handle_exp_control_to_prosthetic_control_msg", str_exp_ctrl_msg);
		}
	}
	return TRUE;
}
