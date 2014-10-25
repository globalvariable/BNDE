#ifndef STDP_VIEW_H
#define STDP_VIEW_H

#define NUM_OF_STDP_GRAPHS	1

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../BufferViewHandler/BufferViewHandler.h"
#include "../../../../../Library/Izlib/Graphs/STDPGraph.h"
#include "../../../../../Library/Izlib/Combos/LayerNrnGrpNrnSynapseCombo.h"
#include "../../../../../Library/Izlib/Combos/STDPCombo.h"

bool create_stdp_view_gui(GtkWidget *tabs);
unsigned int get_num_stdp_graphs_w_scroll(void);
STDPGraphScrollLimited** get_stdp_graphs_w_scroll_ptr(void);


#endif
