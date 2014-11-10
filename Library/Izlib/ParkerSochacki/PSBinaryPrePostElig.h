#ifndef PS_BINARY_PRE_POST_ELIG_H
#define PS_BINARY_PRE_POST_ELIG_H

#include "ParkerSochacki.h"

// PS INTEGRATION WITH PRE POST STDP & BINARY ELIGIBILITY AND SYNAPTIC WEIGHT UPDATE DURING SIMULATION
bool evaluate_neuron_dyn_pre_post_w_binary_stdp_elig(Neuron *nrn, TimeStamp start_time, TimeStamp end_time, bool *spike_generated, TimeStamp *spike_time);




#endif
