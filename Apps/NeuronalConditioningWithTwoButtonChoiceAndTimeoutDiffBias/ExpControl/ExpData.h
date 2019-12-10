#ifndef TRIAL_DATA_H
#define TRIAL_DATA_H


typedef struct __ExpData ExpData;

#include <stdbool.h>
#include "../../../Library/System/TimeStamp/TimeStamp.h"
#include "../../../Library/Thresholding/Thresholding.h"
#include "../../../Library/Misc/Misc.h"

struct __ExpData
{
	TimeStamp			trial_start_time;   
	TimeStamp			trial_end_time;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	unsigned int			target_led_component_list_idx;
	unsigned int			robot_start_position_idx;
	unsigned int			robot_target_position_idx;
	TimeStamp			trial_length;
	EllipsoidThreshold		rewarding_threshold;
	unsigned int			gui_selected_target_position_idx;
	bool				auto_target_select_mode_on;
	double				success_ratio;
	unsigned int			num_of_trials;    // so far, up to this trial
	bool				binary_reward;
	bool				trial_incomplete;
	unsigned int			num_of_incomplete_trials;  // so far, up to this trial
	unsigned int			difficulty_level;
	double				reward_prediction; 
	double				lever_press_requirement_probability;
	TimeStamp			lever_press_wait_duration;	
};





#endif
