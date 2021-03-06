#include "InjectionCurrentData.h"


CurrentTemplate* allocate_current_templates(Network *network, ExpCtrlParadigmRobotReach *paradigm, CurrentTemplate* current_data, unsigned int num_of_trial_start_available_currents, unsigned int num_of_in_refractory_currents, unsigned int num_of_in_trial_currents)
{
	unsigned int i, j, k, m, n;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	if (network == NULL)
		return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "network == NULL.");
	if (paradigm == NULL)
		return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "trial_types_data == NULL.");
	if (current_data != NULL)
	{
		current_data = deallocate_current_templates(network, paradigm, current_data);
		current_data = allocate_current_templates(network, paradigm, current_data, num_of_trial_start_available_currents, num_of_in_refractory_currents, num_of_in_trial_currents);
		return current_data;
	}
	current_data = g_new0(CurrentTemplate,1);

	current_data->trial_start_available_currents = g_new0(CurrentPatternTemplate, num_of_trial_start_available_currents);
	current_data->num_of_trial_start_available_currents = num_of_trial_start_available_currents;
	for (m = 0; m < num_of_trial_start_available_currents; m++)
	{
		if (!get_num_of_layers_in_network(network, &num_of_layers))
			return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of layers. Already allocated some data. Take care of that data.");
		current_data->trial_start_available_currents[m].noise_params = g_new0(CurrentNoiseParams**, num_of_layers);	
		for (i = 0; i < num_of_layers; i++)
		{	
			if(!get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer))
				return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neuron groups. Already allocated some data. Take care of that data.");
			current_data->trial_start_available_currents[m].noise_params[i] = g_new0(CurrentNoiseParams*, num_of_neuron_groups_in_layer);
			for (j=0; j<num_of_neuron_groups_in_layer; j++)
			{
				if (!get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group))
					return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neurons. Already allocated some data. Take care of that data.");
				current_data->trial_start_available_currents[m].noise_params[i][j] = g_new0(CurrentNoiseParams, num_of_neurons_in_neuron_group);
			}
		}		
	}

	current_data->in_refractory_currents = g_new0(CurrentPatternTemplate, num_of_in_refractory_currents);
	current_data->num_of_in_refractory_currents = num_of_in_refractory_currents;
	for (m = 0; m < num_of_in_refractory_currents; m++)
	{
		if (!get_num_of_layers_in_network(network, &num_of_layers))
			return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of layers. Already allocated some data. Take care of that data.");
		current_data->in_refractory_currents[m].noise_params = g_new0(CurrentNoiseParams**, num_of_layers);	
		for (i = 0; i < num_of_layers; i++)
		{	
			if(!get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer))
				return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neuron groups. Already allocated some data. Take care of that data.");
			current_data->in_refractory_currents[m].noise_params[i] = g_new0(CurrentNoiseParams*, num_of_neuron_groups_in_layer);
			for (j=0; j<num_of_neuron_groups_in_layer; j++)
			{
				if (!get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group))
					return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neurons. Already allocated some data. Take care of that data.");
				current_data->in_refractory_currents[m].noise_params[i][j] = g_new0(CurrentNoiseParams, num_of_neurons_in_neuron_group);
			}
		}		
	}

	current_data->in_trial_currents = g_new0(CurrentPatternTemplate*, paradigm->num_of_robot_target_positions);
	current_data->num_of_in_trial_currents = num_of_in_trial_currents;
	for (n = 0; n < paradigm->num_of_robot_target_positions; n++)
	{
		current_data->in_trial_currents[n] = g_new0(CurrentPatternTemplate, num_of_in_trial_currents);
		for (m = 0; m < num_of_in_trial_currents; m++)
		{
			current_data->in_trial_currents[n][m].template_samples = g_new0(NeuronCurrentSample,  paradigm->max_trial_length/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE);
			current_data->in_trial_currents[n][m].num_of_template_samples = paradigm->max_trial_length/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE;
			current_data->in_trial_currents[n][m].template_length = paradigm->max_trial_length;
			for (k = 0; k < current_data->in_trial_currents[n][m].num_of_template_samples ; k++)
			{
				if (!get_num_of_layers_in_network(network, &num_of_layers))
					return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of layers. Already allocated some data. Take care of that data.");
				current_data->in_trial_currents[n][m].template_samples[k].current_sample = g_new0(InjectionCurrent**, num_of_layers);	
				for (i = 0; i < num_of_layers; i++)
				{	
					if(!get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer))
						return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neuron groups. Already allocated some data. Take care of that data.");
					current_data->in_trial_currents[n][m].template_samples[k].current_sample[i] = g_new0(InjectionCurrent*, num_of_neuron_groups_in_layer);
					for (j=0; j<num_of_neuron_groups_in_layer; j++)
					{
						if (!get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group))
							return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neurons. Already allocated some data. Take care of that data.");
						current_data->in_trial_currents[n][m].template_samples[k].current_sample[i][j] = g_new0(InjectionCurrent, num_of_neurons_in_neuron_group);
					}
				}
			}
		}
	}

	for (n = 0; n < paradigm->num_of_robot_target_positions; n++)
	{
		for (m = 0; m < num_of_in_trial_currents; m++)
		{
			if (!get_num_of_layers_in_network(network, &num_of_layers))
				return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of layers. Already allocated some data. Take care of that data.");
			current_data->in_trial_currents[n][m].noise_params = g_new0(CurrentNoiseParams**, num_of_layers);	
			for (i = 0; i < num_of_layers; i++)
			{	
				if(!get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer))
					return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neuron groups. Already allocated some data. Take care of that data.");
				current_data->in_trial_currents[n][m].noise_params[i] = g_new0(CurrentNoiseParams*, num_of_neuron_groups_in_layer);
				for (j=0; j<num_of_neuron_groups_in_layer; j++)
				{
					if (!get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group))
						return (CurrentTemplate*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Couldn' t retrieve number of neurons. Already allocated some data. Take care of that data.");
					current_data->in_trial_currents[n][m].noise_params[i][j] = g_new0(CurrentNoiseParams, num_of_neurons_in_neuron_group);
				}
			}
		}
	}
	print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "Created current_templates.");
	return current_data;

}
CurrentTemplate* deallocate_current_templates(Network *network, ExpCtrlParadigmRobotReach *paradigm, CurrentTemplate* current_data)
{
	print_message(BUG_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "deallocate_current_templates", "Not implemented.");
	return NULL;
}
bool submit_current_length_trial_start_available_status(Network *network, CurrentTemplate* current_data, unsigned int trial_start_available_current_num, TimeStamp current_length, bool *has_unallocated_current_template)
{
	unsigned int i, j, k, m;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	char str [200];
	if (current_data == NULL)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_current_length_trial_start_available_status", "current_data == NULL.");
	if (trial_start_available_current_num >= current_data->num_of_trial_start_available_currents)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_current_length_trial_start_available_status", "trial_start_available_current_num >= current_data->current_templates.num_of_trial_start_available_currents.");
	if (current_data->trial_start_available_currents[trial_start_available_current_num].template_samples != NULL)
	{
		for (k = 0; k < current_data->trial_start_available_currents[trial_start_available_current_num].num_of_template_samples; k++)
		{
			get_num_of_layers_in_network(network, &num_of_layers);
			for (i = 0; i < num_of_layers; i++)
			{	
				get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
				for (j=0; j<num_of_neuron_groups_in_layer; j++)
				{
					get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
					g_free(current_data->trial_start_available_currents[trial_start_available_current_num].template_samples[k].current_sample[i][j]);
				}
				g_free(current_data->trial_start_available_currents[trial_start_available_current_num].template_samples[k].current_sample[i]);
			}
			g_free(current_data->trial_start_available_currents[trial_start_available_current_num].template_samples[k].current_sample);
		}
		g_free(current_data->trial_start_available_currents[trial_start_available_current_num].template_samples);	
		current_data->trial_start_available_currents[trial_start_available_current_num].template_samples = NULL;
	}	
	current_data->trial_start_available_currents[trial_start_available_current_num].template_samples = g_new0(NeuronCurrentSample, current_length/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE);
	current_data->trial_start_available_currents[trial_start_available_current_num].num_of_template_samples = current_length/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE;
	current_data->trial_start_available_currents[trial_start_available_current_num].template_length = current_length;
	for (k = 0; k < current_data->trial_start_available_currents[trial_start_available_current_num].num_of_template_samples; k++)
	{
		get_num_of_layers_in_network(network, &num_of_layers);
		current_data->trial_start_available_currents[trial_start_available_current_num].template_samples[k].current_sample = g_new0(InjectionCurrent**, num_of_layers);
		for (i = 0; i < num_of_layers; i++)
		{	
			get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
			current_data->trial_start_available_currents[trial_start_available_current_num].template_samples[k].current_sample[i] = g_new0(InjectionCurrent*, num_of_neuron_groups_in_layer);
			for (j=0; j<num_of_neuron_groups_in_layer; j++)
			{
				get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
				current_data->trial_start_available_currents[trial_start_available_current_num].template_samples[k].current_sample[i][j] = g_new0(InjectionCurrent, num_of_neurons_in_neuron_group);
			}
		}
	}
	*has_unallocated_current_template = FALSE;
	for (m = 0; m < current_data->num_of_trial_start_available_currents; m++)
	{	
		if (current_data->trial_start_available_currents[m].template_samples == NULL)
		{
			*has_unallocated_current_template = TRUE;
			sprintf (str, "Still there are unallocated current patterns for trial start available current %d.", m);
			print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_current_length_trial_start_available_status", str);
		}
	}
	return TRUE;
}
bool submit_current_length_in_refractory_status(Network *network, CurrentTemplate* current_data, unsigned int in_refractory_current_num, TimeStamp current_length, bool *has_unallocated_current_template)
{
	unsigned int i, j, k, m;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	char str [200];
	if (current_data == NULL)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_current_length_in_refractory_status", "current_data == NULL.");
	if (in_refractory_current_num >= current_data->num_of_in_refractory_currents)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_current_length_in_refractory_status", "in_refractory_current_num >= current_data->current_templates.in_refractory_current_num.");
	if (current_data->in_refractory_currents[in_refractory_current_num].template_samples != NULL)
	{
		for (k = 0; k < current_data->in_refractory_currents[in_refractory_current_num].num_of_template_samples; k++)
		{
			get_num_of_layers_in_network(network, &num_of_layers);
			for (i = 0; i < num_of_layers; i++)
			{
				get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
				for (j=0; j<num_of_neuron_groups_in_layer; j++)
				{
					get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
					g_free(current_data->in_refractory_currents[in_refractory_current_num].template_samples[k].current_sample[i][j]);
				}
				g_free(current_data->in_refractory_currents[in_refractory_current_num].template_samples[k].current_sample[i]);
			}
			g_free(current_data->in_refractory_currents[in_refractory_current_num].template_samples[k].current_sample);
		}
		g_free(current_data->in_refractory_currents[in_refractory_current_num].template_samples);		
		current_data->in_refractory_currents[in_refractory_current_num].template_samples = NULL;	
	}

	current_data->in_refractory_currents[in_refractory_current_num].template_samples = g_new0(NeuronCurrentSample, current_length/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE);
	current_data->in_refractory_currents[in_refractory_current_num].num_of_template_samples = current_length/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE;
	current_data->in_refractory_currents[in_refractory_current_num].template_length = current_length;
	for (k = 0; k < current_data->in_refractory_currents[in_refractory_current_num].num_of_template_samples; k++)
	{
		get_num_of_layers_in_network(network, &num_of_layers);
		current_data->in_refractory_currents[in_refractory_current_num].template_samples[k].current_sample = g_new0(InjectionCurrent**, num_of_layers);
		for (i = 0; i < num_of_layers; i++)
		{
			get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
			current_data->in_refractory_currents[in_refractory_current_num].template_samples[k].current_sample[i] = g_new0(InjectionCurrent*, num_of_neuron_groups_in_layer);
			for (j=0; j<num_of_neuron_groups_in_layer; j++)
			{
				get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
				current_data->in_refractory_currents[in_refractory_current_num].template_samples[k].current_sample[i][j] = g_new0(InjectionCurrent, num_of_neurons_in_neuron_group);
			}
		}
	}
	*has_unallocated_current_template = FALSE;
	for (m = 0; m < current_data->num_of_in_refractory_currents; m++)
	{	
		if (current_data->in_refractory_currents[m].template_samples == NULL)
		{
			*has_unallocated_current_template = TRUE;
			sprintf (str, "Still there are unallocated current patterns for in refractory current %d.", m);
			print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_current_length_in_refractory_status", str);
		}
	}

	return TRUE;
}

