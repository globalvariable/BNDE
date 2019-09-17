#include "DioControl.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl = NULL;  
  	DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui = NULL;  
	DioCtrlData *dio_ctrl_data = NULL;
	DioCtrlParadigmRobotReach *dio_ctrl_paradigm = NULL;
	DioCtrlInputStatusHistory *dio_ctrl_input_status_history = NULL;
	DioCtrlOutputStatusHistory *dio_ctrl_output_status_history = NULL;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "rt_tasks_data == NULL.");


	dio_ctrl_data = allocate_dio_ctrl_data(dio_ctrl_data);

	dio_ctrl_paradigm = g_new0(DioCtrlParadigmRobotReach, 1);
	dio_ctrl_paradigm->target_led_component_indexes_list = g_new0(unsigned int, 2);
	dio_ctrl_paradigm->target_led_component_indexes_list[0] = LEFT_LED_IDX_IN_DIO_CTRL_DATA;
	dio_ctrl_paradigm->target_led_component_indexes_list[1] = RIGHT_LED_IDX_IN_DIO_CTRL_DATA;

	dio_ctrl_paradigm->early_training = FALSE;

//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_input_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, 10000000, 1500000000, 10000000, 1500000000, 1, 1, DIO_CTRL_COMP_STATUS_HIGH, FALSE)) /// 1 nose poke   // initially the nose of the animal gets into ir_beam. this means status low (pic sends it this way). Then the animal retracts nose and status becomes high. and gets it into ir_beam and the status is low. So the repsonse criterion is reached. 
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_input_component_type_to_dio_ctrl_data().");  
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_input_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_INPUT_COMPONENT_RESTRAIN_SWITCH, 10000000, 1500000000, 10000000, 1500000000, 0, 1, DIO_CTRL_COMP_STATUS_HIGH, FALSE)) /// 1 nose poke   // initially the nose of the animal gets into ir_beam. this means status low (pic sends it this way). Then the animal retracts nose and status becomes high. and gets it into ir_beam and the status is low. So the repsonse criterion is reached. 
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_input_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_input_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER, 100000000, 1500000000, 100000000, 1500000000, 0, 1, DIO_CTRL_COMP_STATUS_HIGH, FALSE)) /// 1 nose poke   // initially the nose of the animal gets into ir_beam. this means status low (pic sends it this way). Then the animal retracts nose and status becomes high. and gets it into ir_beam and the status is low. So the repsonse criterion is reached. 
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_input_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_input_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER, 100000000, 1500000000, 100000000, 1500000000, 0, 1, DIO_CTRL_COMP_STATUS_HIGH, FALSE)) /// 1 nose poke   // initially the nose of the animal gets into ir_beam. this means status low (pic sends it this way). Then the animal retracts nose and status becomes high. and gets it into ir_beam and the status is low. So the repsonse criterion is reached. 
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_input_component_type_to_dio_ctrl_data().");



//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_VALVE_CENTER, 40000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_BUZZER, 500000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_LEFT_TARGET_LED, 15000000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_RIGHT_TARGET_LED, 15000000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_GUIDE_LED, 15000000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_LEVER_SOLENOID, 15000000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");
//     Order of addition of components is important. Add them according to ConfigDioCtrlComponentNums.h
	if (! add_output_component_type_to_dio_ctrl_data(dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_GET_READY_LED, 15000000000))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "! add_output_component_type_to_dio_ctrl_data().");

	msgs_gui_2_dio_ctrl = allocate_gui_2_dio_ctrl_msg_buffer(msgs_gui_2_dio_ctrl);
	msgs_dio_ctrl_2_gui = allocate_dio_ctrl_2_gui_msg_buffer(msgs_dio_ctrl_2_gui);

	dio_ctrl_input_status_history = allocate_dio_ctrl_input_status_history(dio_ctrl_input_status_history, 100);
	dio_ctrl_output_status_history = allocate_dio_ctrl_output_status_history(dio_ctrl_output_status_history, 100);

	initialize_data_read_write_handlers();

	if(! create_dio_control_rt_thread(rt_tasks_data, dio_ctrl_data, msgs_gui_2_dio_ctrl, msgs_dio_ctrl_2_gui, dio_ctrl_input_status_history, dio_ctrl_output_status_history, dio_ctrl_paradigm))
		return print_message(ERROR_MSG ,"DioControl", "DioControl", "main", "create_dio_control_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_dio_ctrl, msgs_dio_ctrl_2_gui, dio_ctrl_input_status_history, dio_ctrl_output_status_history, dio_ctrl_data, dio_ctrl_paradigm);
	gtk_main();
	return 0;
}	
