#ifndef HYBRID_NETWORK_DATA_H
#define HYBRID_NETWORK_DATA_H


#include <pthread.h>
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "../../../Library/Izlib/Network/Network.h"
#include "../../../Library/Izlib/SpikeData/SpikeData.h"

RtTasksData *rt_tasks_data;

Network		*in_silico_network;
Network		*blue_spike_network;

bool	sorted_spike_delivery_enabled ;	// tell that the snn simulation is started so that bluespike can send sorted spikes to snn.



#endif
