#ifndef EXP_CTRL_PARADIGM_H
#define EXP_CTRL_PARADIGM_H

#include "../../../Library/System/TimeStamp/TimeStamp.h"
#include "../../../Library/Coordinate/Cartesian.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/Thresholding/Thresholding.h"
#include "ExpData.h"
#include "../../../Library/Misc/Averaging.h"

#define REWARD_PREDICTION_WINDOW	4.0


typedef struct 
{
	unsigned int				num_of_robot_start_positions;
	unsigned int				num_of_robot_target_positions;
	unsigned int				*target_led_component_indexes_list;
	unsigned int				num_of_target_led_components;
	unsigned int				num_of_difficulty_levels;
	TimeStamp				*max_trial_length;			// num of difficulty levels
	TimeStamp				trial_refractory;	
	EllipsoidThreshold			min_target_reach_threshold;
	TimeStamp				get_ready_to_trial_start_length;	
//	Selected values for a trial:
	ExpData					current_trial_data;
	AveragingStruct			**target_success_average; // num_of_targets;
	AveragingStruct			**target_success_average_small; // num_of_targets;
	AveragingStruct			*all_success_average; // num_of_targets;
} ExpCtrlParadigmRobotReach;


#endif