CurrentPatternBuffer* allocate_current_pattern_buffer(Network *network, CurrentPatternBuffer *buffer, unsigned int buffer_size)
{
	unsigned int i, j, k;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;

	if (network == NULL)
		return (CurrentPatternBuffer*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_templates", "network == NULL.");
	if (buffer != NULL)
	{
		buffer = deallocate_current_pattern_buffer(network, buffer);
		buffer = allocate_current_pattern_buffer(network, buffer, buffer_size);
		return buffer;
	}
	buffer = g_new0(CurrentPatternBuffer,1);
	buffer->current_buffer = g_new0(NeuronCurrentSample, buffer_size);

	for (k = 0; k <  buffer_size; k++)
	{
		if (!get_num_of_layers_in_network(network, &num_of_layers))
			return (CurrentPatternBuffer*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_pattern_buffer", "Couldn' t retrieve number of layers. Already allocated some data. Take care of that data.");
		buffer->current_buffer[k].current_sample = g_new0(InjectionCurrent**, num_of_layers);
		for (i = 0; i < num_of_layers; i++)
		{
			if(!get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer))
				return (CurrentPatternBuffer*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_pattern_buffer", "Couldn' t retrieve number of neuron groups. Already allocated some data. Take care of that data.");
			buffer->current_buffer[k].current_sample[i] = g_new0(InjectionCurrent*, num_of_neuron_groups_in_layer);
			for (j=0; j<num_of_neuron_groups_in_layer; j++)
			{
				if (!get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group))
					return (CurrentPatternBuffer*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_pattern_buffer", "Couldn' t retrieve number of neurons. Already allocated some data. Take care of that data.");	
				buffer->current_buffer[k].current_sample[i][j] = g_new0(InjectionCurrent, num_of_neurons_in_neuron_group);
			}
		}
	}	
	buffer->buffer_size = buffer_size;
	print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_pattern_buffer", "Created current_pattern_buffer.");
	return buffer;
}
CurrentPatternBuffer* deallocate_current_pattern_buffer(Network *network, CurrentPatternBuffer *buffer)
{
	print_message(BUG_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "deallocate_current_pattern_buffer", "Not implemented.");	
	return NULL;
}

bool determine_in_trial_current_number_randomly(CurrentTemplate* current_template, unsigned int *current_num)	
{
	if (current_template == NULL)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "determine_in_trial_current_number_randomly", "current_template == NULL.");	
	*current_num = (unsigned int)(current_template->num_of_in_trial_currents* get_rand_number());
	return TRUE;
}

bool determine_trial_start_available_current_number_randomly(CurrentTemplate* current_template, unsigned int *current_num)	
{
	if (current_template == NULL)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "determine_in_trial_current_number_randomly", "current_template == NULL.");	
	*current_num = (unsigned int)(current_template->num_of_trial_start_available_currents* get_rand_number());
	return TRUE;
}

