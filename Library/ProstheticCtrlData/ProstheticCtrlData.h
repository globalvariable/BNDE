#ifndef PROSTHETIC_CTRL_DATA_H
#define PROSTHETIC_CTRL_DATA_H

typedef struct __ProstheticCtrlConstraints ProstheticCtrlConstraints;
typedef struct __ProstheticCtrlCompTypeData ProstheticCtrlCompTypeData;
typedef struct __ProstheticCtrlData ProstheticCtrlData;
typedef struct __ProstheticCtrlStats ProstheticCtrlStats;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "ProstheticCtrlComponentTypes.h"
#include "ProstheticCtrlLocationType.h"
#include "../Messages/NeuralNet2ProstheticCtrl.h"


struct __ProstheticCtrlStats
{
	double		 	trajectory_success;		///  saves the information about how good the mov obj followed the target trajectory
	unsigned int		num_of_actions;		
	double			trajectory_success_ratio;		
};

struct __ProstheticCtrlConstraints
{
	TimeStamp			stay_at_start_duration;
	TimeStamp			stay_at_target_duration;		
	ProstheticCtrlLocationType	initial_threshold;	// for rewarding // millimeters
	ProstheticCtrlLocationType	threshold_increment_amount;	
	ProstheticCtrlLocationType	current_threshold;		
	ProstheticCtrlLocationType	target_location;
	TimeStamp			motor_command_delivery_interval;
};

struct __ProstheticCtrlCompTypeData
{
	ProstheticCtrlCompType		type;
	ProstheticCtrlConstraints		comp_constraints;
	ProstheticCtrlStats			comp_stats;
};

struct __ProstheticCtrlData
{
	ProstheticCtrlCompTypeData		*comp_types;
	unsigned int				num_of_comps;
	ProstheticCtrlConstraints			glo_constraints;
	TimeStamp				neural_net_2_prosthetic_ctrl_delay;   // move this into neural_net_2_prosthetic_ctrl when you have spare time.
	ProstheticCtrlStats				main_stats;
};

ProstheticCtrlData* allocate_prosthetic_ctrl_data(ProstheticCtrlData* data, TimeStamp	neural_net_2_prosthetic_ctrl_delay, TimeStamp	HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
ProstheticCtrlData* deallocate_prosthetic_ctrl_data(ProstheticCtrlData* data);

bool get_component_type_idx_in_prosthetic_ctrl_data(ProstheticCtrlData *data, ProstheticCtrlCompType comp_type, unsigned int *idx);
bool add_component_type_to_prosthetic_ctrl_data(ProstheticCtrlData *data, ProstheticCtrlCompType comp_type, TimeStamp	stay_at_start_duration, TimeStamp stay_at_target_duration, double initial_threshold, double threshold_increment_amount, ProstheticCtrlLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
bool set_global_constraints_prosthetic_ctrl_data(ProstheticCtrlData *data, TimeStamp stay_at_start_duration, TimeStamp stay_at_target_duration, ProstheticCtrlLocationType initial_threshold, ProstheticCtrlLocationType threshold_increment_amount, ProstheticCtrlLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
bool is_prosthetic_ctrl_component_type_used(ProstheticCtrlData* data, ProstheticCtrlCompType comp_type, bool *used);

#endif
