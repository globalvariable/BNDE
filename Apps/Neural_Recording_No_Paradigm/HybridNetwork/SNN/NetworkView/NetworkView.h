#ifndef NETWORK_VIEW_H
#define NETWORK_VIEW_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../NetworkConfig.h"
#include "../../HybridNetworkData.h"
#include "../SnnData.h"
#include "../SnnRtTask.h"
#include "../SnnFunctions/SnnFunctions.h"
#include "../AxonalDelayConfig.h"
#include "../DataHandling/DataHandling.h"
#include "../../../../../Library/Izlib/Neuron/Neuron.h"
#include "../../../../../Library/Izlib/Neuron/NeuronTypes.h"
#include "../../../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.h"


bool create_recording_gui(GtkWidget *tabs);










#endif
