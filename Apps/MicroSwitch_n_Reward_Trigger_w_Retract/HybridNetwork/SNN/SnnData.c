#include "SnnData.h"



bool initialize_snn_data(void)
{
	blue_spike_network = allocate_network(blue_spike_network);
	in_silico_network = allocate_network(in_silico_network);

	initialize_data_read_write_handlers();

	msgs_exp_ctrl_2_neural_net = allocate_shm_server_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net);

	msgs_neural_net_2_prosthetic_ctrl_multi_thread = g_new0(NeuralNet2ProstheticCtrlMsg*, SNN_SIM_NUM_OF_DEDICATED_CPUS); 
	msgs_prosthetic_ctrl_2_neural_net_multi_thread = allocate_shm_server_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer(msgs_prosthetic_ctrl_2_neural_net_multi_thread, SNN_SIM_NUM_OF_DEDICATED_CPUS); 
	msgs_neural_net_2_gui = allocate_neural_net_2_gui_msg_buffer(msgs_neural_net_2_gui);
	trial_status_events = allocate_trial_status_events_buffer(trial_status_events, 100, 3000000);  //  3 ms latency


	in_silico_spike_data_for_graph = g_new0(SpikeData*, SNN_SIM_NUM_OF_DEDICATED_CPUS);	// allocate the array of buffers here. 
	in_silico_spike_data_for_recording = g_new0(SpikeData*, SNN_SIM_NUM_OF_DEDICATED_CPUS); // allocate the array of buffers here.  a recording message which is received before "ready_for_simulation" button can lead to segfault. since read_idx and write_idx are zero here, they will not try to access the buffers (refer to get_next_spike_data_item())


	return TRUE;
}


bool connect_to_prosthetic_ctrl(void )
{
	ProstheticCtrl2NeuralNetMsgItem msg_item;
	char str_prosthetic_ctrl_2_neural_net_msg[PROSTHETIC_CTRL_2_NEURAL_NET_MSG_STRING_LENGTH];
	unsigned int i, num_of_alive_responses = 0;
	while (1) 
	{ 
		for (i = 0; i < SNN_SIM_NUM_OF_DEDICATED_CPUS; i++)
		{
			while (get_next_prosthetic_ctrl_2_neural_net_msg_buffer_item(msgs_prosthetic_ctrl_2_neural_net_multi_thread[i], &msg_item))
			{
				get_prosthetic_ctrl_2_neural_net_msg_type_string(msg_item.msg_type, str_prosthetic_ctrl_2_neural_net_msg);
				print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_prosthetic_ctrl", str_prosthetic_ctrl_2_neural_net_msg);	
				switch (msg_item.msg_type)
				{
					case PROSTHETIC_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE:
						msgs_neural_net_2_prosthetic_ctrl_multi_thread[i] = allocate_shm_client_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer_item(msgs_neural_net_2_prosthetic_ctrl_multi_thread, i, MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY, MIN_NEURAL_NET_2_PROSTHETIC_CTRL_EVENT_SCHEDULING_DELAY);
						usleep(1000);
						if (msgs_neural_net_2_prosthetic_ctrl_multi_thread[i] == NULL)
							return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_prosthetic_ctrl", "msgs_neural_net_2_prosthetic_ctrl == NULL.");	
						if (!write_to_neural_net_2_prosthetic_ctrl_msg_buffer(msgs_neural_net_2_prosthetic_ctrl_multi_thread[i], rt_tasks_data->current_system_time, NEURAL_NET_2_PROSTHETIC_CTRL_MSG_I_AM_ALIVE, 0, 0, 0, 0))
							return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_prosthetic_ctrl", "write_to_neural_net_2_prosthetic_ctrl_msg_buffer().");	
						num_of_alive_responses++;
						if (num_of_alive_responses == SNN_SIM_NUM_OF_DEDICATED_CPUS)
						{
							goto EXIT;	// changed it from GET_JOINT_ANGLE_MINS to EXIT according to new design. no robot angle is required only binary reward signal is enough.
						}
						break;		
					default:
						return print_message(BUG_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_prosthetic_ctrl", str_prosthetic_ctrl_2_neural_net_msg);	
				}
			}
		}
		print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_prosthetic_ctrl", "Waiting for PROSTHETIC_CONTROL to connect.");	
		sleep(1);
	}

	EXIT:
	return print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_prosthetic_ctrl", "Connection to PROSTHETIC_CONTROL is successful!!!");
}

bool connect_to_exp_ctrl(void )
{
	ExpCtrl2NeuralNetMsgItem msg_item;
	char str_exp_ctrl_2_neural_net_msg[EXP_CTRL_2_NEURAL_NET_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_exp_ctrl_2_neural_net_msg_buffer_item(msgs_exp_ctrl_2_neural_net, &msg_item))
		{
			get_exp_ctrl_2_neural_net_msg_type_string(msg_item.msg_type, str_exp_ctrl_2_neural_net_msg);
			print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", str_exp_ctrl_2_neural_net_msg);	
			switch (msg_item.msg_type)
			{
				case EXP_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE:
					msgs_neural_net_2_exp_ctrl = allocate_shm_client_neural_net_2_exp_ctrl_msg_buffer(msgs_neural_net_2_exp_ctrl);
					sleep(1);
					if (msgs_neural_net_2_exp_ctrl == NULL)
						return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", "msgs_neural_net_2_exp_ctrl == NULL.");	
					if (!write_to_neural_net_2_exp_ctrl_msg_buffer(msgs_neural_net_2_exp_ctrl, rt_tasks_data->current_system_time, NEURAL_NET_2_EXP_CTRL_MSG_I_AM_ALIVE, 0))
						return print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", "write_to_neural_net_2_exp_ctrl_msg_buffer().");	
					print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", "Connection to EXP_CONTROL is successful!!!");	
					return TRUE;		
				default:
					return print_message(BUG_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", str_exp_ctrl_2_neural_net_msg);	
			}
		}
		print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", "Waiting for EXP_CONTROL to connect.");	
		sleep(1);
	}
	return print_message(BUG_MSG ,"HybridNetRLBMI", "HybridNetRLBMI", "connect_to_exp_ctrl", "Wrong hit in the code.");
}

