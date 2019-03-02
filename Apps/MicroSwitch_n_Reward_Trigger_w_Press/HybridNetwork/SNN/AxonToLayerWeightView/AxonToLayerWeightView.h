#ifndef AXON_TO_LAYER_WEIGHT_VIEW_H
#define AXON_TO_LAYER_WEIGHT_VIEW_H

#define NUM_OF_AXON_TO_LAYER_GRAPHS	4

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.h"
#include "../../../../../Library/Izlib/Graphs/SynapticWeightHistGraph.h"
#include "../../HybridNetworkData.h"

bool create_axon_to_layer_weight_view_gui(GtkWidget *tabs);


#endif
