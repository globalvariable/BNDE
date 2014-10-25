#ifndef THREE_DOF_ROBOT_H
#define THREE_DOF_ROBOT_H


#define THREE_DOF_ROBOT_NUM_OF_SERVOS	3

#define BASE_SERVO			0
#define SHOULDER_SERVO	1
#define ELBOW_SERVO		2

#include "../Servo/Servo.h"
#include "../Coordinate/Cartesian.h"
#include "../Misc/Misc.h"

typedef struct 
{
	double depth_min;
	double depth_max;
	double lateral_min;
	double lateral_max;
	double height_min;
	double height_max;
} ThreeDofRobotCartesianLimit;

typedef CartesianCoordinates ThreeDofRobotPosition; 

typedef struct 
{
	double		length_humerus;
	double		length_ulna;
	double		height_ulna;
} ThreeDofRobotSize;

typedef struct 
{
	pthread_mutex_t 				mutex; 
	ServoData					servos[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	ThreeDofRobotCartesianLimit	cartesian_security_limits;	// interrupt pulsing servos, robot goes to somewhere dangerous
	ThreeDofRobotPosition			tip_position;
	ThreeDofRobotPosition			tip_position_prev;
	ThreeDofRobotPosition			elbow_position;
	ThreeDofRobotSize			size;
} ThreeDofRobot;	

typedef struct 
{
	ServoPulse		pulse[THREE_DOF_ROBOT_NUM_OF_SERVOS];	// pulse width to transmit
} ThreeDofRobotServoPulse;
	

void init_three_dof_robot_arm(ThreeDofRobot *robot_arm);
void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna, double height_ulna);
void evaluate_three_dof_robot_arm_pw_command(ThreeDofRobot *robot_arm);
void evaluate_three_dof_robot_arm_pw_command_with_degree_limitation(ThreeDofRobot *robot_arm, double degree_limitation);
void evaluate_three_dof_robot_arm_pw_command_with_degree_limitation_and_threshold(ThreeDofRobot *robot_arm, double degree_limitation, double degree_threshold);
bool evaluate_three_dof_robot_arm_pw_command_with_any_servo_target_reach_feedback(ThreeDofRobot *robot_arm);
void calculate_forward_kinematics(ThreeDofRobot *robot_arm);
void submit_static_variables_for_forward_kinematics_with_three_sample_averaging(double servo_angle_base, double servo_angle_shoulder, double servo_angle_elbow);
void calculate_forward_kinematics_with_averaging(ThreeDofRobot *robot_arm);
void submit_arm_security_limits(ThreeDofRobot *robot_arm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max, double joint_angle_base_lower_limit, double joint_angle_base_upper_limit, double joint_angle_shoulder_lower_limit, double joint_angle_shoulder_upper_limit, double joint_angle_elbow_lower_limit, double joint_angle_elbow_upper_limit);
bool check_three_dof_robot_security_limits(ThreeDofRobot *robot_arm);


#endif
