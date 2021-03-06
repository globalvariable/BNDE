#ifndef NEURON_DYNAMICS_COMBO_H
#define NEURON_DYNAMICS_COMBO_H

typedef struct 	__NeuronDynamicsCombo 		NeuronDynamicsCombo;
#include <stdbool.h>
#include <gtk/gtk.h>
#include "../../Misc/Misc.h"

struct  __NeuronDynamicsCombo
{
	GtkWidget *combo;
};

NeuronDynamicsCombo* allocate_neuron_dynamics_combo(GtkWidget *hbox, NeuronDynamicsCombo *combo);
bool neuron_dynamics_combo_get_selected(NeuronDynamicsCombo *combo, int *idx);


#endif
