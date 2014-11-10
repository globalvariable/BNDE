#ifndef ELIGIBILITY_H
#define ELIGIBILITY_H


typedef struct 	__PsEligibility	PsEligibility;

#include "../Network/Network.h"

struct __PsEligibility
{
	RTIME		last_set_time;				
	RTIME		duration;		
};



bool create_ps_eligibility_for_neuron_group(Network *network, unsigned int layer, unsigned int nrn_grp, RTIME duration);  

bool create_ps_eligibility_for_neuron(Neuron* neuron, RTIME duration);

bool create_ps_eligibility_for_synapse(Neuron* neuron, RTIME duration, unsigned int synapse);

bool allocate_ps_eligibility_for_neuron(Neuron* neuron);

bool submit_new_ps_eligibility_vals_for_neuron(Neuron* neuron, RTIME duration);

bool submit_new_ps_eligibility_vals_for_synapse(Neuron* neuron, RTIME duration, unsigned int synapse);

bool submit_new_ps_eligibility_vals_for_neuron_according_to_pre_synaptic_neuron_group(Neuron* neuron, Network *axon_from_network, unsigned int axon_from_layer, unsigned int axon_from_nrn_grp, RTIME duration);



#endif
