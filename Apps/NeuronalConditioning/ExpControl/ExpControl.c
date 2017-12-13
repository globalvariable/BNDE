#include "ExpControl.h"



int main( int argc, char *argv[])
{
	unsigned int i;
	RtTasksData *rt_tasks_data = NULL;
	Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl = NULL;    
	ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui = NULL;    
	ExpCtrlParadigmRobotReach *paradigm = NULL;
	ClassifiedExpHistory* classified_history = NULL; 
	ExpStatusHistory *trial_status_history = NULL;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "ExpControl", "main", "rt_tasks_data == NULL.");

	paradigm = g_new0(ExpCtrlParadigmRobotReach, 1);

	paradigm->num_of_robot_target_positions = 2;
	paradigm->num_of_target_led_components = 2;

	paradigm->num_of_robot_start_positions = 7;	

	paradigm->num_of_difficulty_levels = (paradigm->num_of_robot_start_positions +1)/ 2; 

	paradigm->max_trial_length = g_new0(TimeStamp, paradigm->num_of_difficulty_levels);

	paradigm->max_trial_length[0] = 3000000000;
	for (i = 1; i < paradigm->num_of_difficulty_levels; i++)
	{
//		paradigm->max_trial_length[i] = paradigm->max_trial_length[i-1] + 2500000000;
		paradigm->max_trial_length[i] = paradigm->max_trial_length[i-1] + 0;
	}
	paradigm->trial_refractory = 2000000000;
	paradigm->get_ready_to_trial_start_length = 40000000;

	paradigm->target_led_component_indexes_list = g_new0(unsigned int, paradigm->num_of_target_led_components);
	paradigm->target_led_component_indexes_list[0] = LEFT_LED_IDX_IN_DIO_CTRL_DATA;   // get this number from DioControl/ConfigDioCtrlComponentNums.h
	paradigm->target_led_component_indexes_list[1] = RIGHT_LED_IDX_IN_DIO_CTRL_DATA;

	paradigm->current_trial_data.auto_target_select_mode_on = TRUE; 
	paradigm->current_trial_data.robot_start_position_idx = 0; 

	paradigm->all_success_average = allocate_averaging_struct(paradigm->all_success_average, 40);

	paradigm->target_success_average = g_new0(AveragingStruct*, paradigm->num_of_robot_target_positions);
	paradigm->target_success_average_small = g_new0(AveragingStruct*, paradigm->num_of_robot_target_positions);
	for (i = 0; i < paradigm->num_of_robot_target_positions; i++)
	{
		paradigm->target_success_average[i] = allocate_averaging_struct(paradigm->target_success_average[i], 20);
		paradigm->target_success_average_small[i] = allocate_averaging_struct(paradigm->target_success_average_small[i], 4);
	}


	classified_history = allocate_classified_trial_history(classified_history, 1000, paradigm->num_of_robot_target_positions); 

	msgs_gui_2_exp_ctrl = allocate_gui_2_exp_ctrl_msg_buffer(msgs_gui_2_exp_ctrl);
	msgs_exp_ctrl_2_gui = allocate_exp_ctrl_2_gui_msg_buffer(msgs_exp_ctrl_2_gui);

	trial_status_history = allocate_trial_status_history(trial_status_history, 20);

	if (! create_exp_control_rt_thread(rt_tasks_data, msgs_gui_2_exp_ctrl, paradigm, classified_history, msgs_exp_ctrl_2_gui, trial_status_history))
		return print_message(ERROR_MSG ,"BMIExpController", "ExpControl", "main", "create_exp_control_rt_thread().");


	initialize_data_read_write_handlers();

	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_exp_ctrl, paradigm, classified_history, msgs_exp_ctrl_2_gui, trial_status_history);
	gtk_main();
	return 0;
}	



