#ifndef NEURON_DYNAMICS_VIEW_H
#define NEURON_DYNAMICS_VIEW_H

#define NUM_OF_NEURON_DYNAMICS_GRAPHS  3

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../BufferViewHandler/BufferViewHandler.h"
#include "../../../../../Library/Izlib/Graphs/NeuronDynamicsGraph.h"
#include "../../../../../Library/Izlib/Combos/LayerNrnGrpNeuronCombo.h"
#include "../../../../../Library/Izlib/Combos/NeuronDynamicsCombo.h"

bool create_neuron_dynamics_view_gui(GtkWidget *tabs);
NeuronDynamicsGraphScrollLimited** get_neuron_dynamics_graphs_w_scroll_ptr(void);
void send_global_pause_button_sensitive_request(void);



#endif
