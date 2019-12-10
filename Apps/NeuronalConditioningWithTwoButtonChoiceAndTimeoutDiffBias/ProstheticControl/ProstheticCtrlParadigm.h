#ifndef PROSTHETIC_CTRL_PARADIGM_H
#define PROSTHETIC_CTRL_PARADIGM_H

#include "../../../Library/System/TimeStamp/TimeStamp.h"
#include "../../../Library/Thresholding/Thresholding.h"
#include "../../../Library/Coordinate/Cartesian.h"
#include "../../../Library/Robot/ThreeDofRobot.h"

typedef struct 
{
	unsigned int				selected_position_idx;	
	unsigned int				num_of_positions;
	CartesianCoordinates		*cart_coordinates;
	ThreeDofRobotServoPulse	*robot_pulse_widths;
} RobotSpacePoints;

typedef struct 
{
	EllipsoidThreshold			target_reach_threshold;  /// this data is retrieved from trialhandler when there is a change in it. so no need to save it for every trial during recording. trial handler saves it.
	EllipsoidThreshold			point_reach_threshold;
	EllipsoidThreshold			outer_threshold;
}
ProstheticCtrlThreshold;


typedef struct 
{
	double						left_target_left_bias_constant_gui;   // left_spike_count*left_spike_multiplier+left_bias_constant >? right_spike_count*right_spike_multiplier + right_bias_constant
	double						left_target_right_bias_constant_gui; 

	double						right_target_left_bias_constant_gui;   // left_spike_count*left_spike_multiplier+left_bias_constant >? right_spike_count*right_spike_multiplier + right_bias_constant
	double						right_target_right_bias_constant_gui;
 
	double						left_spike_multiplier;
	double						right_spike_multiplier;

	double						left_bias_constant;   // left_spike_count*left_spike_multiplier+left_bias_constant >? right_spike_count*right_spike_multiplier + right_bias_constant
	double						right_bias_constant;   

	double						spike_count_threshold_left; 
	double						spike_count_threshold_right; 
	TimeStamp					stay_at_target_duration;	
	TimeStamp					send_pw_command_wait_period;
	TimeStamp					receive_position_wait_period;
	double						spike_2_servo_degree_multiplier;
	unsigned int 					spike_2_servo_degree_handling_period_multiplier;  //  send_pw_command_wait_period * this value = spike count handling. 
	double						max_servo_angle_change;  // (in terms of degree)   // for servo control in handle spike data buff. It determines max servo speed.
//	double						servo_angle_change_threshold;  // (in terms of degree)   // for servo control in handle spike data buff. It determines min servo speed to be handled, it is a threshold to handle servo, below it, speed is 0.
	ProstheticCtrlThreshold				threshold;
	RobotSpacePoints				start_info;
	RobotSpacePoints				target_info;
	ThreeDofRobotCartesianLimit	cartesian_space_limits;	// interrupt pulsing servos, robot goes to somewhere dangerous
	ServoAngularLimit				polar_space_limits[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	unsigned int					num_of_output_neurons;
	bool						only_move_toward_selected_side;
} ProstheticCtrlParadigmRobotReach;

bool submit_cartesian_robotic_space_borders(ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *paradigm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max);
bool submit_polar_robotic_space_borders(ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *paradigm, double joint_angle_base_lower_limit, double joint_angle_base_upper_limit, double joint_angle_shoulder_lower_limit, double joint_angle_shoulder_upper_limit, double joint_angle_elbow_lower_limit, double joint_angle_elbow_upper_limit);
bool check_robot_space_borders(ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *paradigm);

#endif
