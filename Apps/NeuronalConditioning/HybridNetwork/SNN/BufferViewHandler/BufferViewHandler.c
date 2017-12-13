#include "BufferViewHandler.h"



static NeuronDynamicsGraphScrollLimited **neuron_dynamics_graph_arr;

static NetworkSpikePatternGraphScroll *blue_spike_spike_graph;
static NetworkSpikePatternGraphScroll *in_silico_spike_graph;

static bool buffer_visualization_global_pause_request = FALSE;
static bool buffer_visualization_global_resume_request = FALSE;

static bool *neuron_dynamics_graph_visualization_resume_request = NULL;
static bool *stdp_graph_visualization_resume_request = NULL;
static bool *eligibility_graph_visualization_resume_request = NULL;
static bool blue_spike_spike_graph_visualization_resume_request = FALSE;
static bool in_silico_spike_graph_visualization_resume_request = FALSE;


static bool buffer_view_handler_paused_global = TRUE;

static gboolean timeout_callback(gpointer user_data) ;


bool buffer_view_handler(GtkWidget *tabs)
{
	if (!create_neuron_dynamics_view_gui(tabs))
		return  print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "buffer_view_handler","! create_neuron_dynamics_view_gui().");
/*	if (!create_blue_spike_spike_pattern_view_gui(tabs))
		return  print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "buffer_view_handler","! create_blue_spike_spike_pattern_view_gui().");
	if (!create_in_silico_spike_pattern_view_gui(tabs))
		return  print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "buffer_view_handler","! create_in_silico_spike_pattern_view_gui().");
	if (!create_synaptic_wegiht_history_view_gui(tabs))
		return  print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "buffer_view_handler","! create_synaptic_wegiht_history_view_gui().");
	if (!create_axon_to_layer_weight_view_gui(tabs))
		return  print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "buffer_view_handler","! create_axon_to_layer_weight_view_gui().");

	neuron_dynamics_graph_arr = get_neuron_dynamics_graphs_w_scroll_ptr();
	neuron_dynamics_graph_visualization_resume_request = g_new0(bool, NUM_OF_NEURON_DYNAMICS_GRAPHS);

	blue_spike_spike_graph = get_blue_spike_spike_pattern_graph_ptr();
	in_silico_spike_graph = get_in_silico_spike_pattern_graph_ptr();

	g_timeout_add(500 , timeout_callback, NULL);		// timeout shoud be less than buffer_followup_latency,

*/

	if (!create_blue_spike_spike_pattern_view_gui(tabs))
		return  print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "buffer_view_handler","! create_blue_spike_spike_pattern_view_gui().");

	blue_spike_spike_graph = get_blue_spike_spike_pattern_graph_ptr();

	g_timeout_add(500 , timeout_callback, NULL);		// timeout shoud be less than buffer_followup_latency,




	return TRUE;
}


static gboolean timeout_callback(gpointer user_data) 
{
	unsigned int i;
	TimeStamp current_system_time;
	unsigned int neuron_dynamics_buffer_write_idx;
	TimeStamp last_sample_time;

	current_system_time = (rt_tasks_data->current_system_time/PARKER_SOCHACKI_INTEGRATION_STEP_SIZE) *PARKER_SOCHACKI_INTEGRATION_STEP_SIZE;
	if (buffer_visualization_global_pause_request)
	{
		buffer_view_handler_paused_global = TRUE;
		buffer_visualization_global_pause_request = FALSE;

		blue_spike_spike_graph->global_pause_request = TRUE;

	}
	if  (buffer_visualization_global_resume_request)	// shoud determine start_idx for neuron dynamics graphs and spike pattern graphs for every request to sync them all. 
	{
		buffer_view_handler_paused_global = FALSE;
		buffer_visualization_global_resume_request = FALSE;


		if (! determine_spike_pattern_graph_scroll_start_time_and_read_indexes(blue_spike_spike_graph, current_system_time))
			return print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "gboolean timeout_callback","! determine_spike_pattern_graph_scroll_start_time().");	
		if (!blue_spike_spike_graph->locally_paused)
			clear_network_spike_pattern_graph_w_scroll(blue_spike_network, blue_spike_spike_graph);
		blue_spike_spike_graph->globally_paused = FALSE;
		blue_spike_spike_graph->global_pause_request = FALSE;
		if (blue_spike_spike_graph_visualization_resume_request)
		{
			blue_spike_spike_graph->locally_paused = FALSE;
			blue_spike_spike_graph_visualization_resume_request = FALSE;
			clear_network_spike_pattern_graph_w_scroll(blue_spike_network, blue_spike_spike_graph);
		}	
	
	}

	if (! handle_spike_pattern_graph_scrolling_and_plotting(blue_spike_spike_graph, blue_spike_network, current_system_time))
		return print_message(ERROR_MSG ,"IzNeuronSimulators", "HybridNetRLBMI", "gboolean timeout_callback","! handle_spike_pattern_graph_scrolling_and_plotting().");		

	return TRUE;
}

void send_global_pause_request_to_buffer_view_handler(void)
{
	buffer_visualization_global_pause_request = TRUE;
}

void send_global_resume_request_to_buffer_view_handler(void)
{
	buffer_visualization_global_resume_request = TRUE;
}

bool send_neuron_dynamics_graph_resume_request_to_buffer_view_handler(unsigned int graph_idx)
{
	if (! buffer_view_handler_paused_global)
	{
		neuron_dynamics_graph_visualization_resume_request[graph_idx] = TRUE;
		buffer_visualization_global_resume_request = TRUE;
		return TRUE;
	}
	return FALSE;
}

bool send_stdp_graph_resume_request_to_buffer_view_handler(unsigned int graph_idx)
{
	if (! buffer_view_handler_paused_global)
	{
		stdp_graph_visualization_resume_request[graph_idx] = TRUE;
		buffer_visualization_global_resume_request = TRUE;
		return TRUE;
	}
	return FALSE;
}

bool send_eligibility_graph_resume_request_to_buffer_view_handler(unsigned int graph_idx)
{
	if (! buffer_view_handler_paused_global)
	{
		eligibility_graph_visualization_resume_request[graph_idx] = TRUE;
		buffer_visualization_global_resume_request = TRUE;
		return TRUE;
	}
	return FALSE;
}

bool send_blue_spike_spike_graph_resume_request_to_buffer_view_handler(void)
{
	if (! buffer_view_handler_paused_global)
	{
		blue_spike_spike_graph_visualization_resume_request = TRUE;
		buffer_visualization_global_resume_request = TRUE;
		return TRUE;
	}
	return FALSE;
}

bool send_in_silico_spike_graph_resume_request_to_buffer_view_handler(void)
{
	if (! buffer_view_handler_paused_global)
	{
		in_silico_spike_graph_visualization_resume_request = TRUE;
		buffer_visualization_global_resume_request = TRUE;
		return TRUE;
	}
	return FALSE;
}

bool is_buffer_view_handler_paused(void)
{
	return buffer_view_handler_paused_global;	
}

