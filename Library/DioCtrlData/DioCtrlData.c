#include "DioCtrlData.h"


DioCtrlData* allocate_dio_ctrl_data(DioCtrlData* data)
{
	if (data != NULL)
	{
		data = deallocate_dio_ctrl_data(data);
		data = allocate_dio_ctrl_data(data);
		return data;
	}  
	data = g_new0(DioCtrlData,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrlData", "allocate_dio_ctrl_data", "Created dio_ctrl_data.");
	return data;	
}

DioCtrlData* deallocate_dio_ctrl_data(DioCtrlData* data)
{
	if (data == NULL)
		return (DioCtrlData*)print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrlData", "deallocate_dio_ctrl_data", "dio_ctrl_data == NULL.");    
	g_free(data->inp_comp_types);
	g_free(data->outp_comp_types);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrlData", "deallocate_dio_ctrl_data", "Destroyed dio_ctrl_data.");
	return NULL;
}

bool get_input_component_type_idx_in_dio_ctrl_data(DioCtrlData *data, DioCtrlInputCompType comp_type, unsigned int *idx)
{
	unsigned int i;
	unsigned int num_of_inp_comps = data->num_of_inp_comps;
	DioCtrlInputCompTypeData	*inp_comp_types = data->inp_comp_types;
	*idx = num_of_inp_comps; 

	for (i = 0; i < num_of_inp_comps; i++)
	{
		if (comp_type == inp_comp_types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_input_component_type_to_dio_ctrl_data(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration, unsigned int num_of_low_2_high_switch, unsigned int num_of_high_2_low_switch, DioCtrlCompStatus required_status_to_initiate_switching, bool enabled)
{
	unsigned int i;
	bool comp_type_used;
	char temp[DIO_CTRL_INPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	DioCtrlInputCompTypeData	*lcl_inp_comp_types;
	if ((min_high_status_duration + 100000000) >= max_high_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_input_component_type_to_dio_ctrl_data", "Inconvenient min_high_status_duration & max_high_status_duration");	
	if ((min_low_status_duration + 100000000) >= max_low_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_input_component_type_to_dio_ctrl_data", "Inconvenient min_low_status_duration & max_low_status_duration");	
	if (!is_input_component_type_used(data, comp_type, &comp_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_input_component_type_to_dio_ctrl_data", "! is_input_component_type_used()");	
	if (comp_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_input_component_type_to_dio_ctrl_data", "comp_type_used");	
	if (!get_dio_ctrl_input_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_input_component_type_to_dio_ctrl_data", "!get_dio_ctrl_input_component_type_string()");
	lcl_inp_comp_types = g_new0(DioCtrlInputCompTypeData, data->num_of_inp_comps + 1);
	for (i = 0; i < data->num_of_inp_comps; i++)
		lcl_inp_comp_types[i] = data->inp_comp_types[i];
	g_free(data->inp_comp_types);
	data->inp_comp_types = lcl_inp_comp_types;
	data->inp_comp_types[data->num_of_inp_comps].type = comp_type;
	data->inp_comp_types[data->num_of_inp_comps].status = DIO_CTRL_COMP_STATUS_READY_FOR_SWITCHING;
	data->inp_comp_types[data->num_of_inp_comps].enabled = enabled;
	data->inp_comp_types[data->num_of_inp_comps].constraints.max_high_status_duration = max_high_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.min_high_status_duration = min_high_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.max_low_status_duration = max_low_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.min_low_status_duration = min_low_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.num_of_low_2_high_switch = num_of_low_2_high_switch;
	data->inp_comp_types[data->num_of_inp_comps].constraints.num_of_high_2_low_switch = num_of_high_2_low_switch;
	data->inp_comp_types[data->num_of_inp_comps].constraints.required_status_to_initiate_switching = required_status_to_initiate_switching;
	data->num_of_inp_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrlData", "add_input_component_type_to_dio_ctrl_data", temp);	
	return TRUE;
}

bool submit_new_time_params_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration)
{
	unsigned int idx;
	if (! get_input_component_type_idx_in_dio_ctrl_data(data, comp_type, &idx))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_time_params_for_input_component_type", "! get_input_component_type_idx_in_dio_ctrl_data()");	

	if ((min_high_status_duration + 100000000) >= max_high_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_time_params_for_input_component_type", "Inconvenient min_high_status_duration & max_high_status_duration");	
	if ((min_low_status_duration + 100000000) >= max_low_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_time_params_for_input_component_type", "Inconvenient min_low_status_duration & max_low_status_duration");	

	data->inp_comp_types[idx].constraints.max_high_status_duration = max_high_status_duration;
	data->inp_comp_types[idx].constraints.min_high_status_duration = min_high_status_duration;
	data->inp_comp_types[idx].constraints.max_low_status_duration = max_low_status_duration;
	data->inp_comp_types[idx].constraints.min_low_status_duration = min_low_status_duration;
	return TRUE;
}

bool submit_new_min_low_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_low_status_duration)
{
	unsigned int idx;
	if (! get_input_component_type_idx_in_dio_ctrl_data(data, comp_type, &idx))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_low_status_duration_for_input_component_type", "! get_input_component_type_idx_in_dio_ctrl_data()");	

	if ((min_low_status_duration + 100000000) >= data->inp_comp_types[idx].constraints.max_low_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_low_status_duration_for_input_component_type", "Inconvenient min_low_status_duration & max_low_status_duration");	

	data->inp_comp_types[idx].constraints.min_low_status_duration = min_low_status_duration;
	return TRUE;
}


bool submit_new_max_low_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp max_low_status_duration)
{
	unsigned int idx;
	if (! get_input_component_type_idx_in_dio_ctrl_data(data, comp_type, &idx))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_max_low_status_duration_for_input_component_type", "! get_input_component_type_idx_in_dio_ctrl_data()");	

	if ((data->inp_comp_types[idx].constraints.max_low_status_duration + 100000000) >= max_low_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_max_low_status_duration_for_input_component_type", "Inconvenient min_low_status_duration & max_low_status_duration");	

	data->inp_comp_types[idx].constraints.max_low_status_duration = max_low_status_duration;
	return TRUE;
}

bool submit_new_min_high_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_high_status_duration)
{
	unsigned int idx;
	if (! get_input_component_type_idx_in_dio_ctrl_data(data, comp_type, &idx))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_min_high_status_duration_for_input_component_type", "! get_input_component_type_idx_in_dio_ctrl_data()");	

	if ((min_high_status_duration + 100000000) >= data->inp_comp_types[idx].constraints.max_high_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_min_high_status_duration_for_input_component_type", "Inconvenient min_high_status_duration & max_high_status_duration");	

	data->inp_comp_types[idx].constraints.min_high_status_duration = min_high_status_duration;
	return TRUE;
}

bool submit_new_max_high_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp max_high_status_duration)
{
	unsigned int idx;
	if (! get_input_component_type_idx_in_dio_ctrl_data(data, comp_type, &idx))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_max_high_status_duration_for_input_component_type", "! get_input_component_type_idx_in_dio_ctrl_data()");	

	if ((data->inp_comp_types[idx].constraints.min_high_status_duration + 100000000) >= max_high_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "submit_new_max_high_status_duration_for_input_component_type", "Inconvenient min_max_status_duration & max_max_status_duration");	

	data->inp_comp_types[idx].constraints.max_high_status_duration = max_high_status_duration;
	return TRUE;
}

bool is_input_component_type_used(DioCtrlData* data, DioCtrlInputCompType comp_type, bool *used)
{
	unsigned int i;
	char temp[DIO_CTRL_INPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_dio_ctrl_input_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "is_input_component_type_used", "!get_dio_ctrl_input_component_type_string()");

	for (i = 0; i < data->num_of_inp_comps; i++)
	{
		if (comp_type == data->inp_comp_types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}

bool get_output_component_type_idx_in_dio_ctrl_data(DioCtrlData *data, DioCtrlOutputCompType comp_type, unsigned int *idx)
{
	unsigned int i;
	unsigned int num_of_outp_comps = data->num_of_outp_comps;
	DioCtrlOutputCompTypeData	*outp_comp_types = data->outp_comp_types;
	*idx = num_of_outp_comps; 

	for (i = 0; i < num_of_outp_comps; i++)
	{
		if (comp_type == outp_comp_types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_output_component_type_to_dio_ctrl_data(DioCtrlData *data, DioCtrlOutputCompType comp_type, TimeStamp high_status_duration)
{
	unsigned int i;
	bool comp_type_used;
	char temp[DIO_CTRL_OUTPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	DioCtrlOutputCompTypeData	*lcl_outp_comp_types;
	if (!is_output_component_type_used(data, comp_type, &comp_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_output_component_type_to_dio_ctrl_data", "! is_output_component_type_used()");	
	if (comp_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_output_component_type_to_dio_ctrl_data", "comp_type_used");	
	if (!get_dio_ctrl_output_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "add_output_component_type_to_dio_ctrl_data", "!get_dio_ctrl_output_component_type_string()");
	lcl_outp_comp_types = g_new0(DioCtrlOutputCompTypeData, data->num_of_outp_comps + 1);
	for (i = 0; i < data->num_of_outp_comps; i++)
		lcl_outp_comp_types[i] = data->outp_comp_types[i];
	g_free(data->outp_comp_types);
	data->outp_comp_types = lcl_outp_comp_types;
	data->outp_comp_types[data->num_of_outp_comps].type = comp_type;
	data->outp_comp_types[data->num_of_outp_comps].status = DIO_CTRL_COMP_STATUS_LOW;
	data->outp_comp_types[data->num_of_outp_comps].high_status_duration = high_status_duration;
	data->num_of_outp_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "DioCtrlData", "add_output_component_type_to_dio_ctrl_data", temp);	
	return TRUE;
}
bool is_output_component_type_used(DioCtrlData* data, DioCtrlOutputCompType comp_type, bool *used)
{
	unsigned int i;
	char temp[DIO_CTRL_OUTPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_dio_ctrl_output_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "DioCtrlData", "is_output_component_type_used", "!get_dio_ctrl_output_component_type_string()");

	for (i = 0; i < data->num_of_outp_comps; i++)
	{
		if (comp_type == data->outp_comp_types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;	
}