bool determine_in_refractory_current_number_randomly(CurrentTemplate* current_template, unsigned int *current_num)	
{
	if (current_template == NULL)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "determine_in_trial_current_number_randomly", "current_template == NULL.");	
	*current_num = (unsigned int)(current_template->num_of_in_refractory_currents* get_rand_number());
	return TRUE;
}

bool get_in_trial_current_pattern_template(CurrentTemplate* current_template, CurrentPatternTemplate** pattern_template, unsigned int trial_type_idx, unsigned int current_num)
{
	* pattern_template = &(current_template->in_trial_currents[trial_type_idx][current_num]);
	return TRUE;
}
bool get_trial_start_available_current_pattern_template(CurrentTemplate* current_template, CurrentPatternTemplate** pattern_template, unsigned int current_num)
{
	* pattern_template = &(current_template->trial_start_available_currents[current_num]);
	return TRUE;
}	
bool get_in_refractory_current_pattern_template(CurrentTemplate* current_template, CurrentPatternTemplate** pattern_template, unsigned int current_num)
{
	* pattern_template = &(current_template->in_refractory_currents[current_num]);
	return TRUE;
}

void reset_prev_noise_addition_times_for_current_template(Network *network, CurrentPatternTemplate* pattern_template)
{
	unsigned int i, j, k;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	get_num_of_layers_in_network(network, &num_of_layers);
	for (i = 0; i < num_of_layers; i++)
	{	
		get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
			for (k = 0; k < num_of_neurons_in_neuron_group; k++)
			{
				pattern_template->noise_params[i][j][k].prev_noise_addition_time = 0;
			}
		}
	}
}

