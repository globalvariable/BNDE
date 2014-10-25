#include "ProstheticCtrlData.h"


ProstheticCtrlData* allocate_prosthetic_ctrl_data(ProstheticCtrlData* data, TimeStamp	neural_net_2_prosthetic_ctrl_delay, TimeStamp	HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
{
	if (neural_net_2_prosthetic_ctrl_delay < HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
		return (ProstheticCtrlData*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "deallocate_prosthetic_ctrl_data", "neural_net_2_prosthetic_ctrl_delay < MINIMUM_NEURAL_NET_2_PROSTHETIC_CTRL_SPIKE_SCHEDULING_DELAY.");    
	if (data != NULL)
	{
		data = deallocate_prosthetic_ctrl_data(data);
		data = allocate_prosthetic_ctrl_data(data, neural_net_2_prosthetic_ctrl_delay, HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
		return data;
	}  
	data = g_new0(ProstheticCtrlData,1);
	data->neural_net_2_prosthetic_ctrl_delay = neural_net_2_prosthetic_ctrl_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "allocate_prosthetic_ctrl_data", "Created prosthetic_ctrl_data.");
	return data;	
}

ProstheticCtrlData* deallocate_prosthetic_ctrl_data(ProstheticCtrlData* data)
{
	if (data == NULL)
		return (ProstheticCtrlData*)print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "deallocate_prosthetic_ctrl_data", "prosthetic_ctrl_data == NULL.");    
	g_free(data->comp_types);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "deallocate_prosthetic_ctrl_data", "Destroyed prosthetic_ctrl_data.");
	return NULL;
}

bool get_component_type_idx_in_prosthetic_ctrl_data(ProstheticCtrlData *data, ProstheticCtrlCompType comp_type, unsigned int *idx)
{
	unsigned int i;
	unsigned int num_of_comps = data->num_of_comps;
	ProstheticCtrlCompTypeData	*comp_types = data->comp_types;
	*idx = num_of_comps; 

	for (i = 0; i < num_of_comps; i++)
	{
		if (comp_type == comp_types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_component_type_to_prosthetic_ctrl_data(ProstheticCtrlData *data, ProstheticCtrlCompType comp_type, TimeStamp	stay_at_start_duration, TimeStamp stay_at_target_duration, double initial_threshold, double threshold_increment_amount, ProstheticCtrlLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
{
	unsigned int i;
	bool comp_type_used;
	char temp[PROSTHETIC_CTRL_COMPONENT_TYPE_MAX_STRING_LENGTH];
	ProstheticCtrlCompTypeData	*lcl_comp_types;
	if (stay_at_start_duration < HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "add_component_type_to_prosthetic_ctrl_data", "stay_at_start_duration < MINIMUM_NEURAL_NET_2_PROSTHETIC_CTRL_SPIKE_SCHEDULING_DELAY.");	
	if (!is_prosthetic_ctrl_component_type_used(data, comp_type, &comp_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "add_component_type_to_prosthetic_ctrl_data", "! is_component_type_used()");	
	if (comp_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "add_component_type_to_prosthetic_ctrl_data", "comp_type_used");	
	if (!get_prosthetic_ctrl_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "add_component_type_to_prosthetic_ctrl_data", "!get_prosthetic_ctrl_component_type_string()");
	lcl_comp_types = g_new0(ProstheticCtrlCompTypeData, data->num_of_comps + 1);
	for (i = 0; i < data->num_of_comps; i++)
		lcl_comp_types[i] = data->comp_types[i];
	g_free(data->comp_types);
	data->comp_types = lcl_comp_types;
	data->comp_types[data->num_of_comps].type = comp_type;
	data->comp_types[data->num_of_comps].comp_constraints.stay_at_start_duration = stay_at_start_duration;
	data->comp_types[data->num_of_comps].comp_constraints.stay_at_target_duration = stay_at_target_duration;
	data->comp_types[data->num_of_comps].comp_constraints.initial_threshold = initial_threshold;
	data->comp_types[data->num_of_comps].comp_constraints.current_threshold = initial_threshold;
	data->comp_types[data->num_of_comps].comp_constraints.threshold_increment_amount = threshold_increment_amount;
	data->comp_types[data->num_of_comps].comp_constraints.target_location = target_location;
	data->comp_types[data->num_of_comps].comp_constraints.motor_command_delivery_interval = motor_command_delivery_interval;
	data->num_of_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "add_component_type_to_prosthetic_ctrl_data", temp);	
	return TRUE;
}
bool is_prosthetic_ctrl_component_type_used(ProstheticCtrlData* data, ProstheticCtrlCompType comp_type, bool *used)
{
	unsigned int i;
	char temp[PROSTHETIC_CTRL_COMPONENT_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_prosthetic_ctrl_component_type_string(comp_type, temp))    // is comp type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "is_component_type_used", "!get_prosthetic_ctrl_component_type_string()");

	for (i = 0; i < data->num_of_comps; i++)
	{
		if (comp_type == data->comp_types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}
bool set_global_constraints_prosthetic_ctrl_data(ProstheticCtrlData *data, TimeStamp stay_at_start_duration, TimeStamp stay_at_target_duration, ProstheticCtrlLocationType initial_threshold, ProstheticCtrlLocationType threshold_increment_amount, ProstheticCtrlLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
{
	if (stay_at_start_duration < HARD_MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ProstheticCtrlData", "set_global_constraints_prosthetic_ctrl_data", "stay_at_start_duration < MINIMUM_NEURAL_NET_2_PROSTHETIC_CTRL_SPIKE_SCHEDULING_DELAY.");	
	data->glo_constraints.stay_at_start_duration = stay_at_start_duration;
	data->glo_constraints.stay_at_target_duration = stay_at_target_duration;
	data->glo_constraints.initial_threshold = initial_threshold;
	data->glo_constraints.current_threshold = initial_threshold;
	data->glo_constraints.threshold_increment_amount = threshold_increment_amount;	
	data->glo_constraints.target_location = target_location;	
	data->glo_constraints.motor_command_delivery_interval = motor_command_delivery_interval;	
	return TRUE;
}


