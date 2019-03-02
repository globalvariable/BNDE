#ifndef SNN_DATA_H
#define SNN_DATA_H

#include <gtk/gtk.h>
#include <stdbool.h>

#include "../HybridNetworkData.h"
#include "../../TaskConfig.h"
#include "../../InterProcessMsgConfig.h"
#include "../../../../Library/Messages/ExpCtrl2NeuralNet.h"
#include "../../../../Library/Messages/NeuralNet2ExpCtrl.h"
#include "../../../../Library/Messages/ProstheticCtrl2NeuralNet.h"
#include "../../../../Library/Messages/NeuralNet2ProstheticCtrl.h"
#include "../../../../Library/Messages/NeuralNet2Gui.h"
#include "../../../../Library/Izlib/NeuronDynamicsData/NeuronDynamicsData.h"
#include "../../../../Library/Izlib/STDPData/STDPData.h"
#include "../../../../Library/Izlib/EligibilityData/EligibilityData.h"
#include "../../../../Library/Izlib/SpikeData/SpikeData.h"
#include "DataHandling/DataHandling.h"

NeuralNet2GuiMsg				*msgs_neural_net_2_gui;


NeuronDynamicsBufferLimited	*neuron_dynamics_limited_buffer;
STDPBufferLimited			*stdp_limited_buffer;
EligibilityBufferLimited			*eligibility_limited_buffer;
SpikeData					**in_silico_spike_data_for_graph;  // for visualization  // each thread writes to one buffer.
SpikeData					**in_silico_spike_data_for_recording;  // for recording to hdd // each thread writes to one buffer.


ExpCtrl2NeuralNetMsg		*msgs_exp_ctrl_2_neural_net;
NeuralNet2ExpCtrlMsg		*msgs_neural_net_2_exp_ctrl;
ProstheticCtrl2NeuralNetMsg		**msgs_prosthetic_ctrl_2_neural_net_multi_thread;
NeuralNet2ProstheticCtrlMsg		**msgs_neural_net_2_prosthetic_ctrl_multi_thread;
NeuralNet2GuiMsg				*msgs_neural_net_2_gui;
ExpStatusEvents				*trial_status_events;   // to show status changed in graphs




double						total_synaptic_weights;

struct RewardData		
{
	double			learning_rate;	
	double			current_reward_prediction;		
} reward_data;



bool initialize_snn_data(void);
bool connect_to_prosthetic_ctrl(void );
bool connect_to_exp_ctrl(void );



#endif