bool load_current_template_sample_to_neurons_with_noise(Network *network, CurrentPatternTemplate* pattern_template, unsigned int current_template_read_idx, TimeStamp now)
{
	unsigned int i, j, k;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	InjectionCurrent ***current_samples =  pattern_template->template_samples[current_template_read_idx].current_sample;
	CurrentNoiseParams *neuron_noise_params;
	get_num_of_layers_in_network(network, &num_of_layers);
	for (i = 0; i < num_of_layers; i++)
	{	
		get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
			for (k = 0; k < num_of_neurons_in_neuron_group; k++)
			{
				neuron_noise_params = &(pattern_template->noise_params[i][j][k]);
				if ((now - neuron_noise_params->prev_noise_addition_time) >=  (neuron_noise_params->noise_addition_interval))
				{
					get_neuron_address(network, i, j, k)->iz_params->I_inject = current_samples[i][j][k] + randn_notrig(0, neuron_noise_params->noise_variance);
					neuron_noise_params->prev_noise_addition_time = now;
				}
			}
		}
	}
	return TRUE;
}

bool push_neuron_currents_to_current_pattern_buffer(Network *network, CurrentPatternBuffer* current_pattern_buffer, TimeStamp sampling_time)
{
	unsigned int i, j, k;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	InjectionCurrent ***current_samples =  current_pattern_buffer->current_buffer[current_pattern_buffer->buff_write_idx].current_sample;
	get_num_of_layers_in_network(network, &num_of_layers);
	for (i = 0; i < num_of_layers; i++)
	{	
		get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
			for (k = 0; k < num_of_neurons_in_neuron_group; k++)
			{
				current_samples[i][j][k] = get_neuron_address(network, i, j, k)->iz_params->I_inject;
			}
		}
	}
	pthread_mutex_lock(&(current_pattern_buffer->mutex));
	if ((current_pattern_buffer->buff_write_idx + 1) == current_pattern_buffer->buffer_size)
		current_pattern_buffer->buff_write_idx = 0;
	else
		current_pattern_buffer->buff_write_idx++;
	current_pattern_buffer->last_sample_time = sampling_time;
	pthread_mutex_unlock(&(current_pattern_buffer->mutex));
	return TRUE;
}

