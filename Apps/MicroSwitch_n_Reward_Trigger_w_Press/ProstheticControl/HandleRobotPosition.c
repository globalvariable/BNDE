#include "HandleRobotPosition.h"




bool handle_robot_arm_position_threshold(ThreeDofRobot *robot, ProstheticCtrlParadigmRobotReach *paradigm, ProstheticCtrlStatus *prosthetic_ctrl_status, TimeStamp current_time, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread)
{
	ProstheticCtrlThreshold *threshold = &(paradigm->threshold);
	CartesianCoordinates	*target_coordinates, *opposite_target_coordinates;
	ThreeDofRobotPosition	*tip_position;
//	ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data;
	char str_prosthetic_ctrl_status[PROSTHETIC_CTRL_STATUS_MAX_STRING_LENGTH];
	double reward, punishment;
	unsigned int opposite_position_idx;

	switch (*prosthetic_ctrl_status)
	{
		case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
			break;	
		case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:
			break;
		case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL: 
			target_coordinates = &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]);
			tip_position = &(robot->tip_position);
			if (apply_ellipsoid_threshold(&(threshold->target_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
//				printf ("Reached Ellipsoid Threshold\n");
				*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL;
				reward = distance_btwn_two_points(&(robot->tip_position), &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]));
//				printf ("Distance to target = %f\n", reward);		
				if (! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl, current_time,  PROSTHETIC_CTRL_2_EXP_CTRL_MSG_REWARD_REQUEST, reward)) 
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer()");
				if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL))
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_prosthetic_ctrl_status_history()");
			}
			
			if (paradigm->target_info.selected_position_idx == 0)
				opposite_position_idx = 1;
			else
				opposite_position_idx = 0;

			opposite_target_coordinates = &(paradigm->target_info.cart_coordinates[opposite_position_idx]);

			if (apply_ellipsoid_threshold(&(threshold->target_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, opposite_target_coordinates->height, opposite_target_coordinates->depth, opposite_target_coordinates->lateral))
			{
//				printf ("Reached Opposite Target\n");
				*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL;
				punishment = distance_btwn_two_points(&(robot->tip_position), &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]));
//				printf ("Distance to target = %f\n", punishment);		
				if (! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl, current_time,  PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST, punishment)) 
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer()");	
				if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL))
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_status_history()");
			}
			if (! check_robot_space_borders(robot, paradigm))
			{
//				printf ("Out of cartesian space borders\n");
				*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL;
				punishment = distance_btwn_two_points(&(robot->tip_position), &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]));
//				printf ("Distance to target = %f\n", punishment);		
				if (! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl, current_time,  PROSTHETIC_CTRL_2_EXP_CTRL_MSG_PUNISHMENT_REQUEST, punishment)) 
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer()");
				if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL))
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs", "handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg", "! write_to_prosthetic_ctrl_status_history()");
			}
			break;
		case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT:
/*			target_coordinates = &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]);
			tip_position = &(robot->tip_position);
			if (apply_ellipsoid_threshold(&(threshold->point_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				*prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT;
				prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = current_time + paradigm->stay_at_target_duration;
				prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION;
				if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, current_time,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data))
					return print_message(BUG_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer()");
				if (! write_to_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, current_time, PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT))
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_prosthetic_ctrl_status_history()");
			}
*/			break;
		case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
			break;
		case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
			break;
		case PROSTHETIC_CTRL_STATUS_DISABLED:
			break;
		default:
			get_prosthetic_ctrl_status_type_string(*prosthetic_ctrl_status, str_prosthetic_ctrl_status);   
			return print_message(BUG_MSG ,"ProstheticControl", "HandleRobotPosition", "handle_robot_arm_position_threshold", str_prosthetic_ctrl_status);
	}

	return TRUE;
}
