#ifndef WEIGHT_HISTORY_VIEW_H
#define WEIGHT_HISTORY_VIEW_H

#define NUM_OF_WEIGHT_HISTORY_GRAPHS	4

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo.h"
#include "../../../../../Library/Izlib/Graphs/SynapticWeightHistGraph.h"
#include "../../HybridNetworkData.h"

bool create_synaptic_wegiht_history_view_gui(GtkWidget *tabs);


#endif