bool get_current_pattern_buffer_last_sample_time_and_write_idx(CurrentPatternBuffer *buffer, TimeStamp *last_sample_time, unsigned int *write_idx)
{
	pthread_mutex_lock(&(buffer->mutex));
	*write_idx = buffer->buff_write_idx;
	*last_sample_time = buffer->last_sample_time;
	pthread_mutex_unlock(&(buffer->mutex));
	return TRUE;
}

ConstantCurrent* allocate_constant_current(Network * network, ConstantCurrent* constant_current)
{
	unsigned int i, j;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	if (network == NULL)
		return (ConstantCurrent*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_constant_current", "network == NULL.");
	if (constant_current != NULL)
	{
		constant_current = deallocate_constant_current(network, constant_current);
		constant_current = allocate_constant_current(network, constant_current);
		return constant_current;
	}
	constant_current = g_new0(ConstantCurrent, 1);
	get_num_of_layers_in_network(network, &num_of_layers);
	constant_current->current = g_new0(InjectionCurrent**, num_of_layers);
	for (i = 0; i < num_of_layers; i++)
	{	
		get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
		constant_current->current[i] = g_new0(InjectionCurrent*, num_of_neuron_groups_in_layer);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			get_num_of_neurons_in_neuron_group(network, i, j, &num_of_neurons_in_neuron_group);
			constant_current->current[i][j] = g_new0(InjectionCurrent, num_of_neurons_in_neuron_group);
		}
	}
	print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_constant_current", "Created constant_current.");	
	return constant_current;
}
ConstantCurrent* deallocate_constant_current(Network * network, ConstantCurrent* constant_current)
{
	unsigned int i, j;
	unsigned int num_of_layers, num_of_neuron_groups_in_layer;
	if (network == NULL)
		return (ConstantCurrent*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "deallocate_constant_current", "network == NULL.");
	if (constant_current == NULL)
		return (ConstantCurrent*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "deallocate_constant_current", "constant_current == NULL.");
	get_num_of_layers_in_network(network, &num_of_layers);
	for (i = 0; i < num_of_layers; i++)
	{	
		get_num_of_neuron_groups_in_layer(network, i, &num_of_neuron_groups_in_layer);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			g_free(constant_current->current[i][j]);
		}
		g_free(constant_current->current[i]);
	}
	g_free(constant_current->current);		
	g_free(constant_current);
	print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "deallocate_constant_current", "Destroyed constant_current.");
	return NULL;	
}

