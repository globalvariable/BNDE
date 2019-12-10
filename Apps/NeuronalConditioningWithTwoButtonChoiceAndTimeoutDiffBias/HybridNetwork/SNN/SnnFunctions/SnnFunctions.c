#include "SnnFunctions.h"




bool add_neurons_for_in_silico_network(void)
{
	if (in_silico_network->num_of_neurons != 0)
		return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIConfig", "prepare_external_and_in_silico_network", "Previously added neurons!! Restart program to clear network.().");	

	// BASE SERVO

	if (!add_neuron_nodes_to_layer(in_silico_network, 1 , 0, FALSE))   // add one neuron node to layer 0 
		return print_message(ERROR_MSG ,"HybridNetRLBMI", "SnnFunctions", "add_neurons_for_in_silico_network", "add_neuron_nodes_to_layer()."); 

	if (!add_neuron_nodes_to_layer(in_silico_network, 1 , 1, FALSE))   // add one neuron node to layer 1 
		return print_message(ERROR_MSG ,"HybridNetRLBMI", "SnnFunctions", "add_neurons_for_in_silico_network", "add_neuron_nodes_to_layer()."); 
	
	return TRUE;
}



bool set_output_layers(void)
{
	set_layer_type_of_the_neurons_in_layer(in_silico_network, 0, NEURON_LAYER_TYPE_OUTPUT);
	set_layer_type_of_the_neurons_in_layer(in_silico_network, 1, NEURON_LAYER_TYPE_OUTPUT);
	return TRUE;	
}

bool connect_external_to_in_silico_network(void)
{
	Neuron *nrn;
	unsigned int i, j, k, cntr = 0;
	
	bool connection_matrix[3][2] = {	{1,0},
								{0,1},
								{1,1}};

	for (i=0; i < blue_spike_network->layer_count; i++)
	{
		for (j=0; j < blue_spike_network->layers[i]->neuron_group_count; j++)
		{
			for (k=0; k < blue_spike_network->layers[i]->neuron_groups[j]->neuron_count; k++)
			{
				nrn = get_neuron_address(blue_spike_network, i, j, k);					
				if (! nrn->include)
					continue;
				if ((connection_matrix[cntr % 3][0]))
				{
					if (! connect_neurons(blue_spike_network, i, j, k, in_silico_network, LAYER_BASE_SERVO_EXTENSOR_SPINY, 0, 0, BLUESPIKE_2_IN_SILICO_EXCITATORY_WEIGHT_MAX, BLUESPIKE_2_IN_SILICO_EXCITATORY_WEIGHT_MIN, BLUESPIKE_2_IN_SILICO_INHIBITORY_WEIGHT_MAX, BLUESPIKE_2_IN_SILICO_INHIBITORY_WEIGHT_MIN, BLUESPIKE_2_IN_SILICO_EXCITATORY_DELAY_MAX, BLUESPIKE_2_IN_SILICO_EXCITATORY_DELAY_MIN, BLUESPIKE_2_IN_SILICO_INHIBITORY_DELAY_MAX, BLUESPIKE_2_IN_SILICO_INHIBITORY_DELAY_MIN, MAXIMUM_BLUE_SPIKE_TO_IN_SILICO_AXONAL_DELAY, MINIMUM_BLUE_SPIKE_TO_IN_SILICO_AXONAL_DELAY, TRUE, FALSE))
						return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIConfig", "connect_external_to_in_silico_network", "! connect_neurons().");
				}
				if ((connection_matrix[cntr % 3][1]))
				{
					if (! connect_neurons(blue_spike_network, i, j, k, in_silico_network, LAYER_BASE_SERVO_FLEXOR_SPINY, 0, 0, BLUESPIKE_2_IN_SILICO_EXCITATORY_WEIGHT_MAX, BLUESPIKE_2_IN_SILICO_EXCITATORY_WEIGHT_MIN, BLUESPIKE_2_IN_SILICO_INHIBITORY_WEIGHT_MAX, BLUESPIKE_2_IN_SILICO_INHIBITORY_WEIGHT_MIN, BLUESPIKE_2_IN_SILICO_EXCITATORY_DELAY_MAX, BLUESPIKE_2_IN_SILICO_EXCITATORY_DELAY_MIN, BLUESPIKE_2_IN_SILICO_INHIBITORY_DELAY_MAX, BLUESPIKE_2_IN_SILICO_INHIBITORY_DELAY_MIN, MAXIMUM_BLUE_SPIKE_TO_IN_SILICO_AXONAL_DELAY, MINIMUM_BLUE_SPIKE_TO_IN_SILICO_AXONAL_DELAY, TRUE, FALSE))
						return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIConfig", "connect_external_to_in_silico_network", "! connect_neurons().");
				}
				cntr++;
			}
		}
	}
	if (cntr == 0)
		return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIConfig", "connect_external_to_in_silico_network", "No connections has been made. no included units in sorted_spike_time_stamp.");
	return TRUE;
}



