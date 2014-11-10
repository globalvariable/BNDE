#ifndef STDP_H
#define STDP_H


typedef struct 	__PsStdpPrePost	PsStdpPrePost;
typedef struct 	__PsStdpPostPre	PsStdpPostPre;

#define STDP_TYPE_PRE_POST	0
#define STDP_TYPE_POST_PRE	1
#define MAX_NUM_OF_STDP_TYPE	2

#include "../Network/Network.h"


struct __PsStdpPrePost
{
	RTIME		last_set_time;				
	RTIME		duration;			
};

bool create_ps_pre_post_stdp_for_neuron_group(Network *network, unsigned int layer, unsigned int nrn_grp, RTIME duration);

bool create_ps_pre_post_stdp_for_neuron(Neuron* neuron, RTIME duration);


bool create_ps_pre_post_stdp_for_synapse(Neuron* neuron, RTIME duration, unsigned int synapse);


bool allocate_ps_pre_post_stdp_for_neuron(Neuron* neuron);


bool submit_new_ps_pre_post_stdp_vals_for_neuron(Neuron* neuron, RTIME duration);

bool submit_new_ps_pre_post_stdp_vals_for_synapse(Neuron* neuron, RTIME duration, unsigned int synapse);

bool submit_new_ps_pre_post_stdp_vals_for_neuron_according_to_pre_synaptic_neuron_group(Neuron* neuron , Network *axon_from_network, unsigned int axon_from_layer, unsigned int axon_from_nrn_grp, RTIME duration);

#endif