CurrentPatternBufferLimited* allocate_current_pattern_buffer_limited(Network *network, CurrentPatternBufferLimited* buffer, unsigned int buffer_size, unsigned int num_of_selected_neurons)
{
	unsigned int i;
	if (network == NULL)
		return (CurrentPatternBufferLimited*)print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_pattern_buffer_limited", "network == NULL.");
	if (buffer != NULL)
	{
		buffer = deallocate_current_pattern_buffer_limited(network, buffer);
		buffer = allocate_current_pattern_buffer_limited(network, buffer, buffer_size, num_of_selected_neurons);
		return buffer;
	}
	buffer = g_new0(CurrentPatternBufferLimited,1);
	pthread_mutex_init(&(buffer->mutex), NULL);
	buffer->buffer = g_new0(SelectedNeuronCurrents, buffer_size);
	for (i = 0; i <  buffer_size; i++)
		buffer->buffer[i].neuron_current = g_new0(double, num_of_selected_neurons);
	buffer->selected_currs = g_new0(SelectedNeuronCurrList, num_of_selected_neurons);
	buffer->num_of_selected_neurons = num_of_selected_neurons;
	buffer->buffer_size = buffer_size;
	print_message(INFO_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "allocate_current_pattern_buffer_limited", "Created current_pattern_buffer_limited.");
	return buffer;
}
CurrentPatternBufferLimited* deallocate_current_pattern_buffer_limited(Network *network, CurrentPatternBufferLimited* buffer)
{
	print_message(BUG_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "deallocate_current_pattern_buffer_limited", "Not implemented.");	
	return NULL;
}
bool submit_selected_neuron_to_current_pattern_buffer_limited(Network *network, CurrentPatternBufferLimited* buffer, unsigned int layer, unsigned int neuron_group, unsigned int neuron_num,  unsigned int list_idx)
{
	if (!is_neuron(network, layer, neuron_group, neuron_num))
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_selected_neuron_to_current_pattern_buffer_limited", "! is_neuron().");
	if (list_idx >= buffer->num_of_selected_neurons)
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "InjectionCurrentData", "submit_selected_neuron_to_current_pattern_buffer_limited", "list_idx >= buffer->num_of_selected_neurons.");	
	pthread_mutex_lock(&(buffer->mutex));	
	buffer->selected_currs[list_idx].layer = layer;
	buffer->selected_currs[list_idx].neuron_group = neuron_group;
	buffer->selected_currs[list_idx].neuron_num = neuron_num;
	pthread_mutex_unlock(&(buffer->mutex));	
	return TRUE;
}
bool push_neuron_currents_to_neuron_current_buffer_limited(Network *network, CurrentPatternBufferLimited* buffer, TimeStamp sampling_time)
{
	unsigned int i;
	SelectedNeuronCurrList	*selected_currs = buffer->selected_currs;
	unsigned int num_of_selected_neurons = buffer->num_of_selected_neurons;
	double *neuron_current = buffer->buffer[buffer->buff_write_idx].neuron_current;

	pthread_mutex_lock(&(buffer->mutex));
	for (i = 0; i < num_of_selected_neurons; i++)
		neuron_current[i] = network->layers[selected_currs[i].layer]->neuron_groups[selected_currs[i].neuron_group]->neurons[selected_currs[i].neuron_num].iz_params->I_inject;
	if ((buffer->buff_write_idx + 1) == buffer->buffer_size)
		buffer->buff_write_idx = 0;
	else
		buffer->buff_write_idx++;
	buffer->last_sample_time = sampling_time;
	pthread_mutex_unlock(&(buffer->mutex));
	return TRUE;
}
bool get_current_pattern_buffer_limited_last_sample_time_and_write_idx(CurrentPatternBufferLimited *buffer, TimeStamp *last_sample_time, unsigned int *write_idx)
{
	pthread_mutex_lock(&(buffer->mutex));
	*write_idx = buffer->buff_write_idx;
	*last_sample_time = buffer->last_sample_time;
	pthread_mutex_unlock(&(buffer->mutex));
	return TRUE;
}