bool connect_medium_spiny_neurons(void)
{
	if (! connect_layers(in_silico_network, LAYER_BASE_SERVO_EXTENSOR_SPINY, in_silico_network, LAYER_BASE_SERVO_FLEXOR_SPINY, MSN_2_MSN_EXCITATORY_WEIGHT_MAX, MSN_2_MSN_EXCITATORY_WEIGHT_MIN, MSN_2_MSN_INHIBITORY_WEIGHT_MAX, MSN_2_MSN_INHIBITORY_WEIGHT_MIN, MSN_2_MSN_EXCITATORY_DELAY_MAX, MSN_2_MSN_EXCITATORY_DELAY_MIN, MSN_2_MSN_INHIBITORY_DELAY_MAX, MSN_2_MSN_INHIBITORY_DELAY_MIN, MAXIMUM_IN_SILICO_TO_IN_SILICO_AXONAL_DELAY, MINIMUM_IN_SILICO_TO_IN_SILICO_AXONAL_DELAY, MSN_2_MSN_EXCITATORY_PROBABILITY, MSN_2_MSN_INHIBITORY_PROBABILITY, FALSE, FALSE))
		return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIConfig", "connect_external_to_in_silico_network", "! connect_ext_network_layer_to_int_network_layer().");

	if (! connect_layers(in_silico_network, LAYER_BASE_SERVO_FLEXOR_SPINY, in_silico_network, LAYER_BASE_SERVO_EXTENSOR_SPINY, MSN_2_MSN_EXCITATORY_WEIGHT_MAX, MSN_2_MSN_EXCITATORY_WEIGHT_MIN, MSN_2_MSN_INHIBITORY_WEIGHT_MAX, MSN_2_MSN_INHIBITORY_WEIGHT_MIN, MSN_2_MSN_EXCITATORY_DELAY_MAX, MSN_2_MSN_EXCITATORY_DELAY_MIN, MSN_2_MSN_INHIBITORY_DELAY_MAX, MSN_2_MSN_INHIBITORY_DELAY_MIN, MAXIMUM_IN_SILICO_TO_IN_SILICO_AXONAL_DELAY, MINIMUM_IN_SILICO_TO_IN_SILICO_AXONAL_DELAY, MSN_2_MSN_EXCITATORY_PROBABILITY, MSN_2_MSN_INHIBITORY_PROBABILITY, FALSE, FALSE))
		return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIConfig", "connect_external_to_in_silico_network", "! connect_ext_network_layer_to_int_network_layer().");

	return TRUE;
}


void normalize_plastic_synaptic_weights(Network *in_silico_network, double weight_total)
{
	Neuron	**all_neurons;
	unsigned int num_of_all_neurons, i, j;
	double sum_weights, diff_weights;	
	Neuron *nrn;

	all_neurons = in_silico_network->all_neurons;

	num_of_all_neurons = in_silico_network->num_of_neurons;

	for (i = 0; i < num_of_all_neurons; i++) 
	{
		nrn = all_neurons[i];
		sum_weights = 0;
		for (j = 0; j < nrn->syn_list->num_of_synapses; j++)
		{
			if (! nrn->syn_list->synapses[j].plastic)
				continue;
			sum_weights += nrn->syn_list->synapses[j].weight;		
		}
		diff_weights = sum_weights - weight_total;

		for (j = 0; j < nrn->syn_list->num_of_synapses; j++)
		{
			if (! nrn->syn_list->synapses[j].plastic)
				continue;
			 nrn->syn_list->synapses[j].weight =  nrn->syn_list->synapses[j].weight - (( nrn->syn_list->synapses[j].weight/sum_weights)*diff_weights);
		}	
	}

}

void update_synaptic_weights_all_neurons_in_thread(Neuron **all_neurons, unsigned int num_of_all_neurons, unsigned int task_num, unsigned int num_of_dedicated_cpus, double reward, double total_synaptic_weights, RTIME current_time)
{
	unsigned int i, j;
	Neuron *nrn;
	Synapse			*synapses;
	Synapse			*synapse;
	SynapseIndex		num_of_synapses; 
	double	E, dw;  // eligibility
	double sum_weights, diff_weights;
	double max_weight;

	for (i = task_num; i < num_of_all_neurons; i+=num_of_dedicated_cpus)  // simulate the neurons for which this thread is responsible
	{
		nrn = all_neurons[i];
		if (nrn->iz_params == NULL)
			continue;
		synapses = nrn->syn_list->synapses;
		num_of_synapses = nrn->syn_list->num_of_synapses;
		max_weight = (total_synaptic_weights/num_of_synapses)*2.5;
		for (j = 0; j < num_of_synapses; j++)
		{
			synapse = &(synapses[j]);
			if (! synapse->plastic)
				continue;
			if ((synapse->ps_eligibility->last_set_time + synapse->ps_eligibility->duration) > current_time)
				E = 1;
			else
				E = 0;
			
			dw = reward * E * synapses[j].weight;
			synapse->weight+=dw;
			if (synapse->weight > max_weight)
			{
				synapse->weight = max_weight;
			}

		}
		sum_weights = 0;
		for (j = 0; j < num_of_synapses; j++)
		{
			if (! synapses[j].plastic)
				continue;
			sum_weights += synapses[j].weight;
		}
		diff_weights = sum_weights - total_synaptic_weights;
		for (j = 0; j < num_of_synapses; j++)
		{
			if (! synapses[j].plastic)
				continue;
			synapses[j].weight = synapses[j].weight - ((synapses[j].weight/sum_weights)*diff_weights);
		}		
	}
	return;
}
